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

Table* Database::query( const QueryObject& query ) {

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

    string readstring;
    stringstream ss;
    string pipe = "|"; //should always = | or empty
    bool cont = true;

    int count = 0;

    while ( !file.eof() ) {

        Entry* entryPtr = Entry::readEntryFromFile( file );
        cout << "NEW ENTRY: " << entryPtr->operator[](Entry::ID) << endl;

        hashes.insert( entryPtr );
        delete entryPtr;
        ++count;
    }
    cout << count << endl;
    hashes.report();
}

Table* Database::select( const QueryObject& query ) {

    //loop through the hash files and read in each value
    for( int i = 0; i < hashes.prime; ++i ) {
        if ( hashes.files[i] != nullptr ) {
            Entry* entry = Entry::readEntryFromFile( hashes.files[i]->getFile() );

        }
    }

}

Table* Database::selectExactID( const QueryObject& query ) {
    //since we are searching for an exact ID, if we hash it and find that the FileObject at that hash
    //is null, we now that the ID is not in the database.
    //If it is not null, we know what the ID is in the file in that hashes's bucket, so we can open the file
    //and read the entries into a binary tree and search that for the ID the get the full entry

    //convert the string to a long because the hashing function
    //requires it to be a long, the hash it
    auto ID_long = long(stol( query.getCondition().value ));
    auto ID_hash = hashes.hasher(ID_long);

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
        Entry *entry_key = new Entry;
        entry_key->operator[](Entry::ID) = query.getCondition().value;

        //search the tree for the node
        Node *entry = tree.findNode(entry_key, tree.Root());

        //if the search found a node, insert the node data into the table
        if (entry != nullptr) {
            Entry* row = new Entry( entry->Key() );
            table->insert( row );
        }

        delete entry_key;
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
    if ( query.getCondition().operations == QueryObject::EQUALS) {
        is_match = ( entry[ key ] == value );
    }

    //CONTAINS- field contains the value
    else if ( query.getCondition().operations == QueryObject::CONTAINS ) {
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