#include <stdlib.h>
#include <math.h>
#include "integracion.h"

double riemann_integral(
    triple_func_t f,
    double xmin, double xmax,
    double ymin, double ymax,
    double zmin, double zmax,
    int nx, int ny, int nz,
    double a, double b, double c
) {
    double dx = (xmax - xmin) / nx;
    double dy = (ymax - ymin) / ny;
    double dz = (zmax - zmin) / nz;
    double total = 0.0;

    for (int i = 0; i < nx; i++) {
        double x = xmin + (i + 0.5) * dx;
        for (int j = 0; j < ny; j++) {
            double y = ymin + (j + 0.5) * dy;
            for (int k = 0; k < nz; k++) {
                double z = zmin + (k + 0.5) * dz;
                total += f(x, y, z, a, b, c) * dx * dy * dz;
            }
        }
    }
    return total;
}

double monte_carlo_integral(
    triple_func_t f,
    double xmin, double xmax,
    double ymin, double ymax,
    double zmin, double zmax,
    int N,
    double a, double b, double c
) {
    double V = (xmax - xmin) * (ymax - ymin) * (zmax - zmin);
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double x = xmin + (double)rand() / RAND_MAX * (xmax - xmin);
        double y = ymin + (double)rand() / RAND_MAX * (ymax - ymin);
        double z = zmin + (double)rand() / RAND_MAX * (zmax - zmin);
        sum += f(x, y, z, a, b, c);
    }
    return V * (sum / N);
}
