#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "btree.h"

void print_table(Database *db, const char *table_name) {
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i]->metadata.name, table_name) == 0) {
            display_table(db->tables[i]);
            return;
        }
    }
    printf("Table '%s' not found.\n", table_name);
}

int main() {
    Database *db = create_database();
    if (!db) {
        fprintf(stderr, "Failed to create database\n");
        return 1;
    }

    ColumnMetadata columns[3] = {
        {"ID", "int"},
        {"Name", "char[50]"},
        {"Age", "int"}
    };

    Table *users_table = create_table(db, "Users", 3, columns);
    if (!users_table) {
        fprintf(stderr, "Failed to create table 'Users'\n");
        free_database(db);
        return 1;
    }

    insert_row(users_table, 1, "Alice", 25);
    insert_row(users_table, 2, "Bob", 30);
    insert_row(users_table, 3, "Charlie", 35);

    print_table(db, "Users");

    Row *found = search_row(users_table, 2);
    if (found) {
        printf("\nFound row with ID 2:\n");
        printf("ID: %d\n", found->id);
        printf("Name: %s\n", found->name);
    }

    delete_row(users_table, 2);

    printf("\nAfter deleting row with ID 2:\n");
    print_table(db, "Users");

    free_database(db); // Free the database at the end

    return 0; // Add return statement
}