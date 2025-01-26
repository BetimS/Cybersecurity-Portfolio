# Bsh Project

A custom shell implementation in C built on a UMB Unix server and tested on Linux. This project demonstrates my understanding of environment variables, process management, and system calls.

## Key Features

1.Environment Variable Management

-```env```: Displays the current environment variables.

-```setenv```: Sets a new environment variable or updates an existing one.

-```unsetenv```: Removes an environment variable.

2.Directory Navigation

-```cd```: Changes the current working directory. Handles edge cases like navigating to ~ (home directory) or no argument (default to home).

3.Command History

-Tracks previously entered commands and prints them on request.

4.Executing Linux Commands

-Supports executing built-in Linux commands by identifying paths in the ```PATH``` environment variable and using ```access()```.

## Implementation Details

-```env```:

--Stored strings into an array instead of printing directly.

-```setenv```:

-- Added logic to create new variables or overwrite existing ones by parsing strings using "=" as a delimiter.

-```unsetenv```:

-- Removed variables by reusing search logic from setenv and reassigning pointers to maintain array structure.

-```cd```:

-- Implemented logic to handle null, ~, or specific directory arguments using ```chdir()``` and ```getcwd()``` system calls.

-```history```:

-- Maintained a dynamic array to store commands and printed them with a loop.

-Linux Commands:

-- Used ```access()``` to check executability of commands in directories listed in ```PATH``` and forked processes for execution to prevent blocking the shell.

## How to Run
1. Clone the repository:
```
  git clone https://github.com/BetimS/Cybersecurity-Portfolio/tree/main/Bsh%20Project/Project%20Files
```
2. Navigate to the project directory:
```
cd bsh-terminal
```
3. Compile the program:
```
gcc bsh.c -o bsh
```
4. Run the shell
```
./bsh
```
## Example Commands

```
bsh> env
bsh> setenv MY_VAR my_value
bsh> unsetenv MY_VAR
bsh> cd ~/Documents
bsh> history
bsh> ls -la
```

## Technologies Used

-Language: C

-Environment: Linux, UMB Unix Server

-Concepts: Environment variables, dynamic memory allocation, process forking, and system calls.

## Learning Outcomes

-Deepened my understanding of shell internals and process management.

-Improved skills in C programming and debugging on Linux systems.

-Gained hands-on experience with system calls like chdir, getcwd, fork, and access.
