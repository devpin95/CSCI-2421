//
// Created by devpin on 4/12/2017.
//

#include "HashTable.h"

HashTable::HashTable(){
    //...
}

HashTable::~HashTable() {
    for ( int i = 0; i < prime; ++i ) {
        if ( files[i] != nullptr ) {
            delete files[i];
        }
    }
}

void HashTable::insert( Entry* entry ) {
    //get the entry id and convert it to a long so that it can be hashed

    Entry& newEntry = *entry;
    string id = newEntry[ Entry::ID ];
    long idi = stol( id );

    //hash the id
    long hash = hasher(idi);
    ++counters[hash];

    if ( files[hash] == nullptr ) {
        files[hash] = new FileObject( "C:\\Users\\devpin\\Documents\\school\\CSCI2421\\final\\temp\\" + std::to_string(hash) + ".txt" );
    }

    files[hash]->append( string(newEntry[ Entry::ID ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::F_NAME ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::M_NAME ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::L_NAME ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::COMPANY_NAME ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::HOME_NUMBER ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::OFFICE_NUMBER ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::EMAIL ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::MOBILE_NUMBER ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::ADDRESS ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::CITY ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::STATE ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::ZIP ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::COUNTRY ] + "\n").c_str() );
    files[hash]->append( string(newEntry[ Entry::AFFILIATES ] + "\n").c_str() );
    files[hash]->append( "|\n" );

}

void HashTable::report(  ) {
    int total = 0;
    int lowest = 1000;
    int highest = 1;
    for ( int i = 0; i < prime; ++i ) {
        if ( counters[i] != 0 ) {
            std::cout << i << ": " << counters[i] << std::endl;
            total += counters[i];
            if ( counters[i] < lowest ) {
                lowest = counters[i];
            } else if ( counters[i] > highest ) {
                highest = counters[i];
            }
        }
    }

    std::cout << std::endl << total << std::endl;
    std::cout << lowest << std::endl;
    std::cout << highest << std::endl;
}