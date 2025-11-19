CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -Iinclude
LIBS = -lm

OBJ = obj/main.o obj/integracion.o obj/densidades.o
TARGET = triple_integral

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj $(TARGET) resultados.csv

.PHONY: clean
