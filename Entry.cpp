#include "Entry.h"

//const string Entry::ID; // = "id";
const string Entry::F_NAME = "fname";
const string Entry::M_NAME = "mname";
const string Entry::L_NAME = "lname";
const string Entry::COMPANY_NAME = "cname";
const string Entry::HOME_NUMBER = "home_number";
const string Entry::OFFICE_NUMBER = "office_number";
const string Entry::MOBILE_NUMBER = "mobile_number";
const string Entry::EMAIL = "email";
const string Entry::ADDRESS = "address";
const string Entry::CITY = "city";
const string Entry::STATE = "state";
const string Entry::ZIP = "zip";
const string Entry::COUNTRY = "country";
const string Entry::AFFILIATES = "affiliates";

const string Entry::fieldNames[ Entry::FIELD_COUNT ] = {
        ID, F_NAME, M_NAME, L_NAME, COMPANY_NAME, HOME_NUMBER, OFFICE_NUMBER,
        MOBILE_NUMBER, EMAIL, ADDRESS, CITY, STATE, ZIP, COUNTRY, AFFILIATES
};

Entry::Entry() {
    for ( int i = 0; i < FIELD_COUNT; ++i ) {
        fields[ fieldNames[i] ] = "";
    }
}

Entry::~Entry() {
    for ( int i = 0; i < FIELD_COUNT; ++i ) {
        fields[ fieldNames[i] ] = "";
    }
}

string& Entry::operator[](const string& column) {
    return fields[column];
}

string& Entry::operator[](const int& i) {
    return fields[ fieldNames[i] ];
}

bool Entry::operator<( Entry* R ) {
    bool is_same = true;

    if ( this->operator[](Entry::ID) != R->operator[](Entry::ID)  ) {
        is_same = false;
    }

    return is_same;
}

bool Entry::operator==( Entry* r ) {
    return fields[ID] == r->fields[Entry::ID];
}

Entry* Entry::operator=( Entry* r ) {
    Entry& right = *r;
    Entry& left = *this;

    left[ID] = right[ID];
    left[F_NAME] = right[F_NAME];
    left[M_NAME] = right[M_NAME];
    left[L_NAME] = right[L_NAME];
    left[COMPANY_NAME] = right[COMPANY_NAME];
    left[HOME_NUMBER] = right[HOME_NUMBER];
    left[OFFICE_NUMBER] = right[OFFICE_NUMBER];
    left[MOBILE_NUMBER] = right[MOBILE_NUMBER];
    left[EMAIL] = right[EMAIL];
    left[ADDRESS] = right[ADDRESS];
    left[CITY] = right[CITY];
    left[STATE] = right[STATE];
    left[COUNTRY] = right[COUNTRY];
    left[AFFILIATES] = right[AFFILIATES];

    return this;
}

Entry* Entry::readEntryFromFile( fstream& file ) {
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
Entry* Entry::readEntryFromFile( ifstream& file ) {
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