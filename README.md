*This project has been created as part of the 42 curriculum by kaaltint.*

# get_next_line

## Description

**get_next_line** is a C programming project developed as part of the 42 Common Core curriculum.

The goal is to implement a function that reads a file descriptor and returns its content one line at a time.

Through this project, I learned about:

- File descriptors and the `read()` function
- Dynamic memory allocation using `malloc()` and `free()`
- Static variables and persistent data
- String manipulation
- Buffer management and memory safety

**Function prototype:**

```c
char *get_next_line(int fd);
```

Each call returns the next available line, including the newline character (`\n`) when present. The function returns `NULL` when there is nothing left to read or an error occurs.

## Algorithm and Design Choices

I chose a simple approach based on four main operations:

**Read → Append → Extract → Preserve**

### 1. Read

The function reads data from a file descriptor using `read()`.

A temporary buffer of `BUFFER_SIZE + 1` bytes is allocated to store the characters.

Reading continues until a newline character is found or the end of the file is reached.

### 2. Append

Each chunk of data is appended to a string called `stash`.

The `stash` stores all characters read so far that have not yet been returned.

### 3. Extract

When a newline is found, the first complete line is extracted into a newly allocated string.

This line is returned to the caller.

### 4. Preserve

Any characters remaining after the extracted line are kept in `stash` for the next function call.

A `static` variable allows the function to preserve this data between calls.

### Why This Algorithm?

I chose this algorithm because it is simple, understandable, and easy to maintain.

Each helper function performs one specific task, making the code easier to debug and explain.

The algorithm also supports different buffer sizes and lines longer than `BUFFER_SIZE`.

One limitation is that repeatedly joining strings requires additional memory allocations and copying. This approach favors simplicity over maximum performance.

The mandatory implementation uses a single static stash. Handling multiple file descriptors independently is reserved for the bonus part.

## Project Structure

```text
get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
└── README.md
```

### Main Functions

| Function | Description |
|---|---|
| `get_next_line` | Main function that coordinates line reading |
| `read_to_stash` | Reads data until a newline or EOF |
| `append_chunk` | Appends new data to the stash |
| `gnl_strlen` | Calculates the length of a string |
| `gnl_join` | Joins two strings |
| `gnl_has_newline` | Checks for a newline character |
| `gnl_extract_line` | Extracts the next line |
| `gnl_clean_stash` | Preserves the remaining characters |

## Instructions

### Compilation

Compile the project with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c test_main.c -o test_gnl
```

`test_main.c` is a separate test file and is not included in the mandatory submission.

### Execution

```bash
./test_gnl
```

### Buffer Size

The buffer size can be changed at compilation.

For example:

```bash
-D BUFFER_SIZE=1
-D BUFFER_SIZE=42
-D BUFFER_SIZE=9999
```

The function should work correctly regardless of the valid buffer size.

### Testing

Recommended tests include:

- Empty files
- Single-line and multi-line files
- Files without a final newline
- Lines longer than `BUFFER_SIZE`
- Invalid file descriptors
- Standard input
- Different buffer sizes
- Memory leaks

Norminette can be checked using:

```bash
norminette get_next_line.c get_next_line_utils.c get_next_line.h
```

## Resources

The following resources were used to understand the concepts involved in this project:

- [Linux read() manual](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux malloc() manual](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [C static storage duration](https://en.cppreference.com/w/c/language/storage_duration.html)
- 42 get_next_line subject — Version 14.3
- 42 Norm — Version 4.1

### AI Usage

ChatGPT was used as a learning assistant during the development of this project.

It helped me understand file reading, static variables, buffer management, memory allocation, and string manipulation.

AI was also used to discuss the algorithm, draft helper functions, explain the implementation step by step, and prepare this README.

The implementation must be reviewed, tested, and understood before submission.

## Status

The mandatory implementation has been written.

Final compilation, Norminette, memory safety, and edge-case testing are required before evaluation.

## Author

**kaaltint**

42 Istanbul — Common Core
