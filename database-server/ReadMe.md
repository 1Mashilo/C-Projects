# Database Server

This project implements a simple database server in C, featuring a B-tree index for efficient query performance and persistent storage.

## Key Features

- **Persistent Storage:**
  - Store data permanently using:
    - File storage: Serialize the B-tree data structure to a file (JSON, binary, or CSV).
    - Database file format: Use a format like SQLite with raw file handling.
  - Add functions to load the database from storage when the server starts and save it when the server shuts down.

- **Server/Client Communication:**
  - Use sockets to allow clients to communicate with the database server over a network.
  - Accept commands over TCP (e.g., through `nc` or custom client tools).

- **Query Language:**
  - Implement a simple query language to interact with the database.

- **Memory Management:**
  - Ensure proper memory allocation and deallocation to avoid memory leaks.
  - Use Valgrind to detect and fix memory leaks.

## Alternatives to Building from Scratch

- **Database Libraries:**
  - **SQLite:** A lightweight embedded database that can be integrated directly into your C application.
  - **ODBC (Open Database Connectivity):** A standard API for accessing various databases from C applications.

## Memory Management

To ensure proper memory management, the following functions have been implemented:

- **`createNode`**: Allocates memory for a new B-tree node.
- **`insert`**: Inserts a key into the B-tree and ensures memory is properly allocated.
- **`deleteNode`**: Deletes a key from the B-tree and frees the associated memory.
- **`freeTree`**: Frees the entire B-tree.
- **`free_database`**: Frees the database, including all tables and the B-tree index.

### Using Valgrind

Valgrind is used to detect memory leaks and ensure proper memory management. To run Valgrind, use the following command:

```sh
valgrind --leak-check=full ./database_server
