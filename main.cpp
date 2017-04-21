//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                            main.cpp
//                                    Devin Piner - 107543409
//                                         April 5, 2017
//
//                                  Driver for the Database class
//                        Gives the user access to search, update, and insert
//                              records retrieved from a database file
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//
//void readFile( Database& );
//  Lets the user input a string filename for the Database object to read from
//
//Table& search( Database& );
//  Prompts the user for columns and conditions for searching the database and returns a
//  table of Entries that can be searched again.
//
//void searchTable( Database&, Table& );
//  Accepts an Table to be searched again using the same algorithm as search (Database)
//
//void newEntry( Database& );
//  Prompts the user for Entry information that will be inserted into the database
//
//void closeDatabase( Database& );
//  Closes the database using Database::disconnect(). All Database states will be handled by the database.
//  Calling this function marks the end of the program
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <sstream>
#include "Database.h"
#include "Table.h"
#include "QueryObject.h"
#include "Entry.h"
#include "FileObject.h"

//void readFile( Database& );
//Table& search( Database& );
//void searchTable( Database&, Table& );
//void newEntry( Database& );
//void closeDatabase( Database& );

using namespace std;
#define ONLAPTOP
//#define ONDESKTOP
#ifdef ONLAPTOP
const char* filename = "C:\\Users\\devpin\\Documents\\school\\CSCI2421\\final\\databasesmall.txt";
#elif ONDESKTOP
const char* filename = "C:\\Users\\devpin\\Documents\\school\\CSCI2421\\final\\databaselarge.txt";
#endif
int main() {

    Database db;
    db.setDatabase( filename );

    cout << "Connecting..." << endl;
    if ( !db.connect() ) {
        cout << "Something went wrong" << endl;
    } else {

        cout << "AFTER READ IN" << endl;

        QueryObject query;
        vector<string> columns = { Entry::ID, Entry::F_NAME, Entry::L_NAME };

        query.setAction(QueryObject::SELECT);
        query.setColumns( columns );
        query.setCondition( Entry::ID, QueryObject::EQUALS, "687075432" );

        Table* tablePtr;

        tablePtr = db.query( query );

        Table& table = *tablePtr;
        if ( !table.isEmpty() ) {
            cout << table[0]->operator[](Entry::ID) << endl;
            cout << table[0]->operator[](Entry::F_NAME) << endl;
            cout << table[0]->operator[](Entry::L_NAME) << endl;
        } else {
            cout << "No Entries Found" << endl;
        }

        cout << "AFTER QUERY" << endl;

    }



    //main do-while loop
//    do {
//
//        //int to hold the user's selection
//        int selection;
//
//        //database object
//        Database db;
//
//        //print the list of menu options
//        //1. Open Database
//        //2. Search
//        //3. Enter Record
//        //4. Close
//
//        //get the option
//        //cin >> selection
//
//        //switch calling all of the functions for
//        //each option
//
//        switch ( selection ) {
//            case 1: readFile(db);
//                break;
//            case 2: search(db);
//                break;
//            case 3: newEntry(db);
//                break;
//            case 4: closeDatabase(db);
//                break;
//            default:
//                cout << selection << " is not an option";
//                break;
//        }
//
//    } while ( true );

    return 0;
}

