//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//
//                                            Table.h
//                                    Devin Piner - 107543409
//                                         April 1, 2017
//
//                                Interface for the Table class
//                  Hold data in a list so that it can be accessed with subscripts
//
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

#include "Table.h"

Table::Table( const vector<string>& table_keys ) {
    keys = table_keys;
}

Table::~Table( void ) {
    if ( size > 0 ) {
        for (auto i = data.size(); i > 0; --i) {
            Entry *entry = data.back();
            data.pop_back();
            --size;
            delete entry;
        }
    }
}

bool Table::insert( Entry* entry ) { //function to insert and entry into the table
    data.push_back( entry );
    ++size;

    return false;
}

bool Table::isEmpty( void ) {
    return !( bool(size) );
}

void Table::setKeys( vector<string>& k ) {
    keys = k;
}

Entry* Table::operator[]( int i ) {
    return data[i];
}

Table* Table::filter( QueryObject& query ) {
    //make a new table with the same keys
    Table* table = new Table( query.getColumns() );

    string key = query.getCondition().key;
    string operation = query.getCondition().operation;
    string value = query.getCondition().value;

    for ( int i = 0; i < this->size; ++i ) {
        if ( operation == QueryObject::EQUALS ) {
            if ( data[i]->operator[]( key ) == value ) {
                table->insert( data[i] );
            }
        } else {
            if ( data[i]->operator[]( key ).find( value ) != std::string::npos ) {
                table->insert( data[i] );
            }
        }
    }

    return table;
}

ostream& operator<<( ostream& out, Table& table ) {
    int table_width = 5; //holds the total width of the table
    int affiliates_pos = 5; //holds the width of the table to the left of the affiliates
    vector< vector<string> > affiliates; //vector of string vectors to hold the serialized affiliates

    out << table.size << " results" << endl;

    out << std::left;
    out << std::setw(5) << "#";

    //loop through the table and print out the column names, with appropriate spacing
    for ( int i = 0; i < table.keys.size(); ++i ) {
        if ( table.keys[i] == Entry::COMPANY_NAME|| table.keys[i] == Entry::EMAIL ) {
            //for company name and email, setw to 50
            out << std::setw( 50 );
            table_width += 50;
        } else if ( table.keys[i] == Entry::AFFILIATES ) {
            //for affiliates, setw to 75
            //when we get into this else if, we know the amount of space to the left of
            //the affiliates column. we can use this later to print out the affiliates nicely
            out << std::setw( 75 );
            affiliates_pos = table_width;
            table_width += 75;
        } else {
            //for every other column, setw to 25
            out << std::setw( 25 );
            table_width += 25;
        }

        //print of the column name
        out << table.keys[i];
    }

    out << endl;

    //print out a line to separate the column names
    for( int i = 0; i < table_width; ++i ) {
        out << "-";
    }

    out << endl;

    //if the table is not empty
    if ( table.size > 0 ) {

        //step through the table
        for (int i = 0; i < table.size; ++i) {
            //serialize the current entries affiliates
            affiliates.clear();
            table[i]->serializeAffiliates( affiliates );

            out << std::setw(5) << i + 1;

            //first, set up the correct spacing for the current column
            for (int j = 0; j < table.keys.size(); ++j) {
                if ( table.keys[j] == Entry::COMPANY_NAME || table.keys[j] == Entry::EMAIL  ) {
                    out << std::setw( 50 );
                } else if ( table.keys[j] == Entry::AFFILIATES ) {
                    out << std::left;
                    out << std::setw( 75 );
                } else {
                    out << std::setw( 25 );
                }

                //now print out the value
                //if the key is affiliates, print out only the first affiliate, if there is one
                if ( table.keys[j] == Entry::AFFILIATES && affiliates.size() > 0 ) {
                    out << affiliates[0][0] + ", " + affiliates[0][1] + ", " + affiliates[0][2];
                } else {
                    out << table.data[i]->operator[](table.keys[j]);
                }

            }

            //go to the net line
            out << endl;

            //now, if there are more affilaites, print them out
            if ( affiliates.size() > 1 ) {
                string spacer; //spacer between the left of the screen and the affiliates column

                //create a string with the width of the table up to the affiliates table
                for ( int spaces = 0; spaces < affiliates_pos; ++spaces ) {
                    spacer += " ";
                }

                //now, go through each affiliates, print of the spacer, then the affiliate data
                //only print a comma for the first two affiliates fields
                for ( int ii = 1; ii < affiliates.size(); ++ ii ) {
                    out << spacer;
                    for ( int jj = 0; jj < affiliates[ii].size(); ++jj ) {
                        out << affiliates[ii][jj];
                        if ( jj < 2 ) {
                            out << ", ";
                        }
                    }
                    out << endl;
                }
            }
        }
    }

    //otherwise, it's empty
    else if ( table.size == 0 ) {
        out << "No Entries Found" << endl;
    }

    return out;
}
