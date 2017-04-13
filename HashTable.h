//
// Created by devpin on 4/12/2017.
//

#ifndef HW9_HASHTABLE_H
#define HW9_HASHTABLE_H

#include "Entry.h"
#include <list>
#include <stdio.h>
#include <iostream>

class HashTable {
public:
    HashTable();
    void insert( Entry* );
    void report();
private:
    const int prime = 150;
    //std::list<Entry*>* buckets[prime] = {nullptr, };
    int counters[ 150 ] = { 0, };

};


#endif //HW9_HASHTABLE_H
