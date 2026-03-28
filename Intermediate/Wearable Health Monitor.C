typedef struct {
    int   heart_rate;    /* bpm */
    int   spo2;          /* % */
    float body_temp;     /* °C */
    int   steps;
    float hrv_ms;        /* heart-rate variability */
    int   stress_score;  /* 0–100 */
} HealthData;

void wearable_health_monitor(void) {
    separator("5. Wearable Health Monitor");

    HealthData hd;
    hd.heart_rate  = 55 + rand() % 90;
    hd.spo2        = 93 + rand() % 8;
    hd.body_temp   = rand_range(36.0f, 38.5f);
    hd.steps       = rand() % 15000;
    hd.hrv_ms      = rand_range(20.0f, 100.0f);
    hd.stress_score = (int)(100.0f - hd.hrv_ms);
    if (hd.stress_score < 0) hd.stress_score = 0;

    printf("  Heart Rate    : %d bpm ", hd.heart_rate);
    if (hd.heart_rate < 60)       printf("(bradycardia)\n");
    else if (hd.heart_rate > 100) printf("(tachycardia)\n");
    else                           printf("(normal)\n");

    printf("  SpO₂          : %d %%\n", hd.spo2);
    printf("  Body Temp     : %.1f °C ", hd.body_temp);
    if (hd.body_temp >= 37.5f) printf("(fever)\n");
    else                        printf("(normal)\n");

    printf("  Steps Today   : %d  (%s)\n", hd.steps,
           hd.steps >= 10000 ? "goal reached ✓" : "keep walking");
    printf("  HRV           : %.1f ms\n", hd.hrv_ms);
    printf("  Stress Score  : %d/100  (%s)\n", hd.stress_score,
           hd.stress_score > 70 ? "HIGH — take a break" :
           hd.stress_score > 40 ? "Moderate"            : "Low");

    if (hd.spo2 < 95)
        printf("  ⚠ Low SpO₂ — seek medical attention!\n");
    if (hd.body_temp > 38.0f)
        printf("  ⚠ Fever detected!\n");
}
