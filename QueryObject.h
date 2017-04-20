//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                         QueryObject.h
//                                    Devin Piner - 107543409
//                                         April 1, 2017
//
//                              Implementaton of the QueryObject class
//                      A specialized class for handling query request details
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//  Public Functions
//
//EntryPrinter()
//  Default constructor for the EntryClass object. No data needs to be passed to the constructor
//
//void setKeys( const vector<Entry::e_type>& )
//  Accepts a vector of Entry field types to set the fields to be printed for the next Entry
//
//void print( const Entry& )
//  Accepts an Entry to be printed using the current field keys (the keys vector is empty by default)
//
//void print( const Entry&, const vector<Entry::e_type>& )
//  Accepts an Entry to be printed using the keys vector passed in. The vector will persist until
//  overwritten by setKeys()
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

#ifndef CSCI2421_QUERYSTRING_H
#define CSCI2421_QUERYSTRING_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class QueryObject {

public:
    enum actions{
        SELECT = 0,
        INSERT,
        UPDATE,
        DELETE
    };

    static actions a;

    static const string CONTAINS; //CONTAINS
    static const string EQUALS; //=
    static const string STAR; //* all

    QueryObject(); //default constructor
    QueryObject( const actions& act, const vector<string>& columns, const string& key, const string& operation, const string& value);
    void setAction(const actions& action);
    void setColumns( const vector<string>& );
    void setCondition( const string& key, const string& operation, const string& value );
    actions getAction() const;
    vector<string>& getColumns() const;
    Condition& getCondition() const;

private:
    vector<string> columns;
    struct Condition {
        string key;
        string operations;
        string value;
    };

    struct Action {
        bool select = false;
        bool insert = false;
        bool update = false;
        bool dlt = false;

        void setAction( actions a ) {
            if ( a == SELECT ) {
                select = true;
                insert = false;
                update = false;
                dlt = false;
            } else if ( a == INSERT ) {
                select = false;
                insert = true;
                update = false;
                dlt = false;
            }else if ( a == UPDATE ) {
                select = false;
                insert = false;
                update = true;
                dlt = true;
            } else if ( a == DELETE ) {
                select = false;
                insert = false;
                update = false;
                dlt = true;
            }
        }
    };

    Action action;
    Condition condition;
};


#endif //CSCI2421_QUERYSTRING_H
