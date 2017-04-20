//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                            Entry.h
//                                    Devin Piner - 107543409
//                                         April 1, 2017
//
//                                Interface for the Entry class
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//Static Class Variables -----------------------------------------------------------------------------------------------
//  ID = id
//  F_NAME = f_name
//  M_NAME = m_name
//  L_NAME = l_name
//  COMPANY_NAME = company_number
//  HOME_NUMBER = home_number
//  OFFICE_NUMBER = office_number
//  MOBILE_NUMBER = mobile_number
//  EMAIL = email
//  ADDRESS = address
//  CITY = city
//  STATE = state
//  ZIP = zip
//  COUNTRY = country
//  AFFILIATES = affiliates
//
//  Entry()
//      Default constructor
//
//  string& operator[](const string&)
//      Overloaded operator[], returns the value of the field name passed in, changing the returned
//      string will result in the value being changed in the class
//
//  const string& operator[](int)
//      Overloaded operator[], returns the name of field at the index passed in. The string will be
//      the exact name of the field. Used to get the names of all the fields of the Entry class
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//UPDATES:
//Added destructor
//changed const char* to string for easier use in Database class

#ifndef CSCI2421_ENTRY_H
#define CSCI2421_ENTRY_H

#include <map>
#include <string>

using std::string;
using std::map;

class Entry {
public:

    //static variables to reference entry fields outside of the class
    static constexpr const char* ID = "id";;
    static const string F_NAME;
    static const string M_NAME;
    static const string L_NAME;
    static const string COMPANY_NAME;
    static const string HOME_NUMBER;
    static const string OFFICE_NUMBER;
    static const string MOBILE_NUMBER;
    static const string EMAIL;
    static const string ADDRESS;
    static const string CITY;
    static const string STATE;
    static const string ZIP;
    static const string COUNTRY;
    static const string AFFILIATES;
    static const int FIELD_COUNT = 15;

    static const string fieldNames[ FIELD_COUNT ];

    Entry(); //Default Constructor
    ~Entry();
    string& operator[](const string&);
    string& operator[](const int&);
    bool operator<( Entry* );

private:
    map<string, string> fields; //key = fieldName, value = fieldName value

};


#endif //CSCI2421_ENTRY_H
