# README.md

# C++ Database Project

This project is a C++ implementation of a database system, designed to manage data storage and retrieval efficiently. It includes core functionalities for handling database operations, table management, and SQL query parsing.

## Project Structure

```
cpp-database
├── src
│   ├── core
│   ├── storage
│   ├── parser
│   └── main.cpp
├── include
│   └── database
├── tests
├── CMakeLists.txt
└── README.md
```

## Features

- **Database Management**: Connect to and disconnect from the database, execute queries.
- **Table Operations**: Create tables, insert data, and retrieve rows.
- **SQL Parsing**: Parse and execute SQL commands.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- CMake

### Building the Project

1. Clone the repository:
   ```
   git clone <repository-url>
   ```
2. Navigate to the project directory:
   ```
   cd cpp-database
   ```
3. Create a build directory and navigate into it:
   ```
   mkdir build && cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   make
   ```

### Running the Application

After building, you can run the application using:
```
./cpp-database
```

## Running Tests

To run the unit tests, navigate to the `tests` directory and execute:
```
./core_tests
./parser_tests
```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for details.