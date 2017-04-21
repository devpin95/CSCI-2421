cmake_minimum_required(VERSION 3.7)
project(hw9)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Node.h BSTree.cpp BSTree.h Entry.cpp Entry.h Table.cpp Table.h EntryPrinter.cpp EntryPrinter.h QueryObject.cpp QueryObject.h Database.cpp Database.h HashTable.cpp HashTable.h FileObject.cpp FileObject.h EntryValidator.cpp EntryValidator.h)
add_executable(hw9 ${SOURCE_FILES})