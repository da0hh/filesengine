# Search Engine Project (C++)

A modern, high-performance C++ search engine designed to index text documents and perform search queries with relevance-based ranking.

## 📝 Project Description
This project is a console application that implements the core logic of a search system. It:
1. Reads engine settings and document paths from a `config.json` file.
2. Indexes text files using multi-threading to build a comprehensive Inverted Index.
3. Processes search queries from a `requests.json` file.
4. Calculates the relative relevance (Rank) for each document based on term frequency.
5. Generates and saves sorted search results into an `answers.json` file.

## 🛠 Technology Stack
*   **Language:** C++ (C++20/23 standard).
*   **Build System:** CMake (version 3.20 or higher).
*   **Multi-threading:** C++ Standard Thread Library (`std::thread`, `std::mutex`, `std::lock_guard`).
*   **Data Handling:** `nlohmann/json` library (for JSON parsing and generation).
*   **Testing:** Google Test (used for verifying indexing and search accuracy).

## 🚀 Local Setup & Launch

### 1. Prerequisites
*   A C++ compiler (GCC 11+, Clang 13+, or MSVC 2022+).
*   CMake installed.
*   The `nlohmann/json` library (the `json.hpp` header should be located in the `include/` directory).

### 2. File Preparation
Ensure that a `jsonFiles/` directory exists in the project root containing the following files:

*   **config.json**: Engine configuration, versioning, and the list of document paths.
*   **requests.json**: A list of search queries.

### 3. Build and Run
Execute the following commands in your terminal from the project's root directory:

```bash
# Create a build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the project
cmake --build .

# Run the application
./SearchEngine
