#include <string.h>
#include <stdio.h>

void CWE121_Stack_Based_Buffer_Overflow__CWE193_char_alloca_loop_01_bad()
{
    char * data;
    char dataBadBuffer[10];
    data = dataBadBuffer;

    char source[20] = "AAAAAAAAAAAAAAAAAAAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    strcpy(data, source); /* CWE121 */
    printf("%s\n", data);
}

int main(int argc, char * argv[])
{
    char localBuffer[10];
    strcpy(localBuffer, argv[1]); /* CWE121 */
    CWE121_Stack_Based_Buffer_Overflow__CWE193_char_alloca_loop_01_bad();
    return 0;
}
