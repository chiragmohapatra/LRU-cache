#include "../include/cache.h"
#include "../include/global.h"

void display_cache(){
    for(int i = 0 ; i < cache.size() ; i++){
        cout<<"\nSet :"<<i<<endl<<endl;
        cache[i]->display_set();
    }
}

// handle write operation for ith request
void handle_write(int i){
    long block_number = stol(memory_access_requests[i][0]);
    int data = stoi(memory_access_requests[i][2]);

    assert(block_number >= 0);

    //long block_number = memory_address/block_size;

    int set_index = block_number % number_of_sets;
    int tag = block_number/number_of_sets;

    //int offset = memory_address % block_size;

    if(cache[set_index]->write_in_set(tag , set_index , data)){
        cout<<"WRITE HIT\n";
        write_hits++;
    }

    else{
        cout<<"WRITE MISS\n";
    }
    
    for(int i = 0 ; i < cache.size() ; i++){
        cache[i]->update_last_used_times();
    }
}

// handle read operation for ith request
void handle_read(int i){
    long block_number = stol(memory_access_requests[i][0]);

    assert(block_number >= 0);

    //long block_number = memory_address/block_size;

    int set_index = block_number % number_of_sets;
    int tag = block_number/number_of_sets;

    //int offset = memory_address % block_size;

    if(cache[set_index]->read_from_set(tag , set_index)){
        read_hits++;
    }

    for(int i = 0 ; i < cache.size() ; i++){
        cache[i]->update_last_used_times();
    }
}

// at the end of all requests , we update main memory a final time
void update_main_memory(){
    for(int i = 0 ; i < cache.size() ; i++){
        cache[i]->update_memory(i);
    }
}

// handle cache requests
void manipulate_cache(){
    for(int i = 0 ; i < memory_access_requests.size() ; i++){
        if(debug){
            cout<<"------------------------------------\n";
            cout<<"Request "<<i<<":\n";
        }

        if(memory_access_requests[i][1] == "W"){
            handle_write(i);
            number_of_writes++;
        }

        else{
            handle_read(i);
            number_of_reads++;
        }

        if(debug){
            cout<<"----------Cache------------\n";
            display_cache();
        }

        if(one_by_one)
            getchar();
    }

    update_main_memory();
}