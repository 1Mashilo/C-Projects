# Database Server

This project implements a simple database server in C, featuring a B-tree index for efficient query performance and persistent storage.

## Key Features

- **Table Management:**
  - Create tables with specified columns.
  - Insert rows into tables.
  - Delete rows from tables.
  - Update rows in tables.
  - Search for rows by ID.
  - Display all rows in a table.

- **B-tree Index:**
  - Efficiently index rows by ID for fast search operations.

## Current Features

1. **Create Database:**
   - Initialize a new database.

2. **Create Table:**
   - Create a new table with specified columns.

3. **Insert Row:**
   - Insert rows into a table with specified values.

4. **Delete Row:**
   - Delete rows from a table by ID.

5. **Update Row:**
   - Update the values of an existing row by ID.

6. **Search Row:**
   - Search for a row by ID.

7. **Display Table:**
   - Display all rows in a table.

## Next Steps

1. **Persistent Storage:**
   - Store data permanently using:
     - File storage: Serialize the B-tree data structure to a file (JSON, binary, or CSV).
     - Database file format: Use a format like SQLite with raw file handling.
   - Add functions to load the database from storage when the server starts and save it when the server shuts down.

2. **Server/Client Communication:**
   - Use sockets to allow clients to communicate with the database server over a network.
   - Accept commands over TCP (e.g., through `nc` or custom client tools).

3. **Query Language:**
   - Implement a simple query language to interact with the database.

4. **Transaction Support:**
   - Add support for transactions to ensure data integrity.

5. **Advanced Indexing:**
   - Improve indexing to support more complex queries and faster search operations.

## How to Run

1. Compile the project:
   ```sh
   gcc -Wall -O2 -std=c2x -g -o database_server main.c btree.c database.c
