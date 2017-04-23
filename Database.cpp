//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                          Database.cpp
//                                    Devin Piner - 107543409
//                                         April 11, 2017
//
//                              Implementation for the Database class
//                  Reads in data from the database text file and stores it to be queried
//          using the QueryObject class and returning a Table class with all the requested entries
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

#include "Database.h"

Database::Database() {
 //EMPTY BODY
}

Database::Database(string file) {
    filename = file;
}

bool Database::connect(string file) {
    setDatabase( file );
    bool status = false;

    ifstream infile;
    infile.open( filename );

    if ( infile ) {
        status = true;
        readfile( infile );
    } else {
        status = false;
    }

    infile.close();

    return status;
}

bool Database::disconnect() {

    return false;
}

Table* Database::query(const QueryObject &query, Entry *in) {
    //query
    //PRECONDITION: query is a valid QueryObject. If inserting, in is not null
    //POSTCONDITION: The query action is carried out. For actions that failed, an empty
    //table is returned from the function

    Table* table;

    switch ( query.getAction() ) {
        case QueryObject::SELECT :
            //select
            if ( query.getCondition().key == Entry::ID ) {
                table = selectExactID( query );
            }
            else {
                select( query );
            }
            break;
        case QueryObject::UPDATE :
            //update
            break;
        case QueryObject::INSERT :
            //insert
            table = insert( in );
            break;
        case QueryObject::DELETE :
            //delete
            break;
    }

    return table;
}

void Database::readfile( ifstream& file ) {
//    117094337
//    Roderick
//    L.
//    Coons
//    Grey Global Group Inc.
//    (324)257-3210
//    (888)475-6767
//    roderick.coons@grey.com
//    (920)615-7364
//    85840 30th Lane
//    Cheyenne Wells
//    MO
//    29353-4042
//    United States
//    Troy Borges,(636)553-5433,tborges2450@oic.biz;
//    Bob Corcoran,(808)368-6692,bcorcoran@comcast.net;
//    Mike Franklin,(340)784-9249,mfranklin@qwest.com;
//    Audie Boren,(567)906-9017,aboren5@yahoo.com;
//    Archie Packard,(308)686-9564,apackard@oic.biz;
//    |

    int count = 0;

    while ( !file.eof() ) {

        Entry* entryPtr = Entry::readEntryFromFile( file );
        //cout << "NEW ENTRY: " << entryPtr->operator[](Entry::ID) << endl;

        hashes.insert( entryPtr );
        delete entryPtr;
        ++count;
    }
    cout << count << endl;
    //hashes.report();
}

Table* Database::select( const QueryObject& query ) {

    //make a new table with the current query's columns
    Table* table = new Table( query.getColumns() );

    //loop through the hash files and read in each value
    for( int i = 0; i < hashes.prime; ++i ) {
        if ( hashes.files[i] != nullptr ) {

            BSTree tree;

            //while the file in the hash table is not at EOF
            while (!(hashes.files[i]->getFile().eof())) {
                //create new entries and add them to the tree
                Entry *entry = Entry::readEntryFromFile(hashes.files[i]->getFile());
                tree.addNode(entry);
            };
        }
    }

    return table;
}

Table* Database::selectExactID( const QueryObject& query ) {
    //since we are searching for an exact ID, if we hash it and find that the FileObject at that hash
    //is null, we now that the ID is not in the database.
    //If it is not null, we know what the ID is in the file in that hashes's bucket, so we can open the file
    //and read the entries into a binary tree and search that for the ID the get the full entry

    //convert the string to a long because the hashing function
    //requires it to be a long, the hash it
    auto ID_long = long(stol( query.getCondition().value ));
    auto ID_hash = hashes.hashify(ID_long);

    //tree to hold all of the entries
    BSTree tree;
    Table *table = new Table(query.getColumns());

    //check the hash tables FileObject to see if it exists
    if ( hashes.files[ID_hash]!= nullptr ) {

        //make sure that the file is ready to be read
        hashes.files[ID_hash]->setForReading();

        //while the file in the hash table is not at EOF
        while (!(hashes.files[ID_hash]->getFile().eof())) {
            //create new entries and add them to the tree
            Entry *entry = Entry::readEntryFromFile(hashes.files[ID_hash]->getFile());
            tree.addNode(entry);
        };


        //create a new entry with the target ID so that the search can compare with
        //the values in the tree
        Entry *temp_entry = new Entry;
        temp_entry->operator[](Entry::ID) = query.getCondition().value;

        //search the tree for the node
        Node *entry = tree.findNode(temp_entry, tree.Root());

        //if the search found a node, insert the node data into the table
        if (entry != nullptr) {
            //make a copy of the node key so that it is not deleted at the end of the function
            //Table now owns the entry pointer
            Entry* row = new Entry( entry->Key() );
            table->insert( row );
        }

        //delete the temp entry
        delete temp_entry;
    }

    return table;

}

Table* Database::insert( Entry* entryPtr ) {
    // insert()
    // PRECONDITION: All data in entry is value, ID must be included
    //
    // POSTCONDITION: Entry is added to the database. If insert fails, an empty table
    // is returned

    Table* table = nullptr;

    Entry& entry = *entryPtr;

    auto ID_long = long(stol( entry[Entry::ID] ));
    auto ID_hash = hashes.hashify(ID_long);

    //test to see if there is an entry at hashes.files[ID_hash]
    if ( hashes.files[ID_hash] == nullptr ) {
        //if the file does not exists, then there must not be an entry with the same
        //ID that already exists
        hashes.insert( entryPtr );
    } else {
        //There must be at least one entry that hashes to the same value
        //So we need to search that file to see if an entry with the same
        //id already exists. Make a query with the correct data and see what
        //the selectExactId function returns
        QueryObject query;
        vector<string> cols = { Entry::ID };
        query.setColumns( cols );
        query.setAction( QueryObject::SELECT );
        query.setCondition( Entry::ID, QueryObject::EQUALS, entry[Entry::ID] );
        table = selectExactID( query );

        if ( table->isEmpty() ) {
            //the table is empty. That means that an entry does not exists with the same ID
            hashes.insert( entryPtr );
        } else {
            //The table is not empty. That means that an entry does exists with the same ID
            //so we can add the entry to the database
            delete table;
            vector<string> keys;
            table = new Table( keys );
        }

    }

    return table;
}

bool Database::evaluateConditions( Entry* entryPtr, const QueryObject& query ) {
    bool is_match = false; //bool to hold the result of the condition check

    //dereference the pointer so that we can access it like normal
    Entry& entry = *entryPtr;

    //First, check what condition we are checking for
    //EQUALS (exact match)
    //CONTAINS (field contains the value)

    string key = query.getCondition().key;
    string value = query.getCondition().value;

    //EQUALS - exact match
    if ( query.getCondition().operation == QueryObject::EQUALS) {
        is_match = ( entry[ key ] == value );
    }

    //CONTAINS- field contains the value
    else if ( query.getCondition().operation == QueryObject::CONTAINS ) {
        //Use find to search the field for the value. If the value is found in
        //the field, it will return an unsigned int. If not found, string::npos
        //string::find referenced from
        //http://www.cplusplus.com/reference/string/string/find/
        if ( key.find( value ) != string::npos ) {
            is_match = true;
        }
    }

    return is_match;
}