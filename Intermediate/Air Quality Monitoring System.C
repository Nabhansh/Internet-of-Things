typedef struct {
    float pm2_5;    /* µg/m³ */
    float pm10;
    float co_ppm;
    float co2_ppm;
    float voc_ppb;
    int   aqi;
} AirQuality;

int compute_aqi(float pm2_5) {
    /* Simplified US EPA breakpoints */
    if (pm2_5 <= 12.0f) return (int)(pm2_5 / 12.0f * 50);
    if (pm2_5 <= 35.4f) return 51 + (int)((pm2_5 - 12.1f) / 23.3f * 49);
    if (pm2_5 <= 55.4f) return 101 + (int)((pm2_5 - 35.5f) / 19.9f * 49);
    if (pm2_5 <= 150.4f) return 151 + (int)((pm2_5 - 55.5f) / 94.9f * 49);
    return 201;
}

const char *aqi_category(int aqi) {
    if (aqi <= 50)  return "Good";
    if (aqi <= 100) return "Moderate";
    if (aqi <= 150) return "Unhealthy for Sensitive Groups";
    if (aqi <= 200) return "Unhealthy";
    return "Very Unhealthy";
}

void air_quality_monitor(void) {
    separator("4. Air Quality Monitoring System");

    AirQuality aq;
    aq.pm2_5   = rand_range(0.0f, 80.0f);
    aq.pm10    = aq.pm2_5 * rand_range(1.5f, 3.0f);
    aq.co_ppm  = rand_range(0.0f, 10.0f);
    aq.co2_ppm = rand_range(400.0f, 2000.0f);
    aq.voc_ppb = rand_range(0.0f, 500.0f);
    aq.aqi     = compute_aqi(aq.pm2_5);

    printf("  PM2.5   : %.1f µg/m³\n", aq.pm2_5);
    printf("  PM10    : %.1f µg/m³\n", aq.pm10);
    printf("  CO      : %.2f ppm\n",   aq.co_ppm);
    printf("  CO₂     : %.0f ppm\n",   aq.co2_ppm);
    printf("  VOC     : %.0f ppb\n",   aq.voc_ppb);
    printf("  AQI     : %d  (%s)\n",   aq.aqi, aqi_category(aq.aqi));

    if (aq.co_ppm > 9.0f)    printf("  ⚠ DANGER: CO level is hazardous!\n");
    if (aq.co2_ppm > 1500.0f) printf("  ⚠ CO₂ too high — ventilate now!\n");
    if (aq.aqi > 150)         printf("  ⚠ Wear N95 mask outdoors!\n");
}
