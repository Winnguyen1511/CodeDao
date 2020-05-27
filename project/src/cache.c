#include "cache.h"

cache_t* create_cache(int sets_num, int ways_assoc, int line_size)
{
    return NULL;
}
set_t* create_set(int ways_assoc)
{
    return NULL;
}
line_t* create_line(int line_size)
{
    return NULL;
}
//Return cache read hit/miss:
int cache_L1_read(cache_t* cache, uint32_t address, uint8_t*ret)
{
    return READ_HIT;
}
//Return cache write hit/miss:
int cache_L1_write(cache_t* cache, uint32_t address, uint8_t data)
{
    return WRITE_HIT;
}

int cache_L1_clear(cache_t* cache, cache_stat_t* stat)
{
    return SUCCESS;
}

int cache_L2_evict(cache_t* cache, uint32_t address)
{
    return EVICT_OK;
}

//For simulate L2 cache reference:
int get_invalidate_cache(uint32_t address)
{
    return 0;
}
int cache_L2_read(void)
{
    return READ_HIT;
}
int cache_L2_write(void)
{
    return WRITE_HIT;
}
int cache_stat_update(cache_stat_t*stat, return_t update)
{
    return SUCCESS;
}
int cache_log(cache_stat_t stat)
{
    return SUCCESS;
}

int clear_stat(cache_stat_t *stat)
{
    if(stat == NULL)
    {
        printf("Error: Stat is null.\n");
        return ERROR;
    }
    stat->read_hits = 0;
    stat->read_misses = 0;
    stat->write_hits = 0;
    stat->write_misses = 0;
    stat->hit_rate = 1;
    return SUCCESS;
}