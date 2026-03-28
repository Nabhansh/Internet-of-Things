#define NUM_MACHINES 5
typedef struct
{
    char name[24];
    float vibration_g; /* g-force RMS */
    float temp_C;
    float current_A;
    int runtime_hours;
    float bearing_wear_pct;
    int alert;
} Machine;

/* Simple threshold-based predictive model */
void predict_maintenance(Machine *m)
{
    m->alert = 0;
    float risk = 0.0f;
    if (m->vibration_g > 3.0f)
        risk += 30.0f;
    if (m->temp_C > 85.0f)
        risk += 25.0f;
    if (m->current_A > 15.0f)
        risk += 20.0f;
    if (m->bearing_wear_pct > 60.0f)
        risk += 25.0f;

    if (risk >= 60.0f)
        m->alert = 2; /* critical */
    else if (risk >= 30.0f)
        m->alert = 1; /* warning  */
}

void industrial_predictive_maintenance(void)
{
    separator("9. Industrial Predictive Maintenance");

    Machine machines[NUM_MACHINES] = {
        {"CNC Mill #1", 0, 0, 0, 0, 0, 0},
        {"Conveyor Belt A", 0, 0, 0, 0, 0, 0},
        {"Pump Station 3", 0, 0, 0, 0, 0, 0},
        {"Compressor B", 0, 0, 0, 0, 0, 0},
        {"Robot Arm #7", 0, 0, 0, 0, 0, 0},
    };

    const char *alert_str[] = {"OK", "WARNING", "CRITICAL"};
    const char *alert_sym[] = {"✓", "⚠", "✖"};

    for (int i = 0; i < NUM_MACHINES; i++)
    {
        machines[i].vibration_g = rand_range(0.1f, 6.0f);
        machines[i].temp_C = rand_range(30.0f, 110.0f);
        machines[i].current_A = rand_range(2.0f, 20.0f);
        machines[i].runtime_hours = rand() % 50000;
        machines[i].bearing_wear_pct = rand_range(0.0f, 100.0f);
        predict_maintenance(&machines[i]);
    }

    printf("  %-20s  %-8s  %-7s  %-8s  %-10s  %-8s  %s\n",
           "Machine", "Vib(g)", "T(°C)", "I(A)", "Runtime h", "Bearing", "Status");
    printf("  ───────────────────────────────────────────────────────────────────\n");
    for (int i = 0; i < NUM_MACHINES; i++)
    {
        printf("  %-20s  %-8.2f  %-7.1f  %-8.1f  %-10d  %-8.1f  %s %s\n",
               machines[i].name,
               machines[i].vibration_g,
               machines[i].temp_C,
               machines[i].current_A,
               machines[i].runtime_hours,
               machines[i].bearing_wear_pct,
               alert_sym[machines[i].alert],
               alert_str[machines[i].alert]);
    }

    int critical = 0, warnings = 0;
    for (int i = 0; i < NUM_MACHINES; i++)
    {
        if (machines[i].alert == 2)
            critical++;
        else if (machines[i].alert == 1)
            warnings++;
    }
    printf("\n  Summary: %d critical, %d warnings, %d healthy\n",
           critical, warnings, NUM_MACHINES - critical - warnings);
    if (critical)
        printf("  → Schedule immediate maintenance for critical machines!\n");
}
