#include "../include/global.h"

int cache_size = 0;
int block_size = 0;

int number_of_blocks = 0;
int number_of_sets = 0;
int cache_associativity = 0;
int T = 0;

int number_of_reads = 0;
int read_hits = 0;
int number_of_writes = 0;
int write_hits = 0;

bool debug = false;
bool one_by_one = false;
int memory_array[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

vector<vector<string>> memory_access_requests;

vector<cache_set*> cache;