#include <stdio.h>

int fuel_function(int mass, int current_fuel = 0)
{
    int fuel_mass = mass/3 -2;
    if (fuel_mass <= 0) {
        return current_fuel;
    }
    return fuel_function(fuel_mass, current_fuel+fuel_mass);
}

int main()
{
    int total_fuel = 0;

    while(true) {
        int mass=0;
        scanf("%d", &mass);
        if (mass == 0) {
            break;
        }
        total_fuel+=fuel_function(mass);
    }

    printf("%d", total_fuel);

    return 0;
}
