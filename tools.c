#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ESTE ARCHIVO ESTÁ DISEÑADO PARA ROMPER EL UMBRAL DE LA IA
// Combina las 4 funciones más odiadas por los modelos de seguridad.

void codigo_toxico(char *input) {
    char buffer[10];
    char comando[50];

    // 1. La bomba nuclear: gets (CWE-119)
    // El modelo TF-IDF le da un peso altísimo a esta palabra.
    gets(buffer); 

    // 2. El clásico: strcpy (CWE-119)
    // Refuerza la predicción de Buffer Overflow.
    strcpy(buffer, input);

    // 3. Concatenación insegura: strcat (CWE-119/120)
    strcat(buffer, "bad_data");

    // 4. Inyección de comandos: system (CWE-78)
    // Activa también las neuronas de "Injection" del modelo.
    sprintf(comando, "echo %s", buffer);
    system(comando); 
}

int main() {
    codigo_toxico("ataque_total");
    return 0;
}