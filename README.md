# C Dictionary

![C](https://img.shields.io/badge/C-Programming-blue)

A simple dictionary implemented in C that stores key-value pairs and allows basic operations such as adding, updating, and deleting entries. This project demonstrates the use of structures, memory management, and basic error handling.

## Features

- **Add Key-Value Pairs**: Add new entries to the dictionary.
- **Update Existing Entries**: Modify values associated with a specific key.
- **Delete Entries**: Remove entries by setting them as invalid.
- **Error Handling**: Handles various error cases like null pointers, buffer overflows, and invalid keys.

## Technology Stack

- **C**: Used as the primary programming language for the project.
- **CLion**: IDE used for development.

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/username/C_Dictionary.git
   ```
   
2. Navigate to the project directory:
   ```bash
   cd C_Dictionary
   ```
   
3. Compile the program:
   ```bash
   gcc -o dictionary dictionar.c
   ```

4. Run the program:
   ```bash
   ./dictionary
   ```
   
### Example Usage

1. **Adding Entries**:
   ```c
   TDictionary dict;
   TDictionary_clearAll(&dict);
   TDictionary_writeValue(&dict, "key1", "value1");
   ```

2. **Updating Entries**:
   ```c
   TDictionary_writeValue(&dict, "key1", "new_value");
   ```

3. **Deleting Entries**:
   ```c
   TDictionary_writeValue(&dict, "key1", NULL); // Passing NULL as value to delete entry
   ```

4. **Reading Entries**:
   ```c
   char buffer[DICTIONARY_ITEM_VALUE_BUFFER_SIZE];
   TDictionary_readValue(&dict, "key1", buffer, sizeof(buffer));
   printf("Value: %s\n", buffer);
   ```
   
## Error Handling

This project includes basic error handling for various cases:

- **Invalid Keys**: Checks for null or empty keys.
- **Buffer Overflow**: Ensures values do not exceed defined buffer sizes.
- **Null Pointers**: Handles cases where pointers may be null.

## Future Improvements

Some potential improvements for this project include:

- **Dynamic Resizing**: Allow the dictionary to expand dynamically when capacity is reached.
- **Persistent Storage**: Implement functionality to save and load dictionary entries to and from a file.
- **Enhanced Error Messages**: Provide more detailed error messages for debugging.
