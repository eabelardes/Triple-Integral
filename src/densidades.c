#include <math.h>

// Densidad constante: ρ = 1 → cuerpos homogéneos (bloques metálicos)
double densidad_constante(double x, double y, double z, double a, double b, double c) {
    (void)a; (void)b; (void)c;
    return 1.0;
}

// Densidad lineal: ρ = a*x + b*y + c*z → gradientes lineales (estratificación térmica)
double densidad_lineal(double x, double y, double z, double a, double b, double c) {
    return a * x + b * y + c * z;
}

// Densidad gaussiana: ρ = exp(-(x²+y²+z²)) → distribuciones concentradas (nubes atómicas)
double densidad_gaussiana(double x, double y, double z, double a, double b, double c) {
    (void)a; (void)b; (void)c;
    return exp(-(x*x + y*y + z*z));
}

// Envoltorios para x*ρ, y*ρ, z*ρ
double densidad_constante_x(double x, double y, double z, double a, double b, double c) { return x * densidad_constante(x, y, z, a, b, c); }
double densidad_constante_y(double x, double y, double z, double a, double b, double c) { return y * densidad_constante(x, y, z, a, b, c); }
double densidad_constante_z(double x, double y, double z, double a, double b, double c) { return z * densidad_constante(x, y, z, a, b, c); }

double densidad_lineal_x(double x, double y, double z, double a, double b, double c) { return x * densidad_lineal(x, y, z, a, b, c); }
double densidad_lineal_y(double x, double y, double z, double a, double b, double c) { return y * densidad_lineal(x, y, z, a, b, c); }
double densidad_lineal_z(double x, double y, double z, double a, double b, double c) { return z * densidad_lineal(x, y, z, a, b, c); }

double densidad_gaussiana_x(double x, double y, double z, double a, double b, double c) { return x * densidad_gaussiana(x, y, z, a, b, c); }
double densidad_gaussiana_y(double x, double y, double z, double a, double b, double c) { return y * densidad_gaussiana(x, y, z, a, b, c); }
double densidad_gaussiana_z(double x, double y, double z, double a, double b, double c) { return z * densidad_gaussiana(x, y, z, a, b, c); }
