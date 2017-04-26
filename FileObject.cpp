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
    } else if ( is_open_for_reading ) {
        is_open_for_reading = close();
    }
    if ( remove( filename.c_str() ) != 0 ) {
        std::cout << "Success" << std::endl;
    }
    filename = "";

}

bool FileObject::append(const string& data) {
    bool success = false;

    if ( is_open_for_writing ) {
        if ( file << data ) {
            success = true;
        }
    }

    return success;
}

bool FileObject::setForWriting() {

    //first, close the file if it is open and not in the correct mode
    //The reopen the file in the correct mode and make sure that is was successful
    if ( !is_open_for_writing ) {

        if ( file.is_open() ) {
            close();
        }

        if (!filename.empty()) {
            //http://www.cplusplus.com/forum/general/25076/
            //used this to help with problem where file was getting erased every time it was opened

            //if the file has not yet been opened, open it so that any data in the file is erased
            if ( !initial_state ) {
                file.open(filename, std::fstream::out | std::fstream::app);
            } else {
                file.open( filename, std::fstream::out );
                initial_state = false;
            }
            if (file.is_open()) {
                is_open_for_writing = true;
                is_open_for_reading = false;
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
            close();
        }

        if (!filename.empty()) {
            file.open(filename, std::fstream::in);
            if (file.is_open()) {
                std::cout << "SETTING FOR READINg" << std::endl;
                is_open_for_reading = true;
                is_open_for_writing = false;
            }
        }
    } else {
        //file.seekg( 0, std::ios_base::beg );
        file.close();
        file.open(filename, std::fstream::in);
    }

    return is_open_for_reading;
}

bool FileObject::close() {
    if ( is_open_for_writing ) {
        //flush the file before closing it
        //without doing this, none of the data will be writen to disk
        file.flush();
        file.close();
    } else if ( is_open_for_reading ) {
        file.close();
    }

    return is_open_for_writing;
}

void FileObject::erase( void ) {
    //to erase the contents of a file, close it, then open it again
    //in a mode that empties the contents of the file.
    //re-open it for writing and reset the initial_state flag
    close();
    file.open(filename, std::fstream::out);
    setForWriting();
    initial_state = true;
}