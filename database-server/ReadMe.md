# Database Server Project

## Overview

This project is a simple database server implemented in C. It uses a binary tree for efficient data storage and retrieval. The server supports basic CRUD operations and ensures data integrity through transaction management.

## Features

- **Data Structures:**
  - **Tables:** Represent data using arrays or linked lists to store rows and columns.
  - **Indexes:** Use data structures like B-trees to quickly locate specific records.
  - **Metadata:** Store information about tables, columns, data types, and constraints.

- **File Storage:**
  - **File System Interaction:** Use standard C functions like `fopen`, `fwrite`, `fread` to read and write data to files.
  - **Data Serialization:** Implement a method to convert data structures into a format that can be stored in files (e.g., JSON, custom binary format).

- **Query Parsing:**
  - **Lexical Analysis:** Break down the query into tokens (SELECT, FROM, WHERE, etc.)
  - **Syntax Analysis:** Check if the token sequence follows the query language grammar.
  - **Semantic Analysis:** Validate the meaning of the query (table existence, column types).

- **CRUD Operations:**
  - **Create (INSERT):** Add new rows to a table.
  - **Read (SELECT):** Retrieve data based on query conditions.
  - **Update (UPDATE):** Modify existing data in a table.
  - **Delete (DELETE):** Remove rows from a table.

- **Important Considerations:**
  - **Concurrency:** Implement mechanisms to handle multiple concurrent requests to the database (e.g., using threads or mutexes).
  - **Transaction Management:** Ensure data integrity by supporting ACID properties (Atomicity, Consistency, Isolation, Durability) with transactions.
  - **Performance Optimization:** Pay attention to data access patterns, indexing strategies, and efficient file I/O to optimize query performance.

- **Alternatives to Building from Scratch:**
  - **Database Libraries:**
    - **SQLite:** A lightweight embedded database that can be integrated directly into your C application.
    - **ODBC (Open Database Connectivity):** A standard API for accessing various databases from C applications.

## Building the Project

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/database-server.git
   cd database-server