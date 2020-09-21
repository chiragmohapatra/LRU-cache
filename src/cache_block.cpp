#include "../include/cache_block.h"
#include "../include/global.h"

cache_block::cache_block(){
    valid_bit = false;
    tag = -1;
    time_left = 0;
    dirty = false;
    block_data = -1;
}

cache_block::cache_block(int tag , int data){
    valid_bit = false;
    dirty = false;
    this->tag = tag;
    block_data = data;
    time_left = 0;
}

// returns true if HIT and false if MISS
bool cache_block::write_in_block(int data){
    dirty = true;
    if(!valid_bit){
        block_data = data;
        valid_bit = true;
        return false;
    }

    else{
        block_data = data;
        return true;
    }
}

// returns true if HIT and false if MISS
bool cache_block::read_from_block(){
    if(!valid_bit){
        valid_bit = true;
        cout<<"READ MISS    : Read data "<<block_data<<endl;
        return false;
    }

    else{
        cout<<"READ HIT    : Read data "<<block_data<<endl;
        return true;
    }
}

void cache_block::display_block(){
    if(!valid_bit){
        cout<<"Valid bit :0 Tag :"<<tag<<endl;
    }

    else{
        cout<<"Valid bit :1 ";
        cout<<"Tag :"<<tag;
        cout<<" Time left :"<<time_left;
        cout<<" Dirty :"<<dirty;
        cout<<" Data :"<<block_data;
        cout<<endl;
    }
}
