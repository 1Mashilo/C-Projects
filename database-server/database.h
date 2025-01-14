// File: database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "btree.h"

// Data entry structure
typedef struct {
    int id;
    char name[100];
    char value[256]; // Can store additional data fields
} DataEntry;

// Database structure
typedef struct Database {
    struct Node* root; // Pointer to the root of the B-Tree for indexing
    int table_count;   // Number of tables
    char **table_names; // List of table names
} Database;

// Function declarations
Database* create_database();
void insert_entry(Database* db, int id, const char* name, const char* value);
void delete_entry(Database* db, int id);
DataEntry* search_entry(Database* db, int id);
void free_database(Database* db);
void display_metadata(Database* db);

#endif // DATABASE_H