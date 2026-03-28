#define NUM_PLANTS 4
typedef struct
{
    char name[20];
    int soil_moisture; /* 0–100 % */
    int threshold;     /* water if below */
    int pump_on;
} Plant;

void plant_watering_system(void)
{
    separator("3. Plant Watering System");

    Plant plants[NUM_PLANTS] = {
        {"Basil", 0, 40, 0},
        {"Tomato", 0, 50, 0},
        {"Cactus", 0, 20, 0},
        {"Fern", 0, 60, 0}};

    for (int i = 0; i < NUM_PLANTS; i++)
    {
        plants[i].soil_moisture = rand() % 101;
        plants[i].pump_on = plants[i].soil_moisture < plants[i].threshold;
    }

    printf("  %-10s  %-9s  %-10s  %s\n",
           "Plant", "Moisture", "Threshold", "Pump");
    printf("  ──────────────────────────────────────\n");
    for (int i = 0; i < NUM_PLANTS; i++)
    {
        printf("  %-10s  %3d %%      %3d %%      %s\n",
               plants[i].name,
               plants[i].soil_moisture,
               plants[i].threshold,
               plants[i].pump_on ? "ON 💧" : "off");
    }

    /* Daily water budget */
    int total_pumps = 0;
    for (int i = 0; i < NUM_PLANTS; i++)
        total_pumps += plants[i].pump_on;
    printf("\n  Pumps active: %d/%d   Est. water used: %d mL\n",
           total_pumps, NUM_PLANTS, total_pumps * 250);
}
