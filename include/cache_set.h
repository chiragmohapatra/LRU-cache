#pragma once

#include <vector>
#include "cache_block.h"

using namespace std;

class cache_set{
    public:
        vector<cache_block*> high_priority_blocks;
        vector<cache_block*> low_priority_blocks;

        cache_set();
        ~cache_set();
        bool write_in_set(int tag , int set_index , int data);
        bool read_from_set(int tag , int set_index);
        void update_lru(int i); // i is the most recently used index , lru is for the high priority group
        void move_to_high_priority(int i);  // move index ith element of low priority to high priority list
        void update_last_used_times();  // decrement the last used times of the blocks
        void move_to_low_priority(int i);  // move index ith element of high priority to low priority list
        void insert_block(int tag , int set_index);     // insert block with tag to the set
        void update_memory(int set_index);  // update main memory , if block is dirty , then we update the data
        void display_set();

};