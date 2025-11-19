## Temas investigados

### Método de Monte Carlo
- Se usó `rand()` con `srand(time(NULL))` para generar números pseudoaleatorios.
- La "semilla" inicializa el generador; usar `time(NULL)` evita secuencias repetidas.
- El error disminuye como \(1/\sqrt{N}\); mayor \(N\) → mayor precisión.

### Organización modular en C
- Archivos `.h`: declaraciones; `.c`: definiciones.
- Se usaron *include guards* (`#ifndef ... #define ... #endif`) para evitar redefiniciones.
- No se usaron variables globales.

### Programación en C
- Tipos numéricos: `double` para precisión.
- `math.h`: para `exp()`.
- `time.h`: para medir tiempo con `clock()`.
- Archivos: `fopen`, `fprintf`, `fclose`.

### Makefile
- Automatiza compilación y limpieza con `make` y `make clean`.
# Cálculo de masa y centro de masa mediante integración triple

Este programa en C calcula la **masa total** y el **centro de masa** de un cuerpo tridimensional con densidad variable, mediante métodos numéricos: **sumas de Riemann** o **Monte Carlo**.

## Compilación
```bash
make


