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

Table* Database::query(const QueryObject &query, Entry *in) {
    //query
    //PRECONDITION: query is a valid QueryObject. If inserting, in is not null
    //POSTCONDITION: The query action is carried out. For actions that failed, an empty
    //table is returned from the function

    Table* table;

    switch ( query.getAction() ) {
        case QueryObject::SELECT :
            //select
            if ( query.getCondition().key == Entry::ID && query.getCondition().operation == QueryObject::EQUALS ) {
                table = selectExactID( query );
            }
            else {
                table = select( query );
            }
            break;
        case QueryObject::UPDATE :
            //update
            if ( query.getCondition().key == Entry::ID && query.getCondition().operation == QueryObject::EQUALS ) {
                table = updateExactID( query, in );
            }
            else {
                table = update( query, in );
            }
            break;
        case QueryObject::INSERT :
            //insert
            table = insert( in );
            break;
        case QueryObject::DELETE :
            //delete
            if ( query.getCondition().key == Entry::ID && query.getCondition().operation == QueryObject::EQUALS ) {
                table = delExactID( query );
            }
            else {
                table = del( query );
            }
            break;
    }

    return table;
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

    int count = 0;

    while ( !file.eof() ) {

        Entry* entryPtr = Entry::readEntryFromFile( file );
        //cout << "NEW ENTRY: " << entryPtr->operator[](Entry::ID) << endl;

        hashes.insert( entryPtr );
        delete entryPtr;
        ++count;
    }
    cout << count << endl;
    //hashes.report();
}

Table* Database::select( const QueryObject& query ) {

    //make a new table with the current query's columns
    Table* table = new Table( query.getColumns() );

    //loop through the hash files and read in each value
    for( int i = 0; i < hashes.prime; ++i ) {
        if ( hashes.files[i] != nullptr ) {

            BSTree tree;

            hashes.files[i]->setForReading();

            //while the file in the hash table is not at EOF
            while (!(hashes.files[i]->getFile().eof())) {
                //create new entries and add them to the tree
                Entry *entry = Entry::readEntryFromFile(hashes.files[i]->getFile());
                tree.addNode(entry);
            };

            //create a new eval object
            AddEvaluate eval;
            eval.tbl = table;
            eval.condition = query.getCondition();
            tree.inorder( tree.Root(), eval );

        }
    }

    return table;
}

Table* Database::selectExactID( const QueryObject& query ) {
    //since we are searching for an exact ID, if we hash it and find that the FileObject at that hash
    //is null, we now that the ID is not in the database.
    //If it is not null, we know what the ID is in the file in that hashes's bucket, so we can open the file
    //and read the entries into a binary tree and search that for the ID the get the full entry

    //convert the string to a long because the hashing function
    //requires it to be a long, the hash it
    auto ID_long = long(stol( query.getCondition().value ));
    auto ID_hash = hashes.hashify(ID_long);

    //tree to hold all of the entries
    BSTree tree;

    //return table
    Table *table = new Table(query.getColumns());

    //check the hash tables FileObject to see if it exists and that it is not empty
    if ( hashes.files[ID_hash]!= nullptr && hashes.counters[ID_hash] > 0 ) {

        //make sure that the file is ready to be read
        hashes.files[ID_hash]->setForReading();

        //while the file in the hash table is not at EOF
        while (!(hashes.files[ID_hash]->getFile().eof())) {
            //create new entries and add them to the tree
            Entry *entry = Entry::readEntryFromFile(hashes.files[ID_hash]->getFile());
            tree.addNode(entry);
        };


        //create a new entry with the target ID so that the search can compare with
        //the values in the tree
        Entry *temp_entry = new Entry;
        temp_entry->operator[](Entry::ID) = query.getCondition().value;

        //search the tree for the node
        Node *entry = tree.findNode(temp_entry, tree.Root());

        //if the search found a node, insert the node data into the table
        if (entry != nullptr) {
            //make a copy of the node key so that it is not deleted at the end of the function
            //Table now owns the entry pointer
            Entry* row = new Entry( entry->Key() );
            table->insert( row );
        }

        //delete the temp entry
        delete temp_entry;
    }

    return table;

}

