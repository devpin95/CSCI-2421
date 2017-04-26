#include "functions.h"

void readDB(Database &db) {
    // readFile()
    // prompts the user to enter the filename from which the Database
    // object can read in records. After calling this function, an not
    // receiving an error, the database is ready to be queried

    //read in a filename string
    string filename;

    cout << "Enter a database file" << endl;
    getline(cin, filename);

    //set the filename in the Database object
    db.setDatabase(filename);
    if ( !db.connect() ) {
        cout << "Could not open file, try again." << endl;
    }

}

void closeDB( Database& db ) {
    db.disconnect();
}

void search( Database& db, Table* t ) {
    //------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------
    //                                     Get the columns for the search
    //------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------
    bool cont = true; //loop control variable
    bool needs_clear = false;
    vector<string> columns;

    do {

        if ( needs_clear )
            clearBuffer( cin );

        cout << "What columns would you like to view?" << endl;

        printEntryOptions( true );

        cout << "Enter field numbers, no repeats, spaces between each number, 0 as the terminating value. Press enter to continue" << endl;
        cout << "Example: 1 3 4 10 0" << endl;
        cout << "Fields: ";

        int field_number;

        for ( int i = 0; i < Entry::FIELD_COUNT; ++i ) {
            cin >> field_number;
            if ( field_number == -1 ) {
                return; //<--------------------------------------------------------------------------------------------- RETURN
            }

            if ( field_number == 0 ) {
                cont = false;
                break;
            }

            //decrement the number entered because the fieldNames array starts at 0
            --field_number;

            //make sure the number is in range
            if ( field_number < 0 || field_number > Entry::FIELD_COUNT ) {
                cont = true;
                needs_clear = true;
                break;
            } else {
                //first, check if the value is already in the vector
                for ( int j = 0; j < columns.size(); ++j ) {
                    if ( columns[j] == Entry::fieldNames[field_number] ) {
                        cont = false;
                        break;
                    }
                }
                //if we get here, the value must not be in the vector, so add it
                columns.push_back( Entry::fieldNames[field_number] );
            }

        }

    } while ( cont );

    cout << endl << endl;

    QueryObject query;
    query.setAction(QueryObject::SELECT);
    query.setColumns(columns);
    getQueryCondition(query);

    if ( t == nullptr ) {

        cout << "Searching..." << endl << endl;
        t = db.query(query);
    } else {
        cout << "Filtering..." << endl << endl;
        t = t->filter( query );
    }

    cout << *t;
    cout << endl << endl;

    int option;

    cout << "Table Actions---------------------------------------------" << endl;
    cout << "1. New Search" << endl;
    cout << "2. Filter Results" << endl;
    cout << "3. Update Entry" << endl;
    cout << "4. Delete Entry" << endl;
    cout << "5. Print Report to File" << endl;
    cout << "6. Back" << endl;
    cout << ">";
    cin >> option;

    cout << endl << endl;

    if ( option == 1 ) { //NEW SEARCH
        //delete the table so that it isnt sitting in memory
        //then start another search
        delete t;
        clearBuffer( cin );
        search(db);
    }
    else if ( option == 2 ) { //FILTER RESULTS ----------------------------------------
        clearBuffer( cin );
        search( db, t );
    }
    else if ( option == 3 ) { //UPDATE ENTRY ------------------------------------------
        clearBuffer( cin );
        int selection;

        do {
            cout << "Update Entry #: ";
            cin >> selection;
            --selection;
        } while ( selection < 0 || selection > t->size );

        cout << endl << endl;
        update( db, (*t)[selection] );
    }
    else if ( option == 4 ) { //DELETE ENTRY ------------------------------------------
        clearBuffer( cin );
        int selection;

        do {
            cout << "Delete Entry #: ";
            cin >> selection;
            --selection;
        } while ( selection < 0 || selection > t->size );

        deleteEntry( db, (*t)[selection] );
    }
    else if ( option == 5 ) { //PRINT REPORT ------------------------------------------
        clearBuffer( cin );
        printReport( t );
    }
    else if ( option == 6 ) { //EXIT --------------------------------------------------
        return; //<----------------------------------------------------------------------------------------------------- RETURN
    }
}

