# ManDB

ManDB is a lightweight, in-memory database designed for educational purposes. It supports basic SQL operations with a fun twist on SQL syntax. This project demonstrates the implementation of a simple database engine, SQL parser, and storage engine.

## Features

- **SQL Parser**: Parses and validates SQL queries with fun aliases.
- **Storage Engine**: Manages data storage with support for write-ahead logging (WAL) and page caching.
- **Database Engine**: Executes SQL queries and manages database connections.

## Fun SQL Syntax

ManDB supports the following fun SQL commands:

- `GIMME` → `SELECT`
- `STUFF IN` → `INSERT INTO`
- `MORPH` → `UPDATE`
- `VANISH` → `DELETE`
- `SUMMON TABLE` → `CREATE TABLE`

## Getting Started

### Prerequisites

- CMake 3.10 or higher
- Visual Studio 2022 or any C++17 compatible compiler

### Building the Project

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/ManDB.git
   cd ManDB/cpp-database
   ```

2. Create a build directory and run CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

3. Run the executable:
   ```sh
   cd Release
   ./cpp-database.exe
   ```

### Running Tests

1. Uncomment the test-related lines in `CMakeLists.txt`:
   ```cmake
   enable_testing()
   add_subdirectory(tests)
   ```

2. Rebuild the project:
   ```sh
   cmake ..
   cmake --build . --config Release
   ```

3. Run the tests:
   ```sh
   ctest -V
   ```

## Project Status

> **This project is ongoing and open to contributions.**  
> Feel free to fork, contribute, and improve ManDB!  

## Contributing

Contributions are welcome! If you would like to contribute:
- Fork the repository
- Open a pull request with your changes
- Follow best practices for C++ development

## License

This project is licensed under the MIT License.

