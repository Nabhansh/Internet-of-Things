#define LANES 4
typedef struct {
    char  name[16];
    int   vehicle_count;
    float avg_speed_kmh;
    int   green_sec;
    int   density;       /* vehicles/100m */
} TrafficLane;

const char *congestion_level(int density) {
    if (density < 10) return "Free Flow";
    if (density < 25) return "Moderate";
    if (density < 40) return "Heavy";
    return "GRIDLOCK";
}

void smart_traffic(void) {
    separator("7. Smart Traffic Management System");

    TrafficLane lanes[LANES] = {
        {"North", 0,0,0,0},
        {"South", 0,0,0,0},
        {"East",  0,0,0,0},
        {"West",  0,0,0,0},
    };

    int total_vehicles = 0;
    for (int i = 0; i < LANES; i++) {
        lanes[i].vehicle_count = rand() % 80 + 5;
        lanes[i].avg_speed_kmh = rand_range(5.0f, 80.0f);
        lanes[i].density       = lanes[i].vehicle_count / 2;
        total_vehicles        += lanes[i].vehicle_count;
    }

    /* Adaptive green-light allocation proportional to density */
    int cycle = 120; /* total cycle seconds */
    for (int i = 0; i < LANES; i++) {
        lanes[i].green_sec = (int)((float)lanes[i].vehicle_count / total_vehicles * cycle);
    }

    printf("  %-8s  %-9s  %-12s  %-12s  %s\n",
           "Lane", "Vehicles", "Avg Speed", "Green (sec)", "Status");
    printf("  ─────────────────────────────────────────────────\n");
    for (int i = 0; i < LANES; i++) {
        printf("  %-8s  %-9d  %-12.1f  %-12d  %s\n",
               lanes[i].name,
               lanes[i].vehicle_count,
               lanes[i].avg_speed_kmh,
               lanes[i].green_sec,
               congestion_level(lanes[i].density));
    }

    /* Find busiest lane */
    int max_idx = 0;
    for (int i = 1; i < LANES; i++)
        if (lanes[i].vehicle_count > lanes[max_idx].vehicle_count) max_idx = i;
    printf("\n  Priority lane: %s (%d vehicles)\n",
           lanes[max_idx].name, lanes[max_idx].vehicle_count);
}