void printEntryOptions( bool back_option ) {
    if ( back_option )
        cout << "-1. Back" << endl;

    for (int i = 0; i < Entry::FIELD_COUNT; ++i) {
        cout << i + 1 << ". " << Entry::fieldNames[i] << endl;
    }
}

void newEntry( Database& db ) {

    cout << "Enter Contact Information" << endl;
    Entry* entry = new Entry;

    //ID  --------------------------------------------------------------------------------------------------------------
    string id;
    do {
        cout << "Entry ID (9 numbers): ";
        cin >> id;
    } while ( !EntryValidate::validateId( id ) );
    (*entry)[Entry::ID] = id;

    clearBuffer( cin );

    //NAMES ------------------------------------------------------------------------------------------------------------
    string fname;
    do {
        cout << "First Name (50 characters or less): ";
        getline( cin, fname );
    } while ( !EntryValidate::validateName( fname ) );
    (*entry)[Entry::F_NAME] = fname;

    string mname;
    do {
        cout << "Middle Name/Initial (50 characters or less): ";
        getline( cin, mname );
    } while ( !EntryValidate::validateName( mname ) );
    (*entry)[Entry::M_NAME] = mname;

    string lname;
    do {
        cout << "Last Name (50 characters or less): ";
        getline( cin, lname );
    } while ( !EntryValidate::validateName( lname ) );
    (*entry)[Entry::L_NAME] = lname;

    string cname;
    do {
        cout << "Company Name (50 characters or less): ";
        getline( cin, cname );
    } while ( !EntryValidate::validateName( cname ) );
    (*entry)[Entry::COMPANY_NAME] = cname;

    //PHONE NUMBERS ----------------------------------------------------------------------------------------------------
    string mobile, home, office;
    do {
        cout << "Home Phone Number (Ex. (555)555-5555): ";
        getline( cin, home );
    } while ( !EntryValidate::validateNumber( home ) );
    (*entry)[Entry::HOME_NUMBER] = home;

    do {
        cout << "Mobile Phone Number (Ex. (555)555-5555): ";
        getline( cin, mobile );
    } while ( !EntryValidate::validateNumber( mobile ) );
    (*entry)[Entry::MOBILE_NUMBER] = mobile;

    do {
        cout << "Office Phone Number (Ex. (555)555-5555): ";
        getline( cin, office );
    } while ( !EntryValidate::validateNumber( office ) );
    (*entry)[Entry::OFFICE_NUMBER] = office;

    //EMAIL ------------------------------------------------------------------------------------------------------------
    string email;
    do {
        cout << "Email Address (Ex. abc@123.com): ";
        getline( cin, email );
    } while ( !EntryValidate::validateEmail( email ) );
    (*entry)[Entry::EMAIL] = email;

    //ADDRESS ----------------------------------------------------------------------------------------------------------
    string address;
    do {
        cout << "Address (50 characters or less): ";
        getline( cin, address );
    } while ( !EntryValidate::validateAddress( address ) );
    (*entry)[Entry::ADDRESS] = address;

    string city;
    do {
        cout << "City (50 characters or less):";
        getline( cin, city );
    } while ( !EntryValidate::validateAddress( city ) );
    (*entry)[Entry::CITY] = city;

    string state;
    do {
        cout << "State (50 characters or less): ";
        getline( cin, state );
    } while ( !EntryValidate::validateAddress( state ) );
    (*entry)[Entry::STATE] = state;

    string country;
    do {
        cout << "Country: ";
        getline( cin, country );
    } while ( !EntryValidate::validateAddress( country ) );
    (*entry)[Entry::COUNTRY] = country;

    string zip;
    do {
        cout << "Zip Code: ";
        getline( cin, zip );
    } while ( !EntryValidate::validateZip( zip ) );
    (*entry)[Entry::ZIP] = zip;

    //AFFILIATES -------------------------------------------------------------------------------------------------------
    //string affiliates;
    char cont_char;
    vector< vector<string> > affils;
    int counter = 0;

    cout << "Add Affiliates? (y/n): ";
    cin >> cont_char;

    while ( tolower( cont_char ) == 'y' ) {
        clearBuffer( cin );

        vector<string> subfields;

        string piece;
        do {
            cout << "Affiliate Name:";
            getline(cin, piece);
        } while ( !EntryValidate::validateName(piece) );

        subfields.push_back( piece );
        //affiliates += piece;

        do {
            cout << "Affiliate Phone Number (555)555-5555:";
            getline(cin, piece);
        } while ( !EntryValidate::validateNumber(piece) );

        subfields.push_back( piece );
        //affiliates += ", " + piece;

        do {
            cout << "Affiliate Email (abc@123.com):";
            getline(cin, piece);
        } while ( !EntryValidate::validateEmail(piece) );

        subfields.push_back( piece );
        //affiliates += ", " + piece + ";";

        affils.push_back( subfields );

        cout << "New Affiliate? (y/n) ";
        cin >> cont_char;
    }
    (*entry).deserializeAffiliates( affils );
    //(*entry)[Entry::AFFILIATES] = affiliates;

    //------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------

    //now add the node to the db
    QueryObject query;
    query.setAction( QueryObject::INSERT );

    do {
        Table *testTable = db.query(query, entry);
        if ( testTable->isEmpty()) {
            cout << "ID " << (*entry)[Entry::ID] << " already exists" << endl;
            cout << "Try a new ID? (y/n): ";
            cin >> cont_char;

            if ( tolower( cont_char ) == 'y' ) {
                do {
                    cout << "New ID: ";
                    cin >> id;
                } while ( !EntryValidate::validateId( id ) );
                (*entry)[Entry::ID] = id;
            }
        } else {
            cont_char = 'n';
            cout << "Entry Added" << endl << endl;
        }
    } while ( tolower( cont_char ) == 'y' );

}

