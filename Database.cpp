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

Table& Database::query( const QueryObject& query ) {

    Table* table = new Table( query.getColumns() );

    switch ( query.getAction() ) {
        case QueryObject::SELECT :
            //select
            select( query );
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

    return *(table);
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

        Entry* entryPtr = readEntryFromFile( file );

        hashes.insert( entryPtr );
        delete entryPtr;
        ++count;
    }
    cout << count << endl;
    hashes.report();
}

Table& Database::select( const QueryObject& query ) {

    //loop through the hash files and read in each value
    for( int i = 0; i < hashes.prime; ++i ) {
        if ( hashes.files[i] != nullptr ) {
            Entry* entry = readEntryFromFile( hashes.files[i]->getFile() );

        }
    }
}

Table& Database::selectExactID( const string& id ) {
    //convert the string to a long because the hashing function
    //requires it to be a long, the hash it
    auto ID_long = long(stol( id ));
    auto ID_hash = hashes.hash( ID_long );

    //tree to hold all of the entries
    BSTree tree;

    //while the file in the hash table is not at EOF
    while ( !( hashes.files[ID_hash]->getFile().eof() ) ) {
        //create new entries and add them to the tree
        Entry* entry = readEntryFromFile( hashes.files[ID_hash]->getFile() );
        tree.addNode( entry );
    };

    tree.findNode(  )

}

Entry* Database::readEntryFromFile( fstream& file ) {
    Entry* entryPtr = new Entry;
    Entry& newEntry = *entryPtr;
    string readstring;
    string pipe = "|"; //should always = | or empty

    getline( file, newEntry[ Entry::ID ] );
    getline( file, newEntry[ Entry::F_NAME ] );
    getline( file, newEntry[ Entry::M_NAME ] );
    getline( file, newEntry[ Entry::L_NAME ] );
    getline( file, newEntry[ Entry::COMPANY_NAME ] );
    getline( file, newEntry[ Entry::HOME_NUMBER ] );
    getline( file, newEntry[ Entry::OFFICE_NUMBER ] );
    getline( file, newEntry[ Entry::EMAIL ] );
    getline( file, newEntry[ Entry::MOBILE_NUMBER ] );
    getline( file, newEntry[ Entry::ADDRESS ] );
    getline( file, newEntry[ Entry::CITY ] );
    getline( file, newEntry[ Entry::STATE ] );
    getline( file, newEntry[ Entry::ZIP ] );
    getline( file, newEntry[ Entry::COUNTRY ] );

    getline(file, readstring);

    while ( readstring != pipe ) {
        newEntry[Entry::AFFILIATES] += readstring;
        if ( file.peek() != '|' ) {
            newEntry[Entry::AFFILIATES] += "\n";
        }
        getline(file, readstring);
    }

    return entryPtr;
}