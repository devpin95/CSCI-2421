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

#ifndef CSCI2421_ENTRYPRINTER_H
#define CSCI2421_ENTRYPRINTER_H

#include <vector>
#include "Entry.h"

using std::vector;

class EntryPrinter {
public:
    EntryPrinter();
    void setKeys( const vector<Entry::e_type>& );
    void print( const Entry& );
    void print( const Entry&, const vector<Entry::e_type>& );

private:
    vector<Entry::e_type> keys;
};


#endif //CSCI2421_ENTRYPRINTER_H