Table* Database::update( const QueryObject& query, Entry* entryPtr ) {
    //make a new table with the current query's columns
    Table* table = new Table( query.getColumns() );

    //loop through the hash files and read in each value
    for( int i = 0; i < hashes.prime; ++i ) {
        if ( hashes.files[i] != nullptr ) {

            //tree to hold the entries
            BSTree tree;

            //make sure the file is ready to be read
            hashes.files[i]->setForReading();

            //while the file in the hash table is not at EOF
            while (!(hashes.files[i]->getFile().eof())) {
                //create new entries and add them to the tree
                Entry *entry = Entry::readEntryFromFile(hashes.files[i]->getFile());
                tree.addNode(entry);
            };

            //create a new eval object and traverse the tree
            //eval's node variable will hold a pointer to the node with the target entry
            DeleteEvaluate eval;
            eval.tbl = table;
            eval.condition = query.getCondition();
            tree.preorder( tree.Root(), eval );

            if ( !table->isEmpty() ) {
                Node* entry = eval.node;
                //if the table is not empty, then a value was found
                //rewrite the tree to disk

                //First, copy the entry passed to the entry in the tree before it gets rewritten to disk
                (*entry->Key()) = *entryPtr;

                //rewrite the file with the new information
                WriteEvaluate writer;
                writer.hashtable = &hashes;
                tree.postorder(tree.Root(), writer);

                //break out of the loop because we've deleted one of the entries
                break;
            }
        }
    }

    return table;
}

Table* Database::updateExactID( const QueryObject& query, Entry* entryPtr ) {

    //convert the string to a long because the hashing function
    //requires it to be a long, the hash it
    auto ID_long = long(stol( query.getCondition().value ));
    auto ID_hash = hashes.hashify(ID_long);

    //tree to hold all of the entries
    BSTree tree;

    //return table
    Table *table = new Table(query.getColumns());

    //check the hash tables FileObject to see if it exists and that it is not empty
    if ( hashes.files[ID_hash]!= nullptr && hashes.counters[ID_hash] > 0 ) {

        //make sure that the file is ready to be read
        hashes.files[ID_hash]->setForReading();

        //while the file in the hash table is not at EOF
        while (!(hashes.files[ID_hash]->getFile().eof())) {
            //create new entries and add them to the tree
            Entry *entry = Entry::readEntryFromFile(hashes.files[ID_hash]->getFile());
            tree.addNode(entry);
        };


        //create a new entry with the target ID so that the search can compare with
        //the values in the tree
        Entry *temp_entry = new Entry;
        temp_entry->operator[](Entry::ID) = query.getCondition().value;

        //search the tree for the node
        Node *entry = tree.findNode(temp_entry, tree.Root());

        //if the search found a node
        if (entry != nullptr) {
            //First, copy the entry data passed in to the data of the entry in the tree
            (*entry->Key()) = *entryPtr;

            //make a copy of the node key so that it is not deleted at the end of the function
            //Table now owns the entry pointer
            Entry* row = new Entry( entry->Key() );
            table->insert( row );

            //rewrite the file with the new information
            WriteEvaluate writer;
            writer.hashtable = &hashes;
            tree.postorder(tree.Root(), writer);
            hashes.counters[ID_hash] = writer.count;
        }

        //delete the temp entry
        delete temp_entry;
    }

    return table;
}

Table* Database::insert( Entry* entryPtr ) {
    // insert()
    // PRECONDITION: All data in entry is value, ID must be included
    //
    // POSTCONDITION: Entry is added to the database. If the insert succeeds, a table with the entry
    // is returned. If insert fails, an empty table is returned

    //return the table
    Table* table = nullptr;

    Entry& entry = *entryPtr;

    //convert the string to a long because the hashing function
    //requires it to be a long, the hash it
    auto ID_long = long(stol( entry[Entry::ID] ));
    auto ID_hash = hashes.hashify(ID_long);

    //test to see if there is an entry at hashes.files[ID_hash]
    if ( hashes.files[ID_hash] == nullptr ) {
        //if the file does not exists, then there must not be an entry with the same
        //ID, so we can directly insert the entry
        hashes.insert( entryPtr );
    } else {
        //otherwise, there must be at least one entry that hashes to the same value
        //So we need to search that file to see if an entry with the same
        //id already exists. Make a query with the correct data and see what
        //the selectExactId function returns
        QueryObject query;
        vector<string> cols = { Entry::ID };
        query.setColumns( cols );
        query.setAction( QueryObject::SELECT );
        query.setCondition( Entry::ID, QueryObject::EQUALS, entry[Entry::ID] );
        table = selectExactID( query );

        if ( table->isEmpty() ) {
            //the table is empty. That means that an entry does not exists with the same ID
            //Insert the entry, delete the old table and make a new one to hold the entry passed in
            hashes.insert( entryPtr );
            delete table;
            vector<string> keys;
            table = new Table( keys );
            table->insert( entryPtr );
        } else {
            //The table is not empty. That means that an entry does exists with the same ID
            //so we cannot add the entry to the database
            delete table;
            vector<string> keys;
            table = new Table( keys );
        }

    }

    return table;
}