void update( Database& db, Entry* entry ) {
    Table* table;
    bool editing_affiliates = false;

    //update without knowing the entry
    if ( entry == nullptr ) {
        string id;
        do {
            cout << "ID: ";
            getline(cin, id);
        } while ( !EntryValidate::validateId( id ) );

        QueryObject query;
        query.setAction( QueryObject::SELECT );
        query.setCondition( Entry::ID, QueryObject::EQUALS, id );

        table = db.query( query );

        if ( table->isEmpty() ) {
            cout << "No Entries found" << endl;
        } else {
            update( db, (*table)[0] );
        }

    }

    //update with the entry
    else {
        cout << "-1. Back" << endl;
        for ( int i = 0; i < Entry::FIELD_COUNT; ++i ) {
            if ( Entry::fieldNames[i] != Entry::ID ) {
                cout << i << ". " << Entry::fieldNames[i] << " = " << (*entry)[Entry::fieldNames[i]] << endl;
            }
        }

        //get the field the user wants to edit
        int selection;
        cout << endl << "Field to Edit: ";
        do {
            cin >> selection;
            if ( selection == -1 ) {
                break;
            } else {
            }
        } while ( selection < -1 || selection == 0 || selection > Entry::FIELD_COUNT );

        cout << endl << endl;

        string value;
        vector<string> columns;

        // -------------------------------------------------------------------------------------------------------------
        // EXIT
        // -------------------------------------------------------------------------------------------------------------
        if ( selection == -1 ) {
            return; // <------------------------------------------------------------------------------------------------ RETURN
        }

        // -------------------------------------------------------------------------------------------------------------
        // EDIT AFFILIATES
        // -------------------------------------------------------------------------------------------------------------
        else if ( selection == 14 ) {
            editing_affiliates = true;
            editAffiliate( entry );
        }

        // -------------------------------------------------------------------------------------------------------------
        // EDIT ENTRY FIELD
        // -------------------------------------------------------------------------------------------------------------
        else {
            do {
                clearBuffer( cin );
                cout << "New " << Entry::fieldNames[selection] << " value: ";
                getline( cin, value );
            } while ( !( EntryValidate::validate( Entry::fieldNames[selection], value ) ) );
            columns.push_back( Entry::fieldNames[selection] );
        }

        // -------------------------------------------------------------------------------------------------------------
        // SUBMIT CHANGES
        // -------------------------------------------------------------------------------------------------------------
        //only set the field value if it is not changing the affiliates
        //because the affiliates have already been set
        if ( !editing_affiliates ) {
            (*entry)[Entry::fieldNames[selection]] = value;
        }

        //set up a query
        QueryObject query;
        query.setAction( QueryObject::UPDATE );
        query.setColumns( columns );
        query.setCondition( Entry::ID, QueryObject::EQUALS, (*entry)[Entry::ID] );

        cout << endl << endl << (*entry)[Entry::AFFILIATES] << endl << endl;

        cout << "Updating...";
        table = db.query( query, entry );

        if ( table->isEmpty() ) {
            cout << "Failed" << endl << endl;
        } else {
            cout << "Succeeded" << endl << endl;
            cout << *table << endl << endl;
        }

    }


}

