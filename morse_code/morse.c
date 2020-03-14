
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
#define     BIT(X)          (1 << X)


struct node_struct{
    uint8_t val;
    struct node_struct*dit, *dah;
};

struct node_struct* morse_map;
uint8_t readBuff[MAX_BUFFER_SIZE];
uint8_t EncodeBuffer[MAX_BUFFER_SIZE];
typedef enum    state_enum{
    idle=0,
    state_1_1,
    state_2_1,
    state_3_1,
    state_1_0,
    state_2_0,
    state_3_0,
    state_4_0,
    state_5_0,
    state_6_0,
    state_7_0,
}state_t;
uint32_t     char_morse;
uint8_t char_alphabet;
uint8_t     bit_count=0, gap_count=0;
// struct node_struct* morse_map_read();
int morse_map_read(struct node_struct **map);
int morse_map_print(struct node_struct *map);
uint8_t morse_to_alphabet(uint32_t morse_code, struct node_struct *map, uint8_t count);
int morse_encode_read(uint8_t* buf);
int main(void)
{
    int i = 0;
    uint8_t c;
    state_t state = idle, state_prev = idle;
    uint8_t wordOffset = 0;
    // morse_map = morse_map_read();
    printf("Reading Morse Rules...\n");
    morse_map_read(&morse_map);
    // morse_map_print(morse_map);
    int fd = open("/home/khoa/CodeDao/morse_code/encoded_text.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("Error: Cannot open file\n");
        return -1;
    }
    printf("Decoding your data...\n");
    size_t readSize = read(fd, EncodeBuffer, MAX_BUFFER_SIZE);
    // close(fd);

    printf("Here is the message:\n");
    printf(">>Start\n");
    while(readSize > 0)
    {
        while(i < readSize+1)
        {
            // scanf("%c", &c);
            c = EncodeBuffer[i];
            if(c == '1')
            {
                if(state == idle)
                {
                    state = state_1_1;
                }
                else if(state == state_1_1)
                {
                    state = state_2_1;
                }
                else if(state == state_2_1)
                {
                    state = state_3_1;
                }
                else if(state == state_3_1)
                {
                    state = state_1_1;
                    //write dah
                    // printf("-");
                    char_morse |= BIT(bit_count);
                    bit_count++;
                    
                }else if(state == state_1_0)
                {
                    state = state_1_1;
                }
                else if(state == state_2_0)
                {
                    state = state_1_1;
                    bit_count = 0;
                    char_morse = 0;
                }
                else if(state == state_3_0)
                {
                    state = state_1_1;
                    //print char
                    // printf("%d", char_morse);
                    uint8_t tmp = morse_to_alphabet(char_morse, morse_map, bit_count);
                    printf("%c", tmp);
                    bit_count = 0;
                }
                else if(state == state_4_0)
                {
                    state = state_1_1;
                    bit_count = 0;
                    char_morse = 0;
                }
                else if(state == state_5_0)
                {
                    state = state_1_1;
                    bit_count = 0;
                    char_morse = 0;
                }
                else if(state == state_6_0)
                {
                    state = state_1_1;
                    bit_count = 0;
                    char_morse = 0;
                }
                else if(state == state_7_0)
                {
                    state = state_1_1;
                    //print space
                    uint8_t tmp = morse_to_alphabet(char_morse, morse_map, bit_count);
                    printf("%c", tmp);
                    printf(" ");
                    char_morse = 0;
                    bit_count = 0;
                }
            }   
            else if(c == '0')
            {
                if(state == idle)
                {
                    state = state_1_0;
                }
                if(state == state_1_1 || state == state_2_1)
                {
                    if(state == state_1_1)
                    {
                        //write dit
                        // printf(".");
                        char_morse &=  ~BIT(bit_count);
                        bit_count++;
                    }
                    else{
                        bit_count = 0;
                        char_morse = 0;
                    }
                    state = state_1_0;
                }
                else if(state == state_3_1)
                {
                    state = state_1_0;
                    //write dah
                    // printf("-");
                    char_morse |= BIT(bit_count);
                    bit_count++;
                }
                else if(state == state_1_0)
                {
                    state = state_2_0;
                }
                else if(state == state_2_0)
                {
                    state = state_3_0;
                }
                else if(state == state_3_0)
                {
                    state = state_4_0;
                }
                else if(state == state_4_0)
                {
                    state = state_5_0;
                }
                else if(state == state_5_0)
                {
                    state = state_6_0;
                }
                else if(state == state_6_0)
                {
                    state = state_7_0;
                }
                else if(state == state_7_0)
                {
                    state = state_1_0;
                    //write space
                    uint8_t tmp = morse_to_alphabet(char_morse, morse_map, bit_count);
                    printf("%c", tmp);
                    printf(" ");
                    char_morse = 0;
                    bit_count = 0;
                }
                else{
                    //do nothing
                }
            }   
            else
            {
                //do nothing
                if(c == '\n')
                {
                    state = idle;
                    
                    uint8_t tmp = morse_to_alphabet(char_morse, morse_map, bit_count);
                    char_morse = 0; bit_count = 0;
                    printf("%c\n", tmp);
                    // printf("\n");
                    // return 0;
                }
            }
            i++;  
        }
        if(bit_count > 0)
            lseek(fd, -bit_count, SEEK_CUR);
        bit_count = 0;
        state = idle;
        char_morse = 0;
        readSize = read(fd, EncodeBuffer, MAX_BUFFER_SIZE);
        i = 0;
        // printf("readSize=%ld\n", readSize);
    }
    // printf("Bit count=%d\n", bit_count);
    printf(">>End\n");
    printf("Decoding completed!\n");
    return 0;
}
int morse_encode_read(uint8_t* buf)
{
    int fd = open("/home/khoa/CodeDao/morse_code/encoded_text.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("Error: Cannot open file\n");
        return -1;
    }
    size_t readSize = read(fd, buf, MAX_BUFFER_SIZE);
    if(readSize >= MAX_BUFFER_SIZE)
    {
        printf("Warning: too much data\n");
        return -2;
    }
    close(fd);
    return 0;
}
int morse_map_print(struct node_struct*map)
{
    if(map == NULL)
    {
        //printf("error\n");
        return 0;
    }
    if(map->val != 0)
        printf("%c", map->val);
    morse_map_print(map->dit);
    morse_map_print(map->dah);
    return 0;
}

