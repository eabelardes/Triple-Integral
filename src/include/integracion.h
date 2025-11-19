#ifndef INTEGRACION_H
#define INTEGRACION_H

typedef double (*triple_func_t)(double, double, double, double, double, double);

double riemann_integral(
    triple_func_t f,
    double xmin, double xmax,
    double ymin, double ymax,
    double zmin, double zmax,
    int nx, int ny, int nz,
    double a, double b, double c
);

double monte_carlo_integral(
    triple_func_t f,
    double xmin, double xmax,
    double ymin, double ymax,
    double zmin, double zmax,
    int N,
    double a, double b, double c
);

#endif
