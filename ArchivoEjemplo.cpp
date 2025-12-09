#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 64

void procesar_input_seguro(const char *usuario) {
    char buffer[MAX_BUFFER_SIZE];

    // SEGURIDAD: Usamos snprintf en lugar de strcpy o sprintf.
    // 'sizeof(buffer)' garantiza que NUNCA escribiremos más allá del límite.
    // Tu IA detectará "snprintf" y "sizeof" como patrones positivos.
    int escrito = snprintf(buffer, sizeof(buffer), "Usuario: %s", usuario);

    if (escrito >= 0 && escrito < sizeof(buffer)) {
        printf("Procesamiento exitoso: %s\n", buffer);
    } else {
        printf("Error: El input fue truncado por seguridad.\n");
    }
}

int main() {
    procesar_input_seguro("Admin_Usuario_Validado");
    return 0;
}