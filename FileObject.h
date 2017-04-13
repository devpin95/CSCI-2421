//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                          FileObject.h
//                                    Devin Piner - 107543409
//                                         April 13, 2017
//
//                               Interface for the FileObject class
//                  Uses fopen() to create files that temporarily store chunks of data
//                   on deletion of this object, the file will be closed and removed.
//                        On every open(), the file is opened in append mode
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//  Public Functions
//
//Table( vector<Entry::e_type );
//  A constructor that accepts a vector of Entry::e_type as keys to the columns of the table
//  These keys will limit the amount of information that the table holds
//
//bool insert( const Entry& )
//  Accepts and Entry to be inserted into the table. Returns true if successful, false in unsuccessful
//
//Entry& operator( int )
//  Returns an Entry from the specified row of the table
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//UPDATES
//private:
//  readfile(ifstream&)
//
//successfully reads in data

#ifndef HW9_FILEOBJECT_H
#define HW9_FILEOBJECT_H

#include <iostream>
#include <stdio.h>
#include <string>

using std::string;

class FileObject {
public:
    FileObject() = delete;
    FileObject( const string& );
    ~FileObject();
    bool append(const string&);
    string filename;
private:
    FILE * file;
    bool is_open = false;
    bool close();
    bool open();
};


#endif //HW9_FILEOBJECT_H