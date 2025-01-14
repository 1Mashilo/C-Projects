#include <stdio.h>
#include "database.h"

int main() {
    printf("Starting Database Server...\n");

    // Initialize the database
    Database* db = create_database();

    // Add entries
    insert_entry(db, 1, "Alice", "Developer");
    insert_entry(db, 2, "Bob", "Designer");

    // Display metadata
    display_metadata(db);

    // Search for an entry
    search_entry(db, 1);
    search_entry(db, 3);

    // Delete an entry
    delete_entry(db, 2);

    // Free the database
    free_database(db);

    return 0;
}