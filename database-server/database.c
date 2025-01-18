#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "btree.h"

#define DATA_FILE "data.txt"
#define INDEX_FILE "index.txt"

// Create a new database
Database* create_database() {
    Database *db = (Database*)malloc(sizeof(Database));
    db->table_count = 0;
    db->tables = NULL;
    return db;
}

// Create a new table with a specified capacity
Table* create_table(Database *db, const char *table_name, int column_count, ColumnMetadata *columns) {
    Table *table = (Table *)malloc(sizeof(Table));
    if (!table) return NULL;

    table->rows = (Row *)malloc(10 * sizeof(Row)); // Assuming a default capacity of 10
    if (!table->rows) {
        free(table);
        return NULL;
    }

    table->row_count = 0;
    table->capacity = 10;
    table->index = NULL;

    strncpy(table->metadata.name, table_name, sizeof(table->metadata.name) - 1);
    table->metadata.column_count = column_count;
    table->metadata.columns = (ColumnMetadata *)malloc(column_count * sizeof(ColumnMetadata));
    if (!table->metadata.columns) {
        free(table->rows);
        free(table);
        return NULL;
    }
    memcpy(table->metadata.columns, columns, column_count * sizeof(ColumnMetadata));

    db->tables = (Table **)realloc(db->tables, (db->table_count + 1) * sizeof(Table*));
    if (!db->tables) {
        free(table->metadata.columns);
        free(table->rows);
        free(table);
        return NULL;
    }
    db->tables[db->table_count++] = table;

    return table;
}

// Free the table and its resources
void free_table(Table *table) {
    if (table) {
        for (size_t i = 0; i < table->row_count; i++) {
            if (table->rows[i].values) {
                for (int j = 0; j < table->metadata.column_count; j++) {
                    free(table->rows[i].values[j]);
                }
                free(table->rows[i].values);
            }
        }
        free(table->rows);
        free(table->metadata.columns);
        freeTree(table->index); // Free the B-tree index
        free(table); // Free the table LAST
    }
}

// Free the database and its resources
void free_database(Database *db) {
    if (db) {
        for (int i = 0; i < db->table_count; i++) {
            free_table(db->tables[i]); // Free each table
        }
        free(db->tables);
        free(db);
    }
}

// Insert a row into the table
bool insert_row(Table *table, int id, const char *name, int age) {
    if (table->row_count >= table->capacity) {
        return false; // Table is full
    }

    // Insert row
    Row *new_row = &table->rows[table->row_count++];
    new_row->id = id;
    strncpy(new_row->name, name, MAX_NAME_LEN - 1);
    new_row->name[MAX_NAME_LEN - 1] = '\0';

    // Allocate memory for the values array
    new_row->values = (char**)malloc(table->metadata.column_count * sizeof(char*));
    if (!new_row->values) {
        fprintf(stderr, "Failed to allocate memory for row values\n");
        return false;
    }

    // Assign values for columns
    new_row->values[0] = (char*)malloc(20 * sizeof(char)); // Assuming ID will fit in 20 characters
    snprintf(new_row->values[0], 20, "%d", id);
    new_row->values[1] = strdup(name);
    new_row->values[2] = (char*)malloc(20 * sizeof(char)); // Assuming age will fit in 20 characters
    snprintf(new_row->values[2], 20, "%d", age);

    // Update index
    table->index = insertNode(table->index, id);

    return true;
}

// Insert a new row with values into the table
void insert_row_with_values(Table *table, char **values) {
    if (table->row_count >= table->capacity) {
        fprintf(stderr, "Table is full\n");
        return;
    }

    Row *new_row = &table->rows[table->row_count++];
    new_row->id = atoi(values[0]); // Assume the first column is the ID

    // Allocate memory for the values array
    new_row->values = (char**)malloc(table->metadata.column_count * sizeof(char*));
    if (!new_row->values) {
        fprintf(stderr, "Failed to allocate memory for row values\n");
        return;
    }

    // Copy the values
    for (int i = 0; i < table->metadata.column_count; i++) {
        new_row->values[i] = strdup(values[i]);
        if (!new_row->values[i]) {
            fprintf(stderr, "Failed to allocate memory for row value\n");
            for (int j = 0; j < i; j++) {
                free(new_row->values[j]);
            }
            free(new_row->values);
            return;
        }
    }

    // Insert into B-tree index
    table->index = insertNode(table->index, new_row->id);

    printf("Row with ID %d inserted into table '%s'.\n", new_row->id, table->metadata.name);
}

