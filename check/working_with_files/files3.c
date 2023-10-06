#include <stdio.h>
#include <errno.h>

int main(void) {
    
    char str[] = "Function fputc() in action.";

    // char buff[100];

    /* FILE* fp = fopen("my_file.txt", "w");
    if (fp == NULL)
        return 1;

    for(int i = 0; i < str[i]; i++){
        fputc(str[i], fp);
    } */

    FILE* in = fopen("my_file.txt", "w");
        if(in == NULL) {
        printf("errno: %d\n", errno);
        perror("my_file2.txt");
        return 1;
        }
    // fseek(in, 0, SEEK_END);
    // int length = ftell(in);
    
    for(int i = 1; str[i]; ++i){
        fseek(in, 0,SEEK_SET);
        fputc(str[i], in);
    }
        putchar('\n');
        fclose(in);
        // fclose(fp);
    return 0;
}