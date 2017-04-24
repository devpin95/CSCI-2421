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
    if ( size > 0 ) {
        for (auto i = data.size(); i > 0; --i) {
            Entry *entry = data.back();
            data.pop_back();
            --size;
            delete entry;
        }
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

void Table::setKeys( vector<string>& k ) {
    keys = k;
}

Entry* Table::operator[]( int i ) {
    return data[i];
}

ostream& operator<<( ostream& out, Table& table ) {
    out << std::left;
    cout << std::setw(5) << "#";
    for ( int i = 0; i < table.keys.size(); ++i ) {
        out << std::setw( 25 ) << table.keys[i];
    }

    out << endl;

    for( int i = 0; i < table.keys.size(); ++i ) {
        cout << "-------------------------";
    }

    out << endl;
    for ( int i = 0; i < table.size; ++i ) {
        out << std::setw(5) << i + 1;
        for ( int j = 0; j < table.keys.size(); ++j ) {
//            if ( table.keys[i] == Entry::AFFILIATES ) {
//                string affils = table.data[ i ]->operator[]( table.keys[j] );
//                str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
//            };
            out << std::setw( 25 ) << table.data[ i ]->operator[]( table.keys[j] );
        }
        out << endl;
    }

    return out;
}
