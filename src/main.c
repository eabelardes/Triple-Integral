#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "integracion.h"
#include "densidades.h"

int main() {
    srand((unsigned int)time(NULL));

    double xmin, xmax, ymin, ymax, zmin, zmax;
    printf("Ingrese los límites de integración [xmin xmax ymin ymax zmin zmax]: ");
    scanf("%lf %lf %lf %lf %lf %lf", &xmin, &xmax, &ymin, &ymax, &zmin, &zmax);

    int metodo;
    printf("Método de integración (1 = Riemann, 2 = Monte Carlo): ");
    scanf("%d", &metodo);

    int tipo_densidad;
    printf("Tipo de densidad (1 = constante, 2 = lineal, 3 = gaussiana): ");
    scanf("%d", &tipo_densidad);

    double a = 0, b = 0, c = 0;
    if (tipo_densidad == 2) {
        printf("Ingrese coeficientes a, b, c: ");
        scanf("%lf %lf %lf", &a, &b, &c);
    }

    int nx = 10, ny = 10, nz = 10;
    int N = 10000;

    if (metodo == 1) {
        printf("Ingrese subdivisiones nx ny nz (ej: 20 20 20): ");
        scanf("%d %d %d", &nx, &ny, &nz);
    } else {
        printf("Ingrese número de muestras N (ej: 100000): ");
        scanf("%d", &N);
    }

    triple_func_t rho, fx, fy, fz;
    char densidad_str[20];
    if (tipo_densidad == 1) {
        rho = densidad_constante;
        fx = densidad_constante_x;
        fy = densidad_constante_y;
        fz = densidad_constante_z;
        strcpy(densidad_str, "constante");
    } else if (tipo_densidad == 2) {
        rho = densidad_lineal;
        fx = densidad_lineal_x;
        fy = densidad_lineal_y;
        fz = densidad_lineal_z;
        strcpy(densidad_str, "lineal");
    } else if (tipo_densidad == 3) {
        rho = densidad_gaussiana;
        fx = densidad_gaussiana_x;
        fy = densidad_gaussiana_y;
        fz = densidad_gaussiana_z;
        strcpy(densidad_str, "gaussiana");
    } else {
        fprintf(stderr, "Error: tipo de densidad inválido.\n");
        return 1;
    }

    char metodo_str[20];
    strcpy(metodo_str, (metodo == 1) ? "Riemann" : "MonteCarlo");

    clock_t start = clock();
    double M, xM, yM, zM;

    if (metodo == 1) {
        M  = riemann_integral(rho, xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, a, b, c);
        xM = riemann_integral(fx,  xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, a, b, c);
        yM = riemann_integral(fy,  xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, a, b, c);
        zM = riemann_integral(fz,  xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, a, b, c);
    } else {
        M  = monte_carlo_integral(rho, xmin, xmax, ymin, ymax, zmin, zmax, N, a, b, c);
        xM = monte_carlo_integral(fx,  xmin, xmax, ymin, ymax, zmin, zmax, N, a, b, c);
        yM = monte_carlo_integral(fy,  xmin, xmax, ymin, ymax, zmin, zmax, N, a, b, c);
        zM = monte_carlo_integral(fz,  xmin, xmax, ymin, ymax, zmin, zmax, N, a, b, c);
    }
    clock_t end = clock();
    double tiempo = (double)(end - start) / CLOCKS_PER_SEC;

    if (fabs(M) < 1e-12) {
        fprintf(stderr, "Error: masa es cero o muy cercana a cero.\n");
        return 1;
    }

    double x_bar = xM / M;
    double y_bar = yM / M;
    double z_bar = zM / M;

    FILE* file = fopen("resultados.csv", "r");
    int header = (file == NULL);
    if (file) fclose(file);

    FILE* csv = fopen("resultados.csv", "a");
    if (header) {
        fprintf(csv, "Metodo,Densidad,Nx,Ny,Nz,M,x_bar,y_bar,z_bar,Tiempo\n");
    }

    if (metodo == 1) {
        fprintf(csv, "%s,%s,%d,%d,%d,%.10f,%.6f,%.6f,%.6f,%.6f\n",
                metodo_str, densidad_str, nx, ny, nz, M, x_bar, y_bar, z_bar, tiempo);
    } else {
        fprintf(csv, "%s,%s,%d,%d,%d,%.10f,%.6f,%.6f,%.6f,%.6f\n",
                metodo_str, densidad_str, N, N, N, M, x_bar, y_bar, z_bar, tiempo);
    }
    fclose(csv);

    printf("\n=== RESULTADOS ===\n");
    printf("Masa total: %.10f\n", M);
    printf("Centro de masa: (%.6f, %.6f, %.6f)\n", x_bar, y_bar, z_bar);
    printf("Tiempo: %.6f s\n", tiempo);
    printf("Resultados guardados en 'resultados.csv'\n");

    return 0;
}
