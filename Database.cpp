//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                          Database.cpp
//                                    Devin Piner - 107543409
//                                         April 11, 2017
//
//                              Implementation for the Database class
//                  Reads in data from the database text file and stores it to be queried
//          using the QueryString class and returning a Table class with all the requested entries
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

//Table& Database::query(const QueryString&) {
//
//}
//
//Table& Database::query(const QueryString&, const Table&) {
//
//}

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

    while ( cont ) {
        Entry* entryPtr = new Entry;
        Entry& newEntry = *entryPtr;

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


        //if the next line is the |, check the next character
        //if the next character is EOF, there is no more data to be read
        //if it is not EOF, there is more data to be read
        if ( readstring == pipe ) {
            int c = file.peek();
            if ( c == EOF ) {
                cont = false;
            }

        }

        for ( int i = 0; i < Entry::FIELD_COUNT; ++i ) {
            cout << newEntry[i] << endl;
        }
        cout << "|" << endl << endl;

        data.addNode( entryPtr );
        ++count;
    }
    cout << count << endl;
}