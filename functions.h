//
// Created by devpin on 4/23/2017.
//

#ifndef HW9_FUNCTIONS_H
#define HW9_FUNCTIONS_H

#include "Database.h"
#include "EntryValidate.h"
#include <fstream>

void readDB(Database &db);
void closeDB( Database& db );
void search( Database& db, Table* t = nullptr );
void newEntry( Database& db );
void update( Database& db, Entry* entry = nullptr );
void editAffiliate( Entry* );
void deleteEntry( Database&, Entry* = nullptr );
void printEntryOptions( bool back_options = true );
void clearBuffer( istream& in );
void getQueryCondition(QueryObject &, bool mode_toggle = false);
void printReport( Table* );

#endif //HW9_FUNCTIONS_H
