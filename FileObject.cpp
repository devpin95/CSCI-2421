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
}

FileObject::~FileObject() {
    if ( is_open ) {
        is_open = close();
    }
    if ( remove( filename.c_str() ) != 0 ) {
        std::cout << "Success" << std::endl;
    }
    filename = "";

}

bool FileObject::append(const string& data) {
    bool success = false;

    if ( is_open ) {
        fputs( data.c_str(), file );
    } else {
        open();
        success = append( data );
    }

    return success;
}

bool FileObject::open() {
    is_open = false;
    if ( !filename.empty() ) {
        file = fopen( filename.c_str(), "a" );
        if ( file!= nullptr ){
            is_open = true;
        }
    }

    return is_open;
}

bool FileObject::close() {
    if ( is_open ) {
        fclose( file );
    }

    return is_open;
}