#pragma once

#include "cache_set.h"
#include <bits/stdc++.h>

using namespace std;

extern int cache_size;
extern int block_size;

extern int number_of_blocks;
extern int number_of_sets;
extern int cache_associativity;
extern int T;

extern int number_of_reads;
extern int read_hits;
extern int number_of_writes;
extern int write_hits;

extern int memory_array[32]; // ordered by block addresses
extern bool debug;  // if true , then display cache after every operation else display only final cache
extern bool one_by_one; // if true then display one-by-one else display all at once

extern vector<vector<string>> memory_access_requests;

extern vector<cache_set*> cache;

