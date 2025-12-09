#include <string.h>
#include <stdio.h>

void bad_function(char *input) {
    char small_buffer[8];
    strcpy(small_buffer, input); /* CWE121 */
    printf("%s\n", small_buffer);
}

int main(int argc, char *argv[]) {
    char local_buffer[10];
    strcpy(local_buffer, argv[1]); /* CWE121 */
    bad_function(argv[1]);
    return 0;
}
