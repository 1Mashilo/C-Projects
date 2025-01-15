#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "btree.h"

void print_table(Database *db, const char *table_name) {
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].metadata.name, table_name) == 0) {
            Table *table = &db->tables[i];
            printf("Table '%s':\n", table_name);
            printf("ID\tName\n");
            for (size_t j = 0; j < table->row_count; j++) {
                printf("%d\t%s\n", table->rows[j].id, table->rows[j].name);
            }
            return;
        }
    }
    printf("Table '%s' not found.\n", table_name);
}

int main() {
    Database *db = create_database();

    ColumnMetadata columns[] = {
        {"ID", "int"},
        {"Name", "char"},
        {"Age", "int"}
    };

    Table *users_table = create_table(db, "Users", 3, columns);
    if (!users_table) {
        fprintf(stderr, "Failed to create table 'Users'\n");
        free_database(db);
        return 1;
    }

    insert_row(users_table, 1, "Alice");
    insert_row(users_table, 2, "Bob");
    insert_row(users_table, 3, "Charlie");

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

    // Free the table and database
    free_table(users_table);
    free_database(db);

    return 0;
}