void editAffiliate( Entry* entry ) {
    cout << endl << endl << endl;
    cout << "EDITING AFFILIATES--------------------------------------------------" << endl;
    cout << endl << endl << endl;
    //edit affiliates
    vector< vector<string> > affils;
    entry->serializeAffiliates( affils );
    int selection;

    do {
        cout << "Affiliate Actions---------------------------------------------" << endl;
        cout << "-1. Back" << endl;
        cout << "1. Add Affiliate" << endl;
        if ( affils.size() > 0 ) {
            cout << "2. Update Affiliate" << endl;
            cout << "3. Delete Affiliate" << endl;
        }
        cout << "Selections: ";
        cin >> selection;

        if ( selection == -1 ) {
            return; // <---------------------------------------------------------------------------------------- RETURN
        }
        cout << endl << endl;
    } while ( selection < 1 || selection > 3 );


    // -----------------------------------------------------------------------------------------------------------------
    // UPDATE AFFILIATE --------------------------------------
    // -----------------------------------------------------------------------------------------------------------------
    if ( selection == 2 && affils.size() > 0 ) { // UPDATE AFFILIATE ---------------------------------------------------

        //print out affiliates
        for (  int i = 0; i < affils.size(); ++i ) {
            cout << i + 1 << ". ";
            for (int j = 0; j < affils[i].size(); ++j) {

                cout << affils[i][j] << " ";
            }
            cout << endl;
        }

        do {
            cout << "Affilate #: ";
            cin >> selection;
            --selection;
        } while ( selection < 0 || selection > affils.size() );

        //print out the selected affiliate
        for ( int i = 0; i < affils[selection].size(); ++i ) {
            cout << affils[selection][i] << " ";
        }

        cout << endl;
        int currentAffil = selection;

        do {
            cout << "Update Affiliate----------------------------------" << endl;

            do {
                cout << "-1. Back" << endl;
                cout << "1. Name" << endl;
                cout << "2. Phone" << endl;
                cout << "3. E-mail" << endl;
                cout << "Selection: ";
                cin >> selection;
                cout << endl << endl;

                if ( selection == -1 ) {
                    break;
                }
            } while ( selection < 1 || selection > 3 );

            string val;

            clearBuffer( cin );
            if (selection == 1) { // UPDATE AFFILIATE ----------------------------------------------------------
                do {
                    cout << "New Name: ";
                    getline(cin, val);
                } while ( !EntryValidate::validateName(val) );
                affils[currentAffil][--selection] = val;
                entry->deserializeAffiliates( affils );
            } else if (selection == 2) {
                do {
                    cout << "New Phone: ";
                    getline(cin, val);
                } while ( !EntryValidate::validateNumber(val) );
                affils[currentAffil][--selection] = val;
                entry->deserializeAffiliates( affils );
            } else if (selection == 3) {
                do {
                    cout << "New Email: ";
                    getline(cin, val);
                } while ( !EntryValidate::validateName(val) );
                affils[currentAffil][--selection] = val;
                entry->deserializeAffiliates( affils );
            }

        } while ( selection != -1 );

    }

    // -----------------------------------------------------------------------------------------------------------------
    // ADD AFFILIATE --------------------------------------
    // -----------------------------------------------------------------------------------------------------------------
    else if ( selection == 1 ) { // ADD AFFILIATE -----------------------------------------
        clearBuffer( cin );

        cout << "Add Affiliate----------------------------------" << endl;

        string name, phone, email;
        do {
            cout << "Name: ";
            getline( cin, name );
        } while ( !EntryValidate::validateName( name ) );

        do {
            cout << "Phone (555)555-5555: ";
            getline( cin, phone );
        } while ( !EntryValidate::validateNumber( phone ) );

        do {
            cout << "Email: ";
            getline( cin, email );
        } while ( !EntryValidate::validateEmail( email ) );

        vector<string> newAffil;
        newAffil.push_back( name );
        newAffil.push_back( phone );
        newAffil.push_back( email );

        affils.push_back( newAffil );
    }

    // -----------------------------------------------------------------------------------------------------------------
    // DELETE AFFILIATE --------------------------------------
    // -----------------------------------------------------------------------------------------------------------------
    else if ( selection == 3 && affils.size() > 0 ) { // DELETE AFFILIATE --------------------------------------

        cout << "Delete Affiliate----------------------------------" << endl;

        //print out affilaites
        for (  int i = 0; i < affils.size(); ++i ) {
            cout << i + 1 << ". ";
            for (int j = 0; j < affils[i].size(); ++j) {

                cout << affils[i][j] << " ";
            }
            cout << endl;
        }

        do {
            cout << "Affiliate #: ";
            cin >> selection;
            --selection;
        } while ( selection < 0 || selection > affils.size() );

        affils.erase( affils.begin() + selection );

    }
    entry->deserializeAffiliates( affils );
}

