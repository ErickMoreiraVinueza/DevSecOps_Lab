#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ejecutar_mantenimiento(char *input_usuario) {
    char comando[256];
    
    // VULNERABILIDAD CRÍTICA (CWE-78): OS Command Injection
    // Se Concatena input del usuario directo al sistema sin sanitizar, se deberia detectar el patrón 'sprintf' + 'system' + 'char'
    sprintf(comando, "ping -c 4 %s", input_usuario);
    
    printf("Ejecutando diagnóstico en: %s\n", input_usuario);
    
    system(comando); 
}

int main() {
    ejecutar_mantenimiento("8.8.8.8; rm -rf /"); 
    return 0;
}