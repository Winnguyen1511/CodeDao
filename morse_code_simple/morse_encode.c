#include <stdio.h>
#include <stdint.h>
const char *input_file = "original.txt";
const char *output_file = "encoded.txt";
const char *morse_char[] = {".-", "-...", "-.-.","-..",
                            ".", "..-.", "--.", "....", "..",
                            ".---","-.-", ".-..", "--", "-.",
                            "---", ".--.", "--.-",".-.","...",
                            "-","..-","...-",".--","-..-","-.--", "--.."};
const char *morse_num[] = {"-----", ".----", "..---","...--",
                            "....-", ".....", "-....", "--...",
                            "---..", "----."};


int main(void)
{
    FILE *fpInput = fopen(input_file, "r");
    FILE *fpEncode = fopen(output_file, "w");
    char c;
    while(!feof(fpInput))
    {
        c = fgetc(fpInput);
        if(c >= 'a' && c <= 'z')
        {
            fprintf(fpEncode,"%s ", morse_char[c - 'a']);                   
        }
        else if(c >= '0' && c <= '9')
        {
            fprintf(fpEncode,"%s ", morse_num[c - '0']);    
        }
        else if(c == ' ')
        {
            fputc('/', fpEncode);
        }
        else if(c == '\n')
        {
            fputc('\n', fpEncode);
        }
        else{
            //printf("");
        }  
    }
    fclose(fpInput);
    fclose(fpEncode);
    return 0;
}
