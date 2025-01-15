#ifndef DATABASE_H
#define DATABASE_H

#include <stddef.h>
#include <stdbool.h>

#define MAX_NAME_LEN 100

typedef struct {
    char name[MAX_NAME_LEN];
    char type[20]; // Example: "int", "char", etc.
} ColumnMetadata;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char **values; // Add this field to store column values
} Row;

typedef struct {
    size_t row_count;
    size_t capacity;
    Row *rows;
    void *index;
    struct {
        char name[50];
        int column_count;
        ColumnMetadata *columns;
    } metadata;
} Table;

typedef struct {
    int table_count;
    Table *tables;
} Database;

// Function prototypes
Database* create_database();
void free_database(Database *db);
Table* create_table(Database *db, const char *table_name, int column_count, ColumnMetadata *columns);
void free_table(Table *table);
bool insert_row(Table *table, int id, const char *name);
void insert_row_with_values(Table *table, char **values);
Row* search_row(Table *table, int id);
void delete_row(Table *table, int id);
void save_table(Table *table, const char *data_file, const char *index_file);
void load_table(Table *table, const char *data_file, const char *index_file);

#endif // DATABASE_H