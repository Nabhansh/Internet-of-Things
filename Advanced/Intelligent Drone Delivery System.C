typedef struct {
    int   id;
    float lat, lon;         /* current position */
    float dest_lat, dest_lon;
    float battery_pct;
    float payload_kg;
    float speed_mps;
    int   status;           /* 0=idle 1=flying 2=delivering 3=returning */
} Drone;

static const char *drone_status[] = {"Idle", "Flying", "Delivering", "Returning"};

float haversine_km(float lat1, float lon1, float lat2, float lon2) {
    float dlat = (lat2 - lat1) * (float)M_PI / 180.0f;
    float dlon = (lon2 - lon1) * (float)M_PI / 180.0f;
    float a = sinf(dlat/2)*sinf(dlat/2) +
              cosf(lat1*(float)M_PI/180.0f)*cosf(lat2*(float)M_PI/180.0f)*
              sinf(dlon/2)*sinf(dlon/2);
    return 6371.0f * 2.0f * atan2f(sqrtf(a), sqrtf(1-a));
}

void drone_delivery(void) {
    separator("8. Intelligent Drone Delivery System");

#define NUM_DRONES 5
    Drone fleet[NUM_DRONES];
    for (int i = 0; i < NUM_DRONES; i++) {
        fleet[i].id          = i + 1;
        fleet[i].lat         = 28.6f + rand_range(-0.5f, 0.5f);
        fleet[i].lon         = 77.2f + rand_range(-0.5f, 0.5f);
        fleet[i].dest_lat    = 28.6f + rand_range(-0.5f, 0.5f);
        fleet[i].dest_lon    = 77.2f + rand_range(-0.5f, 0.5f);
        fleet[i].battery_pct = rand_range(20.0f, 100.0f);
        fleet[i].payload_kg  = rand_range(0.0f, 5.0f);
        fleet[i].speed_mps   = rand_range(5.0f, 20.0f);
        fleet[i].status      = rand() % 4;
    }

    printf("  %-5s  %-12s  %-9s  %-10s  %-12s  %s\n",
           "Drone", "Battery", "Payload", "Speed", "Dist(km)", "Status");
    printf("  ──────────────────────────────────────────────────────\n");
    for (int i = 0; i < NUM_DRONES; i++) {
        float dist = haversine_km(fleet[i].lat, fleet[i].lon,
                                  fleet[i].dest_lat, fleet[i].dest_lon);
        float eta  = dist * 1000.0f / fleet[i].speed_mps / 60.0f; /* minutes */
        printf("  D%-4d  %5.1f %%      %.2f kg    %5.1f m/s   %.2f km     %s",
               fleet[i].id, fleet[i].battery_pct,
               fleet[i].payload_kg, fleet[i].speed_mps,
               dist, drone_status[fleet[i].status]);
        if (fleet[i].status == 1)
            printf(" (ETA %.1f min)", eta);
        printf("\n");
        if (fleet[i].battery_pct < 25.0f)
            printf("         ⚠ LOW BATTERY — return to base!\n");
    }
}
