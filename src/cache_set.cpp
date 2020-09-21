#include "../include/cache_set.h"
#include "../include/global.h"

cache_set::cache_set(){
    for(int i = 0 ; i < cache_associativity ; i++)
        low_priority_blocks.push_back(new cache_block());
}

// at the end of all accesses , update the main memory
void cache_set::update_memory(int set_index){
    for(int i = 0 ; i < high_priority_blocks.size() ; i++){
        if(high_priority_blocks[i]->dirty){
            int block_address = high_priority_blocks[i]->tag*number_of_sets + set_index;
            memory_array[block_address] = high_priority_blocks[i]->block_data;
        }
    }

    for(int i = 0 ; i < low_priority_blocks.size() ; i++){
        if(low_priority_blocks[i]->dirty){
            int block_address = low_priority_blocks[i]->tag*number_of_sets + set_index;
            memory_array[block_address] = low_priority_blocks[i]->block_data;
        }
    }
}

cache_set::~cache_set(){
    for(int i = 0 ; i < high_priority_blocks.size() ; i++)
        delete high_priority_blocks[i];

    for(int i = 0 ; i < low_priority_blocks.size() ; i++)
        delete low_priority_blocks[i];
}

// returns true for HIT and false for MISS
bool cache_set::write_in_set(int tag , int set_index , int data){
    bool temp;

    // search for block in high priority group first
    for(int i = 0 ; i < high_priority_blocks.size() ; i++){
        if(high_priority_blocks[i]->tag == tag){
            temp = high_priority_blocks[i]->write_in_block(data);
            update_lru(i);
            return temp;
        }
    }

    // not found , then search in low priority group
    for(int i = 0 ; i < low_priority_blocks.size() ; i++){
        if(low_priority_blocks[i]->tag == tag){
            temp = low_priority_blocks[i]->write_in_block(data);
            move_to_high_priority(i);
            return temp;
        }
    }

    // if not found , then insert block
    insert_block(tag , set_index);
    low_priority_blocks[0]->write_in_block(data);

    return false;
}

// returns true for HIT and false for MISS
bool cache_set::read_from_set(int tag , int set_index){
    bool temp;

    // search for block in high priority group first
    for(int i = 0 ; i < high_priority_blocks.size() ; i++){
        if(high_priority_blocks[i]->tag == tag){
            temp = high_priority_blocks[i]->read_from_block();
            update_lru(i);
            return temp;
        }
    }

    // not found , then search in low priority group
    for(int i = 0 ; i < low_priority_blocks.size() ; i++){
        if(low_priority_blocks[i]->tag == tag){
            temp = low_priority_blocks[i]->read_from_block();
            move_to_high_priority(i);
            return temp;
        }
    }

    // if not found , then insert block
    insert_block(tag , set_index);
    low_priority_blocks[0]->read_from_block();

    return false;
}

// insert a block with the tag
void cache_set::insert_block(int tag , int set_index){
    int nl = low_priority_blocks.size() , nh = high_priority_blocks.size();
    int block_address = tag*number_of_sets + set_index;

    // already max number of blocks are there
    if(nl + nh == cache_associativity){
        if(nh == cache_associativity){
            // if dirty , then write to main memory
            if(high_priority_blocks[nh - 1]->dirty)
                memory_array[high_priority_blocks[nh - 1]->tag*number_of_sets + set_index] = high_priority_blocks[nh - 1]->block_data;
            
            delete high_priority_blocks[nh - 1];
            high_priority_blocks.pop_back();    // pop the last element from the high prioirity group
            low_priority_blocks.push_back(new cache_block(tag , memory_array[block_address]));
        }

        else{
            // if dirty , then write to main memory
            if(low_priority_blocks[nl - 1]->dirty)
                memory_array[low_priority_blocks[nl - 1]->tag*number_of_sets + set_index] = low_priority_blocks[nl - 1]->block_data;

            delete low_priority_blocks[nl - 1];
            low_priority_blocks.pop_back();     // pop the last element from the low priority group
            low_priority_blocks.insert(low_priority_blocks.begin() , new cache_block(tag , memory_array[block_address]));
        }
    }

    else{
        if(nl == 0){
            low_priority_blocks.push_back(new cache_block(tag , memory_array[block_address]));
        }

        else{
            low_priority_blocks.insert(low_priority_blocks.begin() , new cache_block(tag , memory_array[block_address]));
        }
    }
}

// upadte the lru status of high priority blocks
void cache_set::update_lru(int i){
    cache_block* temp = high_priority_blocks[i];
    high_priority_blocks.erase(high_priority_blocks.begin() + i);
    high_priority_blocks.insert(high_priority_blocks.begin() , temp);
    high_priority_blocks[0]->time_left = T+1;
}

// move block at index i of low priority to high priority
void cache_set::move_to_high_priority(int i){
    cache_block* temp = low_priority_blocks[i];
    low_priority_blocks.erase(low_priority_blocks.begin() + i);
    high_priority_blocks.insert(high_priority_blocks.begin() , temp);
    high_priority_blocks[0]->time_left = T+1;
}

// move block at index i of high priority to low priority
void cache_set::move_to_low_priority(int i){
    cache_block* temp = high_priority_blocks[i];
    high_priority_blocks.erase(high_priority_blocks.begin() + i);
    low_priority_blocks.insert(low_priority_blocks.begin() , temp);
}

// after usage , update the last used times of the block
void cache_set::update_last_used_times(){
    for(int i = 0 ; i < high_priority_blocks.size() ; i++){
        high_priority_blocks[i]->time_left--;
        if(high_priority_blocks[i]->time_left == 0){
            move_to_low_priority(i);
        }
    }
}

void cache_set::display_set(){
    cout<<"High priority blocks :\n";
    for(int i = 0 ; i < high_priority_blocks.size() ; i++)
        high_priority_blocks[i]->display_block();

    cout<<"\nLow priority blocks :\n";
    for(int i = 0 ; i < low_priority_blocks.size() ; i++)
        low_priority_blocks[i]->display_block();
}