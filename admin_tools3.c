#include <string.h>
#include <stdio.h>

// VULNERABILIDAD CRÍTICA: CWE-119 (Stack-based Buffer Overflow)
// Debe rechazar 'strcpy' cuando no se verifica el tamaño
void actualizar_config(char *input_externo) {
    char buffer_pequeno[10];
    
    // Aqui se Copia sin limites. Este es el problema
    strcpy(buffer_pequeno, input_externo);
}

int main() {
    actualizar_config("Texto_demasiado_largo_para_el_buffer");
    return 0;
}