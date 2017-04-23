//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                            Database.h
//                                    Devin Piner - 107543409
//                                         April 1, 2017
//
//                                Interface for the Database class
//                  Reads in data from the database text file and stores it to be queried
//          using the QueryObject class and returning a Table class with all the requested entries
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
//UPDATES
//private:
//  readfile(ifstream&)
//
//successfully reads in data

#ifndef CSCI2421_DATABASE_H
#define CSCI2421_DATABASE_H

#include <string>
#include <fstream>
#include <sstream>
#include "QueryObject.h"
#include "Entry.h"
#include "Table.h"
#include "BSTree.h"
#include "HashTable.h"

using std::string;

class Database {
public:
    Database( void );
    Database( string );
    void setDatabase( string file ) { filename = file; };
    bool connect( void ) { return connect( filename ); };
    bool connect( string );
    bool disconnect( void );
    Table* query(const QueryObject&, Entry *in = nullptr);
    Table& query( const QueryObject&, const Table& );
    static bool evaluateConditions( Entry*, const QueryObject& );

private:
    string filename;
    bool connection = false;
    bool ready = false; //a filename must be added before the object is valid
    BSTree data;
    HashTable hashes;

    void readfile( ifstream& );
    Table* select( const QueryObject& );
    Table* selectExactID( const QueryObject& );
    Table* update( const QueryObject& );
    Table* insert( Entry* );
};


#endif //CSCI2421_DATABASE_H
