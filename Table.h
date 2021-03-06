//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                            Table.h
//                                    Devin Piner - 107543409
//                                         April 1, 2017
//
//                                Interface for the Table class
//                  Hold data in a list so that it can be accessed with subscripts
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//  Public Functions
//
//Table( vector<Entry::e_type );
//  A constructor that accepts a vector of Entry::e_type as keys to the columns of the table
//  These keys will limit the amount of information that the table holds
//
//bool insert( const Entry& )
//  Accepts and Entry to be inserted into the table. Returns true if successful, false in unsuccessful
//
//Entry& operator( int )
//  Returns an Entry from the specified row of the table
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

#ifndef CSCI2421_TABLE_H
#define CSCI2421_TABLE_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "Entry.h"
#include "QueryObject.h"

using std::vector;
using std::ostream;
using std::cout;
using std::endl;

class Table {
    friend class EntryValidate;
public:
    Table( const vector<string>& ); //constructor that accepts a vector containing the keys to the column names
    ~Table( void );
    Table* filter( QueryObject& );
    friend ostream& operator<<( ostream& out, Table& );
    bool insert( Entry* ); //function to insert and entry into the table
    bool isEmpty( void ); //function to return if there are no entries in the table
    void setKeys( vector<string>& );
    Entry* operator[]( int ); //access an entry in the table
    int size = 0; //increased on each insert

private:
    vector<Entry*> data; //a vector of pointers to each entry
    vector<string> keys; //the columns that are active in the table (the ones we care about)
};


#endif //CSCI2421_TABLE_H