//void readFile( Database& db ) {
//    // readFile()
//    // prompts the user to enter the filename from which the Database
//    // object can read in records. After calling this function, an not
//    // receiving an error, the database is ready to be queried
//
//    //read in a filename string
//    string filename;
//
//    cout << "Enter a database file" << endl;
//    getline(cin, filename);
//
//    //set the filename in the Database object
//    db.setDatabase(filename);
//    if ( !db.connect() ) {
//        cout << "Could not open file, try again." << endl;
//    }
//
//}
//
//Table& search( Database& db ) {
//    //------------------------------------------------------------------------------------------------------------------
//    //------------------------------------------------------------------------------------------------------------------
//    //                                     Get the columns for the search
//    //------------------------------------------------------------------------------------------------------------------
//    //------------------------------------------------------------------------------------------------------------------
//
//    //prompt the user for the columns they would like returned
//    cout << "What information would you like? (insert # separated by spaces" << endl;
//
//    //print out all of the fields in Entry
//    for ( int ii = 0; ii < Entry::FIELD_COUNT; ++ii) {
//        cout << ii + 1 << ". " << Entry::fieldNames[ii] << endl;
//    }
//
//    //read in the numbers to a string, then put them into a stringstream so we can read them 1 at a time
//    string readline;
//    getline(cin, readline);
//    stringstream ss;
//    ss << readline;
//
//    int key;
//    string fields; //a concatinated string of fields for the query
//    QueryObject query;
//    query.setAction( QueryObject::SELECT );
//    while ( ss >> key ) {
//        //since the menu starts at one, the user will enter numbers 1 higher than what they actually want
//        //based on the array of fieldNames from Entry
//        --key;
//
//        fields += Entry::fieldNames[key] + " ";
//    }
//
//    //pass the string of fields to the setcolumns function for parsing
//    query.setColumns(fields);
//
//    //------------------------------------------------------------------------------------------------------------------
//    //------------------------------------------------------------------------------------------------------------------
//    //                                     Get the conditions for the search
//    //------------------------------------------------------------------------------------------------------------------
//    //------------------------------------------------------------------------------------------------------------------
//
//    int column;
//    string conditions;
//    string value;
//    do {
//        //--------------------------------------------------------------------------------------------------------------
//        //--------------------------------------------------------------------------------------------------------------
//        //                                      Get the condition key
//        //--------------------------------------------------------------------------------------------------------------
//        //--------------------------------------------------------------------------------------------------------------
//        value.clear();
//
//        //prompt the user for the conditions they would like to filter out records
//        cout << "What conditions? (-1 to exit)" << endl;
//
//        //print out all of the fields in Entry
//        for (int ii = 0; ii < Entry::FIELD_COUNT; ++ii) {
//            cout << ii + 1 << ". " << Entry::fieldNames[ii] << endl;
//        }
//
//        //get the column for the condition
//        int column;
//        cin >> column;
//
//        //skip this if the column number is -1
//        if ( column != -1 ) {
//            conditions += Entry::fieldNames[column - 1] + " = ";
//
//            //----------------------------------------------------------------------------------------------------------
//            //----------------------------------------------------------------------------------------------------------
//            //                                     Get the condition value
//            //----------------------------------------------------------------------------------------------------------
//            //----------------------------------------------------------------------------------------------------------
//            cout << "Enter the value" << endl;
//            cin >> value;
//
//            conditions += value + ", ";
//        }
//
//        //we should end with a string in this form
//        //id = 12345, f_name = Devin
//
//    } while ( column != -1 );
//
//    //----------------------------------------------------------------------------------------------------------
//    //----------------------------------------------------------------------------------------------------------
//    //                               Set the query string and send it to the database
//    //----------------------------------------------------------------------------------------------------------
//    //----------------------------------------------------------------------------------------------------------
//
//    query.setConditions( conditions );
//    searchTable( db, db.query( query ) );
//}
//
//void searchTable( Database& db, Table& table ) {
//    //print out the table
//    //TODO find a better way for printing so that it Table can print it for us
//    for ( int ii = 0; ii < table.size; ++ii ) {
//        cout << table[ii];
//    }
//
//    //------------------------------------------------------------------------------------------------------------------
//    //------------------------------------------------------------------------------------------------------------------
//    //                                              Menu to search a table
//    //                                          TODO MOVE TO SEPARATE FUNCTION
//    //------------------------------------------------------------------------------------------------------------------
//    //------------------------------------------------------------------------------------------------------------------
//
//    do {
//        //print a menu of available actions on the table
//        //1. Search Table
//        //2. Back
//
//        if ( 1 ) //do the same algorithm as search
//        //TODO make a separate function for getting columns and conditions from user
//        else if ( 2 ); //go back
//
//        //--------------------------------------------------------------------------------------------------------------
//        //--------------------------------------------------------------------------------------------------------------
//        //Build a QueryObject to search the table
//        //pass the QueryObject and table to Database::query()
//        //--------------------------------------------------------------------------------------------------------------
//        //--------------------------------------------------------------------------------------------------------------
//
//    } while ( /*user wants to continue */ );
//}
//
//void newEntry( Database& db ) {
//    //TODO implement the concept of NOTNULL columns similar to SQL databases
//
//    //--------------------------------------------------------------------------------------------------------------
//    //--------------------------------------------------------------------------------------------------------------
//    //set up strings to hold the keys and values
//    string keyValues;
//
//    //Build a QueryObject for inserting a new record
//    QueryObject query;
//    query.setAction( QueryObject::INSERT );
//
//    //Get the fields the user wishes to enter and the values using similar loops to the search function
//    //get the id because it is required
//    cin >> id;
//    keyValues += "id = " + id + " ";
//
//    //now loop through and let the user select each field and insert a value
//    int selection; //key
//    string value; //value
//
//    //print out the menu and get the input
//    //-1 if no more fields are going to be entered
//    cout << "Add field, -1 to exit" << endl;
//    for (int ii = 0; ii < Entry::FIELD_COUNT; ++ii) {
//        cout << ii + 1 << ". " << Entry::fieldNames[ii] << endl;
//    }
//    cin >> selection;
//
//    while ( selection != - 1 ) {
//        //get the keys value
//        cin >> value;
//        keyValues += " , " + Entry::fieldNames[selection] + " = " + value;
//
//        //start the menu again, -1 to exit
//        cout << "Add field, -1 to exit" << endl;
//        for (int ii = 0; ii < Entry::FIELD_COUNT; ++ii) {
//            cout << ii + 1 << ". " << Entry::fieldNames[ii] << endl;
//        }
//        cin >> selection;
//    }
//
//    //Set the query conditions and send it of to the database
//    query.setConditions( keyValues );
//    db.query( query );
//
//    //--------------------------------------------------------------------------------------------------------------
//    //--------------------------------------------------------------------------------------------------------------
//
//}
//
//void closeDatabase( Database& db ) {
//    if ( !db.disconnect() ) {
//        cout << "Something went wrong, disconnected unsuccessfully" << endl;
//    } else {
//        cout << "Disconnected successfully" << endl;
//    }
//}
