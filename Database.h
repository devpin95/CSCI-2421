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
    Table* update( const QueryObject&,  Entry* );
    Table* updateExactID( const QueryObject&,  Entry* );
    Table* insert( Entry* );
    Table* delExactID( const QueryObject& );
    Table* del( const QueryObject& );

};

struct AddEvaluate {
    Table* tbl = nullptr;
    Condition condition;

    void eval(Entry *entryPtr) {
        bool is_match = false; //bool to hold the result of the condition check

        //dereference the pointer so that we can access it like normal
        Entry& entry = *entryPtr;

        //First, check what condition we are checking for
        //EQUALS (exact match)
        //CONTAINS (field contains the value)

        string key = entry[condition.key];
        string value = condition.value;

        //cout << "|  " << entry[ key ] << " - " << value << endl;

        //EQUALS - exact match
        if ( condition.operation == QueryObject::EQUALS) {
            is_match = ( key == value );
        }

            //CONTAINS- field contains the value
        else if ( condition.operation == QueryObject::CONTAINS ) {
            //Use find to search the field for the value. If the value is found in
            //the field, it will return an unsigned int. If not found, string::npos
            //string::find referenced from
            //http://www.cplusplus.com/reference/string/string/find/
            if ( key.find( value ) != std::string::npos ) {
                is_match = true;
            }
        }

        if ( is_match ) {
            Entry* row = new Entry( entryPtr );
            tbl->insert( row );
        }
    };
};

struct DeleteEvaluate {
    Table* tbl = nullptr;
    Condition condition;
    Node* node;

    bool eval(Entry *entryPtr) {
        bool is_match = false; //bool to hold the result of the condition check

        //dereference the pointer so that we can access it like normal
        Entry& entry = *entryPtr;

        //First, check what condition we are checking for
        //EQUALS (exact match)
        //CONTAINS (field contains the value)

        string key = entry[condition.key];
        string value = condition.value;

        //cout << "|  " << entry[ key ] << " - " << value << endl;

        //EQUALS - exact match
        if ( condition.operation == QueryObject::EQUALS) {
            is_match = ( key == value );
        }

            //CONTAINS- field contains the value
        else if ( condition.operation == QueryObject::CONTAINS ) {
            //Use find to search the field for the value. If the value is found in
            //the field, it will return an unsigned int. If not found, string::npos
            //string::find referenced from
            //http://www.cplusplus.com/reference/string/string/find/
            if ( key.find( value ) != std::string::npos ) {
                is_match = true;
            }
        }

        if ( is_match ) {
            Entry* row = entryPtr;
            entryPtr = nullptr;
            tbl->insert( row );
        }

        return is_match;
    };
};

struct WriteEvaluate {
    HashTable* hashtable;
    int count = 0;

    void eval(Entry *entryPtr) {
        if ( count == 0 ) {
            hashtable->insert(entryPtr, true);
        } else {
            hashtable->insert(entryPtr);
        }
        ++count;
    };
};

#endif //CSCI2421_DATABASE_H
