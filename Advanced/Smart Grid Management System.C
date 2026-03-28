#define GRID_NODES 6
typedef struct {
    char  name[20];
    float demand_kW;
    float supply_kW;
    float voltage_V;
    float frequency_Hz;
    int   fault;
} GridNode;

void smart_grid(void) {
    separator("BONUS: Smart Grid Management System");

    GridNode nodes[GRID_NODES] = {
        {"Residential A", 0,0,0,0,0},
        {"Residential B", 0,0,0,0,0},
        {"Industrial Z1", 0,0,0,0,0},
        {"Solar Farm",    0,0,0,0,0},
        {"Wind Turbine",  0,0,0,0,0},
        {"Battery Store", 0,0,0,0,0},
    };

    float total_demand = 0.0f, total_supply = 0.0f;
    for (int i = 0; i < GRID_NODES; i++) {
        nodes[i].demand_kW   = rand_range(10.0f, 500.0f);
        nodes[i].supply_kW   = rand_range(10.0f, 500.0f);
        nodes[i].voltage_V   = rand_range(215.0f, 245.0f);
        nodes[i].frequency_Hz= rand_range(49.5f, 50.5f);
        nodes[i].fault       = (nodes[i].voltage_V < 218.0f || nodes[i].voltage_V > 242.0f
                                || nodes[i].frequency_Hz < 49.7f) ? 1 : 0;
        total_demand += nodes[i].demand_kW;
        total_supply += nodes[i].supply_kW;
    }

    printf("  %-18s  %-12s  %-12s  %-9s  %-11s  %s\n",
           "Node", "Demand(kW)", "Supply(kW)", "V(volt)", "Hz", "Status");
    printf("  ────────────────────────────────────────────────────────────\n");
    for (int i = 0; i < GRID_NODES; i++) {
        printf("  %-18s  %-12.1f  %-12.1f  %-9.1f  %-11.2f  %s\n",
               nodes[i].name,
               nodes[i].demand_kW,
               nodes[i].supply_kW,
               nodes[i].voltage_V,
               nodes[i].frequency_Hz,
               nodes[i].fault ? "⚠ FAULT" : "✓ Normal");
    }

    float balance = total_supply - total_demand;
    printf("\n  Total Demand : %.1f kW\n", total_demand);
    printf("  Total Supply : %.1f kW\n",  total_supply);
    printf("  Balance      : %+.1f kW  (%s)\n", balance,
           balance > 0 ? "surplus → charge batteries"
                       : "deficit → draw from storage");

    int faults = 0;
    for (int i = 0; i < GRID_NODES; i++) faults += nodes[i].fault;
    if (faults)
        printf("  ⚠ %d node(s) need attention!\n", faults);
    else
        printf("  Grid operating normally.\n");
}
