//
// Created by devpin on 4/12/2017.
//

#ifndef HW9_HASHTABLE_H
#define HW9_HASHTABLE_H

#include "Entry.h"
#include "FileObject.h"
#include <list>
#include <stdio.h>
#include <iostream>

class HashTable {
public:
    HashTable();
    ~HashTable();
    void insert( Entry* );
    void report();
private:
    const static int prime = 167;
    FileObject* files[ prime ] { nullptr, };
    int counters[ prime ] = { 0, };

};


#endif //HW9_HASHTABLE_H
