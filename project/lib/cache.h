#ifndef CACHE_H
#define CACHE_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "memory_generic.h"

#define SUCCESS     0
#define ERROR       -1

#define TRUE    0
#define FALSE   -1

typedef enum command_enum {
    READ_DATA=0,
    WRITE_DATA,
    INSTRUCTION_FETCH,
    EVICT,
    CLEAR_CACHE=8,
    PRINT_CONTENT
}command_t;

typedef enum return_enum {
    READ_HIT=0,
    READ_MISS,
    WRITE_HIT,
    WRITE_MISS,
    EVICT_OK,
    EVICT_ERROR
}return_t;

typedef struct line_struct {
    uint16_t tag_array;
    uint8_t* data; 
}line_t;

typedef struct set_struct {
    line_t* lines;
}set_t;

typedef struct cache_struct {
    int sets_num;
    int ways_assoc;
    int line_size;
    set_t* sets;
}cache_t;


typedef struct cache_stat_struct {
    int count;
    char*name;
    int mode;
    FILE *log_file;
    int read_hits;
    int read_misses;
    int write_hits;
    int write_misses;
    double hit_rate;
}cache_stat_t;
cache_t* create_cache(int sets_num, int ways_assoc, int line_size);
set_t* create_set(int ways_assoc);
line_t* create_line(int line_size);

//Return cache read hit/miss:
int cache_L1_read(cache_t* cache, uint32_t address, uint8_t*ret);
//Return cache write hit/miss:
int cache_L1_write(cache_t* cache, uint32_t address, uint8_t data);
//Clear cache:
int cache_L1_clear(cache_t* cache, cache_stat_t* stat);
int get_invalidate_cache(uint32_t address);
//
int cache_L2_evict(cache_t* cache, uint32_t address);

//For simulate L2 cache reference:
int cache_L2_read(void);
int cache_L2_write(void);

//Log activity:
int cache_stat_update(cache_stat_t*stat, return_t update);
int cache_log(cache_stat_t stat);
int clear_stat(cache_stat_t *stat);

#endif
