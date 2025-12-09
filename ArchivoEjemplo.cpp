// tools.c - Ejemplo de código seguro
// No contiene funciones inseguras ni patrones de vulnerabilidad comunes

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT 100

// Función segura para leer texto del usuario
void leer_texto_seguro(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) != NULL) {
        // Remover salto de línea
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

int sumar(int a, int b) {
    return a + b;
}

int main(void) {
    char nombre[MAX_INPUT];

    printf("Ingrese su nombre: ");
    leer_texto_seguro(nombre, sizeof(nombre));

    printf("Hola, %s!\n", nombre);

    int x = 5;
    int y = 10;
    printf("La suma es: %d\n", sumar(x, y));

    return 0;
}




