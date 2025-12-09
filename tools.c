#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* CÓDIGO INTENCIONALMENTE INSEGURO PARA DISPARAR CWE-121 (Stack-based Buffer Overflow)
   Se añaden más patrones clásicos:
   - strcpy / strcat sin límites
   - gets()
   - sprintf() a buffers pequeños
   - scanf("%s") sin ancho máximo
*/

struct Student {
    char first_name[10];
    char last_name[10];
    char student_id[8];
    char bio[50];
};

void process_name(char *raw_input, struct Student *s) {
    // VULNERABILIDAD 1
    char temp_buffer[10];
    strcpy(temp_buffer, raw_input); 
    strcpy(s->first_name, temp_buffer);
}

void process_lastname(char *raw_input, struct Student *s) {
    // VULNERABILIDAD 2
    char temp_buffer[10];
    strcpy(temp_buffer, raw_input);
    strcpy(s->last_name, temp_buffer);
}

void process_id(char *raw_input, struct Student *s) {
    // VULNERABILIDAD 3: strcat en buffer fijo muy pequeño
    char id_buffer[8] = "ID:";
    strcat(id_buffer, raw_input); 
    strcpy(s->student_id, id_buffer);
}

void process_bio_legacy(struct Student *s) {
    // VULNERABILIDAD 4: gets()
    char bio_buffer[50];
    printf("Enter bio: ");
    gets(bio_buffer); 
    
    // VULNERABILIDAD 5: strcpy sin validar
    strcpy(s->bio, bio_buffer);
}

void legacy_report(struct Student *s, char *extra) {
    // VULNERABILIDAD 6: cadena de reportes insegura
    char header[10] = "STU:";
    char report[30];
    char tail[10] = "-END";

    strcpy(report, header);          // copia inicial
    strcat(report, s->first_name);   // concat sin comprobar longitud
    strcat(report, s->last_name);    // sigue concatenando
    strcat(report, extra);           // más datos de entrada
    strcat(report, tail);            // remate final

    printf("REPORT: %s\n", report);
}

void unsafe_copy_loop(char **lines, int count) {
    // VULNERABILIDAD 7: bucle copiando a un buffer ridículamente pequeño
    for (int i = 0; i < count; i++) {
        char tiny[5];
        strcpy(tiny, lines[i]);  // cualquier string >4 chars desborda
    }
}

void debug_formatting(char *raw_input) {
    // VULNERABILIDAD 8: sprintf hacia buffer pequeño
    char debug_msg[20];
    sprintf(debug_msg, "DBG:%s", raw_input); // sin límite de tamaño
    printf("%s\n", debug_msg);
}

void legacy_scan(struct Student *s) {
    // VULNERABILIDAD 9: scanf sin especificador de tamaño
    char local_buffer[15];
    printf("Legacy scan: ");
    scanf("%s", local_buffer);       // no limita lo que entra
    strcpy(s->first_name, local_buffer);
}

void parse_csv_line(char *line) {
    struct Student current_student;
    char debug_buffer[20];

    // VULNERABILIDAD 10
    strcpy(debug_buffer, line);
    
    // Cadena original de vulnerabilidades
    process_name(line, &current_student);
    process_lastname(line, &current_student);
    process_id(line, &current_student);
    process_bio_legacy(&current_student);

    // NUEVOS encadenamientos inseguros
    legacy_report(&current_student, line);

    char *batch[3] = { line, debug_buffer, current_student.bio };
    unsafe_copy_loop(batch, 3);

    debug_formatting(line);
    legacy_scan(&current_student);
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    // VULNERABILIDAD 11: copia de argumento sin verificar longitud
    char command_line_buffer[100];
    strcpy(command_line_buffer, argv[1]);

    parse_csv_line(command_line_buffer);
    
    // VULNERABILIDAD 12: otro modo interactivo usando gets()
    char extra_line[60];
    printf("Extra CSV (legacy): ");
    gets(extra_line);
    parse_csv_line(extra_line);
    
    return 0;
}
