#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#define     MAX_BUFFER_SIZE 1024
#define     MAX_MORSE_LEN   5
#define     CHAR_SEP        3
#define     WORD_SEP        7
#define     ASCII_SIZE      128
#define     BIT(X)          (1 << X)
#define     DIT             "1"
#define     DAH             "111"
#define     CSEP            "000"
#define     WSEP            "0000000"

uint8_t RdBuffer[MAX_BUFFER_SIZE];
uint8_t WrBuffer[MAX_BUFFER_SIZE];
int encoded_buff_count = 0;
uint16_t    wr_buf_count = 0;
typedef struct node_struct{
    uint32_t val;
    uint8_t count;
}node_t;
node_t  morse_map[ASCII_SIZE];
int morse_map_read(int, node_t *map);
int morse_encode(int fdOrg,int fdEnc, uint8_t *origin_buff, uint8_t *encoded_buff, node_t *map);
int morse_write_file(int fd, uint8_t *encoded_buff);
int main(void)
{
    int fdEncoded, fdOrg, fdMorse;
    fdOrg = open("/home/khoa/CodeDao/morse_code/original_text.txt", O_RDONLY);
    fdEncoded = open("/home/khoa/CodeDao/morse_code/encoded_text.txt", O_CREAT | O_WRONLY | O_TRUNC, 
                        S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    fdMorse = open("/home/khoa/CodeDao/morse_code/morse_map.txt", O_RDONLY);
    
    int orgRdSize, encWrSize;
    printf("Reading Morse Rules...\n");
    morse_map_read(fdMorse, morse_map);
    printf("Encoding your data...\n");
    morse_encode(fdOrg,fdEncoded, RdBuffer, WrBuffer, morse_map);
    // int i;
    // for (i =0; i < encoded_buff_count +1 ; i++)
    //     printf("%c", WrBuffer[i]);
    // printf("\n");
    //encWrSize = morse_write_file(fdEncoded, WrBuffer);
    printf("Encoding success.\n");
    return 0;
}

int morse_write_file(int fdEncoded, uint8_t *encoded_buff)
{
    size_t writeSize = write(fdEncoded, encoded_buff, encoded_buff_count);
    if(writeSize < encoded_buff_count)
    {
        printf("Error: partial write\n");
        return -1;
    }
    encoded_buff_count = 0;
    return writeSize;
}
int morse_encode(int fdOrg,int fdEncoded, uint8_t *origin_buff, uint8_t *encoded_buff, node_t *map)
{
    if(fdOrg < 0)
    {
        printf("Error: Open origin file\n");
        return -1;
    }
    size_t readSize = read(fdOrg, origin_buff, MAX_BUFFER_SIZE);
    // if(readSize >= MAX_BUFFER_SIZE)
    // {
    //     printf("Warning: Too much text\n");
    //     // return -2;
    // }
    while(readSize > 0)
    {
        int i, j, k;
        for(i = 0; i < readSize; i++)
        {
            if(encoded_buff_count >= MAX_BUFFER_SIZE)
                morse_write_file(fdEncoded, encoded_buff);
            uint8_t newData = origin_buff[i];
            if(newData == '\n')
            {
                encoded_buff[encoded_buff_count++] = '\n';
            }
            else if(newData != ' ')
            {
                uint32_t tmpMorse = map[newData].val;
                uint8_t tmpCount = map[newData].count;
                for(j  = 0; j < (int)tmpCount; j++)
                {
                    if(tmpMorse & BIT(j))
                    {
                        for(k = 0; k < 3; k++)
                        {
                            encoded_buff[encoded_buff_count++] = '1';
                        }
                        encoded_buff[encoded_buff_count++] = '0';

                    }
                    else
                    {
                        encoded_buff[encoded_buff_count++] = '1';
                        encoded_buff[encoded_buff_count++] = '0';
                    }              
                }
                encoded_buff[encoded_buff_count++] = '0';
                encoded_buff[encoded_buff_count++] = '0';
            }
            else{
                for(k = 0; k < 4; k++)
                {
                    encoded_buff[encoded_buff_count++] = '0';
                }
            }
        }
        encoded_buff[encoded_buff_count++] = '\n';
        // close(fdOrg);
        if(encoded_buff_count > 0)
        {
            morse_write_file(fdEncoded, encoded_buff);
        }
        readSize = read(fdOrg, origin_buff, MAX_BUFFER_SIZE);
    }
    return readSize;
}
int morse_map_read(int fdMorse, node_t *map)
{
    size_t readSize = read(fdMorse, RdBuffer, MAX_BUFFER_SIZE);
    // if(readSize >= MAX_BUFFER_SIZE)
    // {
    //     printf("Warning: too much rules\n");
    //     return -2;
    // }
    if(fdMorse < 0)
    {
        printf("Error: open file\n");
        return -1;
    }
    int i;
    uint8_t tmpVal = 0, state_read_buff = 0, bitCount = 0;
    uint32_t tmpMorse = 0;
    for(i = 0; i < readSize; i++)
    {
        uint8_t newData = RdBuffer[i];
        if(newData != '\n')
        {
            if(state_read_buff == 0)
            {
                tmpVal = newData;
                state_read_buff = 1;
            }
            else{
                if(newData == '0')
                {
                    tmpMorse &= ~BIT(bitCount);
                    bitCount++;
                }
                else if(newData == '1')
                {
                    tmpMorse |= BIT(bitCount);
                    bitCount++;
                }
                else{
                    //do nothing
                }
            }
        }
        else{
            state_read_buff = 0;
            map[tmpVal].val = tmpMorse;
            map[tmpVal].count = bitCount;
            bitCount = 0;
            tmpMorse = 0;
        }
    }
    // close(fdMorse);
    return readSize;
}