#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_STR_LEN     1024
#define DEFAULT_BUFFER_SIZE 128        
#define DEFAULT_WORD_LEN    8
#define DATA_SIZE           sizeof(char)
#define BUFFER_DATA_SIZE    sizeof(char*)
int main(void)
{
    int strLen=0, str_allocated_count = 1, strCap = DEFAULT_STR_LEN;
    int bufLen=0, buf_allocated_count = 1, bufCap = DEFAULT_BUFFER_SIZE, buf_index = 0;
    int wordLen=0, word_allocated_count =1, wordCap = DEFAULT_WORD_LEN, word_index = 0; 
    int word_begin = 0, word_end=0;
    char *inputStr = malloc(strCap* DATA_SIZE);
    char **buffer = malloc(bufCap * BUFFER_DATA_SIZE);
    char *word = malloc(wordCap*DATA_SIZE);
    printf("Enter the string:");
    char tmp;
    //int count = 0;
    for(;;)
    {
        scanf("%c", &tmp);
        if(tmp == '\n' || tmp == '\r')
            break;
        inputStr[strLen++] = tmp;
        check_str_cappacity:
        if(strLen >= strCap)
        {
            inputStr = realloc(inputStr, DEFAULT_STR_LEN*(++str_allocated_count)*DATA_SIZE);
            strCap = DEFAULT_STR_LEN * str_allocated_count;
            if(strLen >= strCap)
                goto check_str_cappacity;
        }
            
    }    
    strLen++;
    for(;word_end < strLen ; word_end++)
    {
        //word = malloc(wordCap * DEFAULT_WORD_LEN);
        if(inputStr[word_end] == ' ' || word_end == strLen-1)
        {
            buffer[bufLen++] = word;
            check_buf_cappacity:
            if(bufLen >= bufCap)
            {
                buffer = realloc(buffer, DEFAULT_BUFFER_SIZE*(++buf_allocated_count)*BUFFER_DATA_SIZE);
                bufCap = DEFAULT_BUFFER_SIZE * buf_allocated_count;
                if(bufLen >= bufCap)
                    goto check_buf_cappacity;
            }
                
            wordLen = 0, word_allocated_count = 1, wordCap = DEFAULT_WORD_LEN;
            word = malloc(wordCap * DEFAULT_WORD_LEN);
            continue;
        }
        word[wordLen++] = inputStr[word_end];
        check_word_cappacity:
        if(wordLen >= wordCap)
        {
            word = realloc(word, DEFAULT_WORD_LEN * (++word_allocated_count)*DATA_SIZE);
            wordCap = DEFAULT_WORD_LEN * word_allocated_count;
            if(wordLen >= wordCap)
                goto check_word_cappacity;
        }
    }
    int i;
    printf("Reverse string:");
    for(i =bufLen - 1; i >= 0; i--)
    {
        printf("%s ", buffer[i]);
    }
    printf("\n");
    free(inputStr); free(buffer); free(word);
    return 0;
}