#include <stdio.h>
#include <stdlib.h>

//#define MONODIR
//#define INPUT_MAP     
typedef struct node_struct {
    int this_node;
    int path_len;
    int prev_node;
}node_t;
node_t min_node;
int**map;
//int*min_arr;
int count=0;
int num_node=0, start_node = 0, tmp_node_num;
int* N_prime_set;
int main(void)
{
    int i;
    //num_node = 6;
    num_node = 9;
    map = (int**)malloc((num_node)* sizeof(int*));
    N_prime_set = (int*)malloc(num_node * sizeof(int));
    N_prime_set[0] = -1;
    for(i = 1; i < num_node; i++)
    {
        N_prime_set[i] = 0;
    }
    #ifdef MONODIR
    //do another time :v
    #else
    for(i=1; i < num_node; i++)
    {
        map[i] = (int*)malloc(i * sizeof(int));
    }
    #endif

    #ifdef INPUT_MAP

    #else
    // map[1][0] = 1; map[5][0] = 2;
    // map[2][1] = 4; map[4][1] = 3; map[5][1] = 2;
    // map[3][2] = 2; map[4][2] = 1; map[4][3] = 5;
    // map[5][4] = 1;
    map[1][0] = 4; map[1][7] = 11; map[7][0] = 8;
    map[2][1] = 8; map[8][2] = 2; map[8][7] = 7; map[7][6] = 1;
    map[3][2] = 7; map[5][2] = 4; map[6][5] = 2; map[5][3]=14;
    map[4][3]=4; map[5][4] = 10;

    // if(map[5][4] == NULL)
    //     printf("null\n");
    start_node = 0;
    #endif

    node_t* list = (node_t*)malloc(num_node * sizeof(node_t));
    //Init list
    // min_arr_num_node = num_node;
    // min_arr = (int*)malloc(min_arr_num_node * sizeof(int));
    min_node.path_len = 0;
    min_node.prev_node = 0;
    for(i = 1; i < num_node; i++)
    {
        if(map[i][0] != 0)
        {
            list[i].this_node = i;
            list[i].path_len = map[i][0];
            list[i].prev_node = 0;
            printf("0->%d:len=%d, prev=%d\n", i, list[i].path_len, list[i].prev_node);
            //min_arr_cnt++;
            if(min_node.path_len == 0 || min_node.path_len > list[i].path_len)
            {
                min_node.this_node = i;
                min_node.path_len = list[i].path_len;
                min_node.prev_node = list[i].prev_node;
            }
        }      
    }
    printf("Finished 1st round\n");
    printf("min_node #%d: len=%d, prev=%d\n",min_node.this_node, min_node.path_len, min_node.prev_node);
    N_prime_set[min_node.this_node] = -1;
    tmp_node_num = min_node.this_node;

    count = num_node - 2;
    while(count--)
    {
        min_node.this_node = 0;
        min_node.path_len = 0;
        min_node.prev_node = 0;
        for(i = 1; i < num_node ; i++)
        {
            int map_index=i;
            int swap_tmp = tmp_node_num;
            if(map_index < tmp_node_num)
            {
                map_index = tmp_node_num;
                tmp_node_num = i;
            }
            if(N_prime_set[i] == -1)
            {
                tmp_node_num =swap_tmp;
                continue;
            }
            if(list[i].path_len == 0)
            {
                if(map[map_index][tmp_node_num] != 0)
                {
                    list[i].this_node = i;
                    list[i].path_len = map[map_index][tmp_node_num] + list[swap_tmp].path_len;
                    list[i].prev_node = swap_tmp;
                    if(min_node.path_len == 0 || min_node.path_len > list[i].path_len)
                    {
                        min_node.this_node = i;
                        min_node.path_len = list[i].path_len;
                        min_node.prev_node = list[i].prev_node;                        
                    }
                }
            }
            else{
                int tmp_path_len = list[i].path_len;
                int tmp_prev_node = list[i].prev_node;
                int tmp_this_node = i;
                if(map[map_index][tmp_node_num] != 0)
                {
                    int tmp_val = map[map_index][tmp_node_num] + list[swap_tmp].path_len;

                    if(list[i].path_len < tmp_val)
                    {
                        tmp_path_len = list[i].path_len;
                        tmp_prev_node = list[i].prev_node;
                        tmp_this_node = i;
                    }
                    else{
                        tmp_path_len = tmp_val;
                        tmp_prev_node = swap_tmp;
                        tmp_this_node = i;
                    }
                    list[i].this_node = tmp_this_node;
                    list[i].path_len = tmp_path_len;
                    list[i].prev_node = tmp_prev_node;
                }
                if(min_node.path_len == 0 || min_node.path_len > tmp_path_len)
                {
                    min_node.this_node = tmp_this_node;
                    min_node.path_len = tmp_path_len;
                    min_node.prev_node = tmp_prev_node;                        
                }
            }
            tmp_node_num = swap_tmp;
        }
        N_prime_set[min_node.this_node] = -1;
        tmp_node_num = min_node.this_node;
    }
    for(i = 1; i < num_node; i++)
    {
        printf("#%d: len=%d, prev=%d\n", list[i].this_node, list[i].path_len, list[i].prev_node);
    }

    return 0;
}