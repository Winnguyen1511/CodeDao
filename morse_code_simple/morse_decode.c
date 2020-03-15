#include <stdio.h>

const char *morse_decode_char = "etianmsurwdkgohvf*l*pjbxcyzq";
char morse_decode_num[32];


const char *input_file = "encoded.txt";
const char *output_file = "decoded.txt";
#define     BIT(X)      (1 << X)
int main(void)
{
    morse_decode_num[0] = '5';morse_decode_num[16] = '6';
    morse_decode_num[1] = '4';morse_decode_num[24] = '7';
    morse_decode_num[3] = '3';morse_decode_num[28] = '8';
    morse_decode_num[7] = '2';morse_decode_num[30] = '9';
    morse_decode_num[15] = '1';morse_decode_num[31] = '0';
    FILE *fpInput = fopen(input_file, "r");
    FILE *fpDecode = fopen(output_file, "w");
    char word[5] = {0};
    int i = 0, tmp= 0;
    char c;

    while(!feof(fpInput))
    {
        c = fgetc(fpInput);
        if(c == '/')
        {
            fputc(' ', fpDecode);

        }
        else if (c == '\n')
        {
            fputc('\n', fpDecode);
        }
        else if (c == ' ' || c == '\n')
        {
            //decode here
            if(i <= 4)
            {
                fputc(morse_decode_char[BIT(i) + tmp - 2], fpDecode);
            }
            else if(i == 5)
            {
                fputc(morse_decode_num[tmp], fpDecode);
            }
            else{
                //do nothing
            }
            i = 0;
            tmp = 0;
        }
        else
        {
            //word[i] = c;
            tmp = tmp << 1;
            if(c == '.')
                tmp &= ~BIT(0);
            else if(c == '-')
                tmp |= BIT(0);
            else
            {
                //do nothing
            }   
                   
            i++;
        }
        
    }
    return 0;
}
