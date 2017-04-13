//
// Created by devpin on 4/12/2017.
//

#ifndef HW9_HASHTABLE_H
#define HW9_HASHTABLE_H

#include "Entry.h"
#include <list>
#include <stdio.h>

class HashTable {
public:
    HashTable();
    void insert( const Entry* );
private:
    std::list<Entry*> buckets[4111];

};


#endif //HW9_HASHTABLE_H