void deleteEntry( Database& db, Entry* entry ) {
    //deletes an entry from the database
    //if entry passed in nullptr, we must get the information
    //necessary to delete the entry
    //If the entry is not nullptr, just set of a delete query and pass in the entry

    Table* table;

    if ( entry == nullptr ) {
        QueryObject query;
        getQueryCondition(query, true);
        table = db.query( query );
    }
    else {
        QueryObject query;
        query.setAction( QueryObject::DELETE );
        query.setCondition( Entry::ID, QueryObject::EQUALS, (*entry)[Entry::ID] );
        table = db.query( query );
    }

    cout << "Deleting...";

    if ( table->isEmpty() ) {
        cout << "Failed" << endl << endl;
    } else {
        cout << "Succeeded" << endl << endl;
    }
}

void getQueryCondition(QueryObject &query, bool mode_toggle) {

    bool cont = true;
    string query_key;
    string query_mode;
    string query_value;

    do {

        //clearBuffer( cin );

        cout << "Which field would you like to search on?" << endl;

        printEntryOptions( );

        cout << "Enter 1 field number. Press enter to continue" << endl;
        cout << "Field: ";

        int field_number;

        //get the field from the user
        cin >> field_number;


        //decrement the number entered because the fieldNames array starts at 0
        --field_number;

        if ( !( field_number < 0 || field_number > Entry::FIELD_COUNT ) ) {
            query_key = Entry::fieldNames[field_number];
            cont = false;
        } else {
            cont = true;
        }

    } while ( cont );

    cout << endl << endl;

    do {

        clearBuffer( cin );

        cout << "What mode would you like to search in?" << endl;
        cout << "1. Contains ";
        if ( mode_toggle ) {
            cout << "(searches for a value occurring in a field, the first one encountered will be deleted)" << endl;
        } else {
            cout << "(searches for a value occurring in a field)" << endl;
        }
        cout << "2. Equals";
        if ( mode_toggle ) {
            cout << "(deletes an exact match, if found)" << endl;
        } else {
            cout << "(searches for exact matches, may return zero entries)" << endl;
        }
        cout << ">" << endl;

        int mode;

        cin >> mode;

        if ( mode != 1 && mode != 2 ) {
            cont = true;
        } else {
            if ( mode == 1 ) {
                query_mode = QueryObject::CONTAINS;
            } else {
                query_mode = QueryObject::EQUALS;
            }
            cont = false;
        }

    } while ( cont );

    clearBuffer( cin );

    cout << endl << endl;

    do {
        cout << "What value are you searching for (must include at least 1 character)?" << endl;
        cout << ">";
        getline(cin, query_value);
    } while ( query_value.length() < 1 );

    query.setCondition( query_key, query_mode, query_value );

}

void clearBuffer( istream& in ) {
    in.clear();
    in.ignore(256, '\n');
}

void printReport( Table* t ) {
    string filename;
    cout << "What file would you like to print the report?" << endl;
    getline( cin, filename );

    ofstream outfile;
    outfile.open( filename );

    if ( outfile ) {
        cout << "Printing to " << filename << endl;
        outfile << *t;
        cout << "Report printed" << endl << endl;
    } else {
        cout << "Could not open file" << endl << endl;
    }

}