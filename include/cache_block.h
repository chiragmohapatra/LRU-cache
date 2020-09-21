#pragma once

#include <vector>
#include <utility>

using namespace std;

class cache_block{
    public:
        int tag;    // represents the uniqueness of blocks within the same set
        bool valid_bit;     // true if some data is in block
        bool dirty;     // true if data in block is overwritten
        int time_left;    // initially T when inserted into a high priority group , decrements in each cycle when not accessed again
        int block_data;     // the data in the block

        cache_block();
        cache_block(int tag , int data);
        bool write_in_block(int data);  // write data to the block , true if HIT and false if MISS
        bool read_from_block();     // read from block , true if HIT and false if MISS
        void display_block();   // display the block

};