// Search for a row by ID
Row* search_row(Table *table, int id) {
    if (!searchNode(table->index, id)) {
        return NULL;
    }

    for (size_t i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            return &table->rows[i];
        }
    }
    return NULL;
}

// Delete a row by ID
void delete_row(Table *table, int id) {
    size_t i;
    for (i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            break;
        }
    }

    if (i == table->row_count) {
        printf("Row with ID %d not found in table '%s'.\n", id, table->metadata.name);
        return;
    }

    // Free the memory allocated for the row
    if (table->rows[i].values) {
        for (int j = 0; j < table->metadata.column_count; j++) {
            free(table->rows[i].values[j]);
        }
        free(table->rows[i].values);
    }

    // Shift the remaining rows
    for (size_t j = i; j < table->row_count - 1; j++) {
        table->rows[j] = table->rows[j + 1];
    }
    table->row_count--;

    // Remove from B-tree index
    table->index = deleteNode(table->index, id);

    printf("Row with ID %d deleted from table '%s'.\n", id, table->metadata.name);
}

// Update a row by ID
void update_row(Table *table, int id, char **values) {
    Row *row = search_row(table, id);
    if (!row) {
        printf("Row with ID %d not found in table '%s'.\n", id, table->metadata.name);
        return;
    }

    // Free the existing values
    for (int i = 0; i < table->metadata.column_count; i++) {
        free(row->values[i]);
    }
    free(row->values);

    // Allocate memory for the new values array
    row->values = (char**)malloc(table->metadata.column_count * sizeof(char*));
    if (!row->values) {
        fprintf(stderr, "Failed to allocate memory for row values\n");
        return;
    }

    // Copy the new values
    for (int i = 0; i < table->metadata.column_count; i++) {
        row->values[i] = strdup(values[i]);
        if (!row->values[i]) {
            fprintf(stderr, "Failed to allocate memory for row value\n");
            for (int j = 0; j < i; j++) {
                free(row->values[j]);
            }
            free(row->values);
            return;
        }
    }

    printf("Row with ID %d updated in table '%s'.\n", id, table->metadata.name);
}

// Save the table to files
void save_table(Table *table, const char *data_file, const char *index_file) {
    // Save rows to data file
    FILE *data_fp = fopen(data_file, "w");
    if (!data_fp) {
        perror("Failed to open data file for writing");
        return;
    }

    for (size_t i = 0; i < table->row_count; i++) {
        fprintf(data_fp, "%d,%s\n", table->rows[i].id, table->rows[i].name);
    }

    fclose(data_fp);

    // Save index to index file
    FILE *index_fp = fopen(index_file, "w");
    if (!index_fp) {
        perror("Failed to open index file for writing");
        return;
    }

    saveTree(table->index, index_fp);
    fclose(index_fp);
}

// Load the table from files
void load_table(Table *table, const char *data_file, const char *index_file) {
    // Load rows from data file
    FILE *data_fp = fopen(data_file, "r");
    if (!data_fp) {
        perror("Failed to open data file for reading");
        return;
    }

    table->row_count = 0;
    while (!feof(data_fp) && table->row_count < table->capacity) {
        Row *row = &table->rows[table->row_count];
        if (fscanf(data_fp, "%d,%49[^,]\n", &row->id, row->name) == 2) {
            table->row_count++;
        }
    }

    fclose(data_fp);

    // Load index from index file
    FILE *index_fp = fopen(index_file, "r");
    if (!index_fp) {
        perror("Failed to open index file for reading");
        return;
    }

    table->index = loadTree(index_fp);
    fclose(index_fp);
}

// Display all rows in a table
void display_table(Table *table) {
    printf("Table '%s':\n", table->metadata.name);
    for (int i = 0; i < table->metadata.column_count; i++) {
        printf("%s\t", table->metadata.columns[i].name);
    }
    printf("\n");

    for (size_t i = 0; i < table->row_count; i++) {
        for (int j = 0; j < table->metadata.column_count; j++) {
            printf("%s\t", table->rows[i].values[j]);
        }
        printf("\n");
    }
}