uint8_t morse_to_alphabet(uint32_t morse_code, struct node_struct *map, uint8_t count)
{
    uint8_t tmp = 0;
    int i;
    struct node_struct* ptr = map;
    for(i = 0; i < count; i++)
    {
        if(morse_code & BIT(i))
        {
            //dah
            ptr = ptr->dah;
        }
        else
        {
            //dit
            ptr = ptr->dit;
        }
    }
    tmp = ptr->val;
    return tmp;
}

// struct node_struct* morse_map_read()
// {
//     struct node_struct* map = (struct node_struct*)malloc(sizeof(struct node_struct));
//     // map = morse_map;
//     map->dit = NULL; map->dah = NULL;
//     map->val = 0;
//     int fd = open("/home/khoa/CodeDao/morse_code/morse_map.txt", O_RDONLY);
//     if(fd < 0)
//     {
//         printf("Error open file\n");
//         return NULL;
//     }
//     size_t readSize = read(fd, readBuff, MAX_BUFFER_SIZE);
//     if(readSize >= MAX_BUFFER_SIZE)
//     {
//         printf("Warning, too much mapping rules\n");
//         return NULL;
//     }
//     int i;
//     uint8_t tmpVal, state_read_buff = 0;
//     struct node_struct *cur = map;
//     for(i = 0; i < readSize; i++)
//     {
//         uint8_t newData = readBuff[i];
//         if(newData != '\n')
//         {
//             if(state_read_buff == 0)
//             {
//                 tmpVal = newData;
//                 state_read_buff = 1;
//             }
//             else
//             {
//                 if(newData == '0')
//                 {
//                     if(cur->dit == NULL)
//                     {
//                         struct node_struct *newNode = (struct node_struct*)malloc(sizeof(struct node_struct));
//                         newNode->val = 0;
//                         newNode->dit = NULL; newNode->dah = NULL;
//                         cur->dit = newNode;
//                         cur = newNode;
//                     }
//                     else{
//                         cur = cur->dit;
//                     }
//                 }
//                 else if (newData == '1')
//                 {
//                     if(cur->dah == NULL)
//                     {
//                         struct node_struct *newNode = (struct node_struct*)malloc(sizeof(struct node_struct));
//                         newNode->val = 0;
//                         newNode->dit = NULL; newNode->dah =NULL;
//                         cur->dah = newNode;
//                         cur = newNode;
//                     }
//                     else
//                     {
//                         cur = cur->dah;
//                     }
//                 }
//                 else
//                 {
//                     //do nothing
//                 }   
//             }
//         }
//         else{
//             cur->val = tmpVal;
//             cur = map;
//             state_read_buff = 0;
//         } 
//     }
//     close(fd);
//     return map;
// }


int morse_map_read(struct node_struct **map)
{
    *map = (struct node_struct*)malloc(sizeof(struct node_struct));
    // map = morse_map;
    (*map)->dit = NULL; (*map)->dah = NULL;
    (*map)->val = 0;
    int fd = open("/home/khoa/CodeDao/morse_code/morse_map.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("Error open file\n");
        return -1;
    }
    size_t readSize = read(fd, readBuff, MAX_BUFFER_SIZE);
    if(readSize >= MAX_BUFFER_SIZE)
    {
        printf("Warning, too much mapping rules\n");
        return -2;
    }
    int i;
    uint8_t tmpVal, state_read_buff = 0;
    struct node_struct *cur = *map;
    for(i = 0; i < readSize; i++)
    {
        uint8_t newData = readBuff[i];
        if(newData != '\n')
        {
            if(state_read_buff == 0)
            {
                tmpVal = newData;
                state_read_buff = 1;
            }
            else
            {
                if(newData == '0')
                {
                    if(cur->dit == NULL)
                    {
                        struct node_struct *newNode = (struct node_struct*)malloc(sizeof(struct node_struct));
                        newNode->val = 0;
                        newNode->dit = NULL; newNode->dah = NULL;
                        cur->dit = newNode;
                        cur = newNode;
                    }
                    else{
                        cur = cur->dit;
                    }
                }
                else if (newData == '1')
                {
                    if(cur->dah == NULL)
                    {
                        struct node_struct *newNode = (struct node_struct*)malloc(sizeof(struct node_struct));
                        newNode->val = 0;
                        newNode->dit = NULL; newNode->dah =NULL;
                        cur->dah = newNode;
                        cur = newNode;
                    }
                    else
                    {
                        cur = cur->dah;
                    }
                }
                else
                {
                    //do nothing
                }   
            }
        }
        else{
            cur->val = tmpVal;
            cur = *map;
            state_read_buff = 0;
        } 
    }
    close(fd);
    return 0;
}