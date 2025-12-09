#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * CÓDIGO INTENCIONALMENTE INSEGURO
 * Objetivo: Disparar CWE-121 (Stack-based Buffer Overflow) por encima del 75%.
 *
 * Patrones incluidos:
 *  - strcpy sin límites
 *  - strcat sin límites
 *  - gets()
 *  - scanf("%s") sin ancho máximo
 *  - sprintf() a buffers pequeños
 *  - buffers demasiado pequeños para los datos esperados
 */

struct Student {
    char first_name[10];
    char last_name[10];
    char student_id[8];
    char bio[50];
};

void overflow_name(char *raw_input, struct Student *s) {
    // VULNERABILIDAD A: strcpy en buffer local pequeño
    char name_buffer[8];
    strcpy(name_buffer, raw_input);           // posible overflow
    strcpy(s->first_name, name_buffer);       // otro overflow potencial
}

void overflow_lastname(char *raw_input, struct Student *s) {
    // VULNERABILIDAD B: doble copia insegura
    char last_buffer[6];
    strcpy(last_buffer, raw_input);           // overflow casi garantizado
    strcpy(s->last_name, last_buffer);
}

void overflow_id(char *raw_input, struct Student *s) {
    // VULNERABILIDAD C: strcat en buffer muy pequeño
    char id_buffer[8] = "ID:";
    strcat(id_buffer, raw_input);             // buffer fijo + strcat = CWE-121
    strcpy(s->student_id, id_buffer);
}

void overflow_bio_gets(struct Student *s) {
    // VULNERABILIDAD D: gets()
    char bio_buffer[30];
    printf("Enter bio (inseguro): ");
    gets(bio_buffer);                         // clásica bomba de overflow
    strcpy(s->bio, bio_buffer);               // copia sin validar
}

void overflow_report(struct Student *s, char *extra) {
    // VULNERABILIDAD E: formato inseguro + strcat
    char header[10] = "REP:";
    char report[32];
    char tail[10] = ":END";

    strcpy(report, header);
    strcat(report, s->first_name);
    strcat(report, s->last_name);
    strcat(report, extra);
    strcat(report, tail);

    printf("INSECURE REPORT: %s\n", report);
}

void overflow_loop(char **lines, int count) {
    // VULNERABILIDAD F: bucle de copias a buffer ridículo
    for (int i = 0; i < count; i++) {
        char tiny[4];
        strcpy(tiny, lines[i]);               // overflow casi siempre
    }
}

void overflow_debug_format(char *raw_input) {
    // VULNERABILIDAD G: sprintf sin límite a buffer pequeño
    char debug_msg[16];
    sprintf(debug_msg, "DBG:%s", raw_input);  // sin control de tamaño
    printf("%s\n", debug_msg);
}

void overflow_scan(struct Student *s) {
    // VULNERABILIDAD H: scanf sin especificador de tamaño
    char local_buffer[12];
    printf("Legacy scan (inseguro): ");
    scanf("%s", local_buffer);                // sin límite -> CWE-121
    strcpy(s->first_name, local_buffer);
}

void parse_csv_line_insecure(char *line) {
    struct Student current_student;
    char debug_buffer[20];

    // VULNERABILIDAD I: copia directa sin validar longitud
    strcpy(debug_buffer, line);

    // Encadenamiento de vulnerabilidades
    overflow_name(line, &current_student);
    overflow_lastname(line, &current_student);
    overflow_id(line, &current_student);
    overflow_bio_gets(&current_student);

    overflow_report(&current_student, line);

    char *batch[3] = { line, debug_buffer, current_student.bio };
    overflow_loop(batch, 3);

    overflow_debug_format(line);
    overflow_scan(&current_student);
}

void insecure_env_processing() {
    // VULNERABILIDAD J: leer env var sin validar y copiar a buffers pequeños
    char env_buffer[32];
    char small[8];

    char *env = getenv("INSECURE_ENV");
    if (env != NULL) {
        strcpy(env_buffer, env);              // posible overflow
        strcpy(small, env_buffer);            // otro overflow
    }
}

int main(int argc, char *argv[]) {
    // VULNERABILIDAD K: copia de argumento sin verificar longitud
    char command_line_buffer[32];

    if (argc > 1) {
        strcpy(command_line_buffer, argv[1]);
        parse_csv_line_insecure(command_line_buffer);
    }

    // VULNERABILIDAD L: segunda entrada con gets()
    char extra_line[64];
    printf("Extra CSV (legacy inseguro): ");
    gets(extra_line);
    parse_csv_line_insecure(extra_line);

    // VULNERABILIDAD M: procesar variables de entorno de forma insegura
    insecure_env_processing();

    return 0;
}
