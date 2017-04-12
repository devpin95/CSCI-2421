//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                         EntryPrinter.h
//                                    Devin Piner - 107543409
//                                         April 1, 2017
//
//                              Interface for the EntryPrinter class
//               A specialized class for printing a specific data from an Entry based on the
//                                    table in which it resides
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

class QueryString {
    friend class Parser;

public:
    enum actions{
        SELECT = 0,
        INSERT,
        UPDATE,
        DELETE
    };

    static actions a;

    static const string WHERE; //WHERE
    static const string CONTAINS; //CONTAINS
    static const string EQUALS; //=
    static const string STAR; //* all

    QueryString(); //default constructor
    QueryString( string, string, string );
    void setAction(int);
    void setColumns( string ); //must be comma separated with no spaces in the keys
    void setConditions( string ); //must be delimited by a comma, = for each condition

private:
    vector<string> columns;
    struct Condition {
        string key;
        string operations;
        string value;
    };
    vector<Condition> conditions;

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
};

class Parser {
public:
    Parser(); //default constructor
    vector<string> parseKeys( string );
    vector<QueryString::Condition> parseConditions( string );
};


#endif //CSCI2421_QUERYSTRING_H
