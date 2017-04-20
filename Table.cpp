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

Table::Table( vector<string> ) {

}

bool Table::insert( Entry* entry ) { //function to insert and entry into the table
    data.push_back( entry );
    ++size;

    return false;
}

Entry* Table::operator[]( int i ) {
    return data[i];
}
