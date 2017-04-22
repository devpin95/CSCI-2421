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

#include "Table.h"

Table::Table( const vector<string>& table_keys ) {
    keys = table_keys;
}

Table::~Table( void ) {
    for ( int i = 0; i < data.size(); ++i ) {
        Entry* entry = (*data.end());
        data.pop_back();
        delete entry;
    }
}

bool Table::insert( Entry* entry ) { //function to insert and entry into the table
    data.push_back( entry );
    ++size;

    return false;
}

bool Table::isEmpty( void ) {
    return !( bool(size) );
}

Entry* Table::operator[]( int i ) {
    return data[i];
}
