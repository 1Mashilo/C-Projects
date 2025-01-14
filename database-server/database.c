// File: database.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "btree.h"

// Create a new database
Database* create_database() {
    Database* db = (Database*)malloc(sizeof(Database));
    db->root = NULL;
    db->table_count = 0;
    db->table_names = NULL;
    return db;
}

// Insert a new entry into the database
void insert_entry(Database* db, int id, const char* name, const char* value) {
    DataEntry* entry = (DataEntry*)malloc(sizeof(DataEntry));
    entry->id = id;
    strncpy(entry->name, name, sizeof(entry->name));
    strncpy(entry->value, value, sizeof(entry->value));

    db->root = insertNode(db->root, id);
    printf("Inserted: ID = %d, Name = %s, Value = %s\n", id, name, value);
}

// Delete an entry from the database
void delete_entry(Database* db, int id) {
    db->root = deleteNode(db->root, id);
    printf("Deleted entry with ID = %d\n", id);
}

// Search for an entry in the database
DataEntry* search_entry(Database* db, int id) {
    struct Node* result = searchNode(db->root, id);
    if (result) {
        printf("Found entry with ID = %d\n", id);
        // Placeholder for returning a DataEntry. Would require integration with actual data storage.
        return NULL;
    }
    printf("Entry with ID = %d not found\n", id);
    return NULL;
}

// Free the database
void free_database(Database* db) {
    freeTree(db->root);
    free(db->table_names);
    free(db);
    printf("Database freed\n");
}

// Display metadata about the database
void display_metadata(Database* db) {
    printf("Table count: %d\n", db->table_count);
    for (int i = 0; i < db->table_count; ++i) {
        printf("Table %d: %s\n", i + 1, db->table_names[i]);
    }
}