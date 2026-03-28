typedef struct
{
    float temp_C;
    float humidity;
    float pressure_hPa;
    float wind_kmh;
    float rain_mm;
} WeatherReading;

const char *weather_condition(const WeatherReading *w)
{
    if (w->rain_mm > 5.0f)
        return "Rainy";
    if (w->wind_kmh > 50.0f)
        return "Stormy";
    if (w->humidity > 85.0f)
        return "Foggy";
    if (w->temp_C > 30.0f)
        return "Hot & Sunny";
    return "Clear";
}

void weather_station(void)
{
    separator("2. Weather Monitoring Station");

    WeatherReading w;
    w.temp_C = rand_range(-5.0f, 40.0f);
    w.humidity = rand_range(20.0f, 100.0f);
    w.pressure_hPa = rand_range(990.0f, 1025.0f);
    w.wind_kmh = rand_range(0.0f, 80.0f);
    w.rain_mm = rand_range(0.0f, 20.0f);

    /* Heat index (simplified Steadman) */
    float hi = -8.78f + 1.61f * w.temp_C + 2.34f * (w.humidity / 100.0f) - 0.146f * w.temp_C * (w.humidity / 100.0f);

    printf("  Temperature  : %.1f °C\n", w.temp_C);
    printf("  Humidity     : %.1f %%\n", w.humidity);
    printf("  Pressure     : %.1f hPa\n", w.pressure_hPa);
    printf("  Wind Speed   : %.1f km/h\n", w.wind_kmh);
    printf("  Rainfall     : %.1f mm\n", w.rain_mm);
    printf("  Heat Index   : %.1f °C\n", hi);
    printf("  Condition    : %s\n", weather_condition(&w));

    if (w.wind_kmh > 60.0f)
        printf("  ⚠ HIGH WIND WARNING!\n");
    if (w.rain_mm > 10.0f)
        printf("  ⚠ HEAVY RAIN WARNING!\n");
}