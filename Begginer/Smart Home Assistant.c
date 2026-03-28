typedef struct
{
    float temperature; /* °C */
    float humidity;    /* %  */
    int motion;        /* 0/1 */
    int light_lux;
    int door_open;
} HomeState;

void smart_home_assistant(void)
{
    separator("1. Smart Home Assistant");

    HomeState h;
    h.temperature = rand_range(18.0f, 35.0f);
    h.humidity = rand_range(30.0f, 80.0f);
    h.motion = rand() % 2;
    h.light_lux = rand() % 1000 + 100;
    h.door_open = rand() % 2;

    printf("  [Sensors]\n");
    printf("    Temperature : %.1f °C\n", h.temperature);
    printf("    Humidity    : %.1f %%\n", h.humidity);
    printf("    Motion      : %s\n", h.motion ? "DETECTED" : "none");
    printf("    Light       : %d lux\n", h.light_lux);
    printf("    Door        : %s\n", h.door_open ? "OPEN" : "closed");

    printf("\n  [Assistant Actions]\n");
    if (h.temperature > 28.0f)
        printf("    → AC ON  (%.1f°C is too hot)\n", h.temperature);
    else if (h.temperature < 20.0f)
        printf("    → Heater ON  (%.1f°C is too cold)\n", h.temperature);

    if (h.humidity > 70.0f)
        printf("    → Dehumidifier ON\n");

    if (h.light_lux < 300 && h.motion)
        printf("    → Smart lights ON (motion + low light)\n");

    if (h.door_open)
        printf("    → ALERT: Front door is open!\n");

    if (!h.motion)
        printf("    → No motion — switching to Eco mode\n");
}