Table* Database::del( const QueryObject& query ) {

    //return table
    Table *table = new Table(query.getColumns());

    //loop through the hash files and read in each value
    for( int i = 0; i < hashes.prime; ++i ) {
        if ( hashes.files[i] != nullptr ) {

            //tree to hold the entries
            BSTree tree;

            //make sure the file is ready to beread
            hashes.files[i]->setForReading();

            //while the file in the hash table is not at EOF
            while (!(hashes.files[i]->getFile().eof())) {
                //create new entries and add them to the tree
                Entry *entry = Entry::readEntryFromFile(hashes.files[i]->getFile());
                tree.addNode(entry);
            };

            //create a new eval object that will filter out entries
            //that do not fit the criteria
            DeleteEvaluate eval;
            eval.tbl = table;
            eval.condition = query.getCondition();
            tree.preorder( tree.Root(), eval );

            if ( !table->isEmpty() ) {
                //if the table is not empty, then a value was found
                //delete the node from the tree, and rewrite the tree to disk
                tree.deleteNode( eval.node->Key() );

                if ( hashes.counters[i] == 0 ) {
                    //if there are no entries in the file, just erase it
                    //by setting it back to an intial state
                    hashes.files[i]->erase();
                } else {
                    //if there is at least one entry in the file
                    //rewrite the tree to file with the entry removed
                    WriteEvaluate writer;
                    writer.hashtable = &hashes;
                    tree.postorder(tree.Root(), writer);
                    hashes.counters[i] = writer.count;
                }

                //break out of the loop because we've deleted one of the entries
                break;
            }
        }
    }

    return table;

}

Table* Database::delExactID( const QueryObject& query ) {
    //since we are searching for an exact ID, if we hash it and find that the FileObject at that hash
    //is null, we now that the ID is not in the database.
    //If it is not null, we know what the ID is in the file in that hashes's bucket, so we can open the file
    //and read the entries into a binary tree and search that for the ID the get the full entry

    //convert the string to a long because the hashing function
    //requires it to be a long, the hash it
    auto ID_long = long(stol( query.getCondition().value ));
    auto ID_hash = hashes.hashify(ID_long);

    //tree to hold all of the entries
    BSTree tree;
    Table *table = new Table(query.getColumns());

    //check the hash tables FileObject to see if it exists and that it is not empty
    if ( hashes.files[ID_hash]!= nullptr && hashes.counters[ID_hash] > 0 ) {

        //make sure that the file is ready to be read
        hashes.files[ID_hash]->setForReading();

        //while the file in the hash table is not at EOF
        while (!(hashes.files[ID_hash]->getFile().eof())) {
            //create new entries and add them to the tree
            Entry *entry = Entry::readEntryFromFile(hashes.files[ID_hash]->getFile());
            tree.addNode(entry);
        };


        //create a new entry with the target ID so that the search can compare with
        //the values in the tree
        Entry *temp_entry = new Entry;
        temp_entry->operator[](Entry::ID) = query.getCondition().value;

        //search the tree for the node
        Node *entry = tree.findNode(temp_entry, tree.Root());

        //if the search found a node, insert the node data into the table
        if (entry != nullptr) {
            //make a copy of the node key so that it is not deleted at the end of the function
            //Table now owns the entry pointer. Delete the node from the tree and decrement the count
            //of the hash table bucket
            Entry* row = new Entry( entry->Key() );
            table->insert( row );
            tree.deleteNode( entry->Key() );
            --hashes.counters[ID_hash];

            if ( hashes.counters[ID_hash] == 0 ) {
                //if the hash table bucket is empty, just reset the file to its initial state
                hashes.files[ID_hash]->erase();
            } else {
                //otherwise, rewrite the tree to file with the entry removed
                WriteEvaluate writer;
                writer.hashtable = &hashes;
                tree.postorder(tree.Root(), writer);
                hashes.counters[ID_hash] = writer.count;
            }
        }

        //delete the temp entry
        delete temp_entry;
    }

    return table;
}