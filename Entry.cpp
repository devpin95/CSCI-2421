#include "Entry.h"

const string Entry::ID = "id";
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

