#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ESTE CÓDIGO ESTÁ DISEÑADO PARA DISPARAR CWE-121 (Stack-based Buffer Overflow).
   Usa repetidamente funciones inseguras de manejo de strings (strcpy, strcat, gets).
   El objetivo es saturar el vectorizador TF-IDF con tokens de riesgo.
*/

struct Student {
    char first_name[10];
    char last_name[10];
    char student_id[8];
    char bio[50];
};

void process_name(char *raw_input, struct Student *s) {
    // VULNERABILIDAD 1: strcpy sin validación
    // El modelo detectará el patrón: char[] + strcpy
    char temp_buffer[10];
    strcpy(temp_buffer, raw_input); 
    strcpy(s->first_name, temp_buffer);
}

void process_lastname(char *raw_input, struct Student *s) {
    // VULNERABILIDAD 2: Otra instancia de strcpy inseguro
    char temp_buffer[10];
    strcpy(temp_buffer, raw_input);
    strcpy(s->last_name, temp_buffer);
}

void process_id(char *raw_input, struct Student *s) {
    // VULNERABILIDAD 3: strcat sin limites
    // Concatenar en un buffer fijo es un patrón clásico de CWE-121
    char id_buffer[8] = "ID:";
    strcat(id_buffer, raw_input); 
    strcpy(s->student_id, id_buffer);
}

void process_bio_legacy(struct Student *s) {
    // VULNERABILIDAD 4: La "bomba" gets()
    // Esta función por sí sola tiene un peso enorme en datasets como SARD/SecureC
    char bio_buffer[50];
    printf("Enter bio: ");
    gets(bio_buffer); 
    
    // VULNERABILIDAD 5: Copia insegura final
    strcpy(s->bio, bio_buffer);
}

void parse_csv_line(char *line) {
    struct Student current_student;
    char debug_buffer[20];

    // VULNERABILIDAD 6: Copia local insegura para debug
    strcpy(debug_buffer, line);
    
    // Procesamiento en cadena de vulnerabilidades
    process_name(line, &current_student);
    process_lastname(line, &current_student);
    process_id(line, &current_student);
    process_bio_legacy(&current_student);
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    // VULNERABILIDAD 7: Copia de argumento de línea de comandos sin verificar longitud
    char command_line_buffer[100];
    strcpy(command_line_buffer, argv[1]);

    parse_csv_line(command_line_buffer);
    
    return 0;
}




