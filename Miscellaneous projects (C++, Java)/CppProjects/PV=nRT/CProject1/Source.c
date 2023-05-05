#include <stdio.h>

const double GAS_CONST = 8.3144621;

double ComputeGasVolume(double pressure, double temperature, double moles) {
	double volume = (moles * GAS_CONST * temperature) / pressure;

	return volume;
}

int main(void) {
	double gasPressure;
	double gasMoles;
	double gasTemperature;
	double gasVolume;

	gasPressure = 100;
	gasMoles = 1;
	gasTemperature = 273;

	gasVolume = ComputeGasVolume(gasPressure, gasTemperature, gasMoles);
	printf("Gas volume: %lf m^3\n", gasVolume);

	return 0;
}