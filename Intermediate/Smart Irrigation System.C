#define ZONES 6
typedef struct {
    char  zone[16];
    float soil_moisture;
    float temp_C;
    float rain_forecast_mm;
    int   valve_open;
    int   schedule_min;
} IrrigationZone;

void smart_irrigation(void) {
    separator("6. Smart Irrigation System");

    IrrigationZone zones[ZONES] = {
        {"Zone A - Lawn",   0,0,0,0,0},
        {"Zone B - Shrubs", 0,0,0,0,0},
        {"Zone C - Garden", 0,0,0,0,0},
        {"Zone D - Trees",  0,0,0,0,0},
        {"Zone E - Flower", 0,0,0,0,0},
        {"Zone F - Veggie", 0,0,0,0,0},
    };

    float rain_forecast = rand_range(0.0f, 15.0f);
    printf("  Rain forecast (next 24h): %.1f mm\n\n", rain_forecast);

    printf("  %-18s  %-10s  %-7s  %-6s  %s\n",
           "Zone", "Moisture", "Temp°C", "Valve", "Mins");
    printf("  ──────────────────────────────────────────────\n");

    for (int i = 0; i < ZONES; i++) {
        zones[i].soil_moisture      = rand_range(10.0f, 90.0f);
        zones[i].temp_C             = rand_range(15.0f, 40.0f);
        zones[i].rain_forecast_mm   = rain_forecast;

        /* Open valve if dry + no heavy rain coming */
        int needs_water = zones[i].soil_moisture < 45.0f;
        int skip_rain   = rain_forecast > 10.0f;
        zones[i].valve_open    = needs_water && !skip_rain;
        zones[i].schedule_min  = zones[i].valve_open
            ? (int)((45.0f - zones[i].soil_moisture) * 0.8f) : 0;

        printf("  %-18s  %5.1f %%    %5.1f    %s     %d\n",
               zones[i].zone,
               zones[i].soil_moisture,
               zones[i].temp_C,
               zones[i].valve_open ? "OPEN" : "shut",
               zones[i].schedule_min);
    }

    int total_min = 0;
    for (int i = 0; i < ZONES; i++) total_min += zones[i].schedule_min;
    printf("\n  Total irrigation time today: %d min\n", total_min);
    float litres = total_min * 12.0f;  /* 12 L/min assumed */
    printf("  Estimated water usage: %.0f L\n", litres);
}
