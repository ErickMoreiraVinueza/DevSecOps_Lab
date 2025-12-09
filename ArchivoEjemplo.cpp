#include <stdio.h>
#include <string.h>

// ESTE CÓDIGO ES INTENCIONALMENTE INSEGURO
// Usa 'gets', que es la función más peligrosa en la historia de C.
// La IA debería darle una probabilidad cercana al 99%.

void funcion_prohibida() {
    char buffer_pequeno[8];
    
    printf("Introduce datos: ");
    
    // PELIGRO EXTREMO: gets() no verifica límites.
    // Es imposible usar esta función de forma segura.
    // El modelo TF-IDF asociará la palabra "gets" con vulnerabilidad inmediatamente.
    gets(buffer_pequeno); 
    
    // Y para asegurar, añadimos un strcpy inseguro también
    char otro_buffer[8];
    strcpy(otro_buffer, buffer_pequeno);
}

int main() {
    funcion_prohibida();
    return 0;
}





