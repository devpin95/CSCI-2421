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

#include "FileObject.h"

FileObject::FileObject( const string& fn ) {
    filename = fn;
    setForWriting();
}

FileObject::~FileObject() {
    if ( is_open_for_writing ) {
        is_open_for_writing = close();
    }
    if ( remove( filename.c_str() ) != 0 ) {
        std::cout << "Success" << std::endl;
    }
    filename = "";

}

bool FileObject::append(const string& data) {
    bool success = false;

    if ( is_open_for_writing ) {
        file << data;
        success = true;
    }

    return success;
}

bool FileObject::setForWriting() {

    if ( !is_open_for_writing ) {
        if (!filename.empty()) {
            file.open(filename, std::fstream::out);
            if (file.is_open()) {
                is_open_for_writing = true;
            }
        }
    }

    return is_open_for_writing;
}

bool FileObject::setForReading() {

    //first, close the file if it is open and not in the correct mode
    //The reopen the file in the correct mode and make sure that is was successful
    if ( !is_open_for_reading ) {

        if ( file.is_open() ) {
            file.close();
        }

        if (!filename.empty()) {
            file.open(filename, std::fstream::in);
            if (file.is_open()) {
                is_open_for_writing = true;
            }
        }
    }

    return is_open_for_reading;
}

bool FileObject::close() {
    if ( is_open_for_writing ) {
        file.close();
    }

    return is_open_for_writing;
}