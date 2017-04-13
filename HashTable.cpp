//
// Created by devpin on 4/12/2017.
//

#include "HashTable.h"

HashTable::HashTable(){
    //...
}

void HashTable::insert( Entry* entry ) {
    Entry& newEntry = *entry;
    string id = newEntry[ Entry::ID ];
    long idi = stol( id );

    long hash = idi % prime;
    ++counters[hash];
}

void HashTable::report(  ) {
    int total = 0;
    for ( int i = 0; i < prime; ++i ) {
        if ( counters[i] != 0 ) {
            std::cout << i << ": " << counters[i] << std::endl;
            total += counters[i];
        }
    }

    std::cout << total << std::endl;
}