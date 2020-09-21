#include "../include/cache_set.h"
#include "../include/cache.h"
#include "../include/cache_block.h"
#include "../include/global.h"
#include <bits/stdc++.h>

using namespace std;

// convert string to tokens by "," , ignore spaces
void tokenise_memory(string temp){
    if(temp.empty())
        return;
    vector<string> tokenised;
    string foo;

    for(int i = 0 ; i < temp.length() ; i++){
        if(temp[i] == ' ')
            continue;

        else if(temp[i] == ','){
            tokenised.push_back(foo);
            foo.clear();
        }

        else{
            foo.push_back(temp[i]);
        }
    }
    tokenised.push_back(foo);

    memory_access_requests.push_back(tokenised);
}

// reads the corresponding input , store accesses as tokens
void read_from_input_file(){
    fstream infile;

    infile.open("input.txt",ios::in);

    string temp;

    infile>>cache_size;
    infile>>block_size;
    infile>>cache_associativity;
    infile>>T;

    while(getline(infile,temp)){
        tokenise_memory(temp);
    }

    infile.close();
}

int main(){

    read_from_input_file();

    number_of_blocks = cache_size/block_size;
    number_of_sets = number_of_blocks/cache_associativity;

    for(int i = 0 ; i < number_of_sets ; i++)
        cache.push_back(new cache_set());

    manipulate_cache();

    cout<<"\n----------Final cache--------------\n";
    display_cache();
    cout<<"------------------------------------\n";

    cout<<"----------------Main memory-----------\n";
    for(int i = 0 ; i < 32 ; i++){
        cout<<memory_array[i]<<" ";
    }

    cout<<"\n--------Cache statistics----------\n";

    cout<<"\nNumber of Accesses = "<<memory_access_requests.size();
    cout<<"\nNumber of Reads = "<<number_of_reads;
    cout<<"\nNumber of Read Hits = "<<read_hits;
    cout<<"\nNumber of Read Misses = "<<number_of_reads - read_hits;
    cout<<"\nNumber of Writes = "<<number_of_writes;
    cout<<"\nNumber of Write Hits = "<<write_hits;
    cout<<"\nNumber of Write Misses = "<<number_of_writes - write_hits;
    cout<<"\nHit Ratio = "<<(float)(read_hits + write_hits)/memory_access_requests.size()<<endl;

    for(int i = 0 ; i < number_of_sets ; i++)
        delete cache[i];

    return 0;
}