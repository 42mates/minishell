# Minishell

This is the repository for 42's Minishell project made by [@ku-alexej](https://github.com/ku-alexej) and [@marinsucks](https://github.com/marinsucks).

## Description

Minishell is a simplified version of a shell, implementing some of the basic functionalities of the Bash POSIX shell. It supports executing commands, handling environment variables, basic and managing processes.

## Features

Minishell supports the following features:
- [Command Execution](#command-execution)
- [Signal Handling](#signal-handling)
- [Environment Variables](#environment-variables)
- [Quoting](#quoting)
- [Redirections and Pipes](#redirections-and-pipes)
- [Builtins](#builtins)


#### Command Execution: 
Commands can be executed with or without arguments from absolute and relative paths as well as directories included in the `PATH` environment variable.

#### Signal Handling:

- __ctrl-C__ sends a SIGINT signal to interrupt the running process.   
- __ctrl-D__ sends and End Of File (EOF) signal.  
- __ctrl-\\__ quits a running process.

#### Environment Variables:
Environment variables can be used in any command as `$` followed by the variable name. They can be manipulated using the [`export`](#builtins) and [`unset`](#builtins) builtins. These variables are inherited from the parent process and sent to the child processes. `$?`, which expands to the exit status of the last executed command, is also supported.

#### Quoting: 
Minishell handles single quotes `'` and double quotes `"` which prevent the shell from interpreting the meta-characters in the quoted sequence, except for environment variables inside double quotes (`echo "$USER"` prints the username, while `echo '$USER'` simply prints $USER).

#### Redirections and Pipes: 
- `<` for input
- `<<[delimiter]` for reading input until a line containing the delimiter is seen
- `>` for output
- `>>` for appending output.
- `|` for the pipe, where the output of the left command is sent to the input of the right command.

#### Builtins
- `echo` prints its arguments followed by a newline. The  `-n` option suppresses the newline at the end.
- `cd` changes the current directory and accpets absolute and relative paths. 
- `pwd` prints the current working directory.
- `export` sets its arguments to environment variables, or prints all environment variables if no argument is provided.
- `unset` removes the specified environment variables.
- `env` prints the environment variables which values aren't NULL.
- `exit` terminates the process with the specified exit code.


## Getting Started

To get started with Minishell, follow these steps:

1. Clone the repository:
	```bash
	git clone https://github.com/42mates/minishell.git; cd minishell
	```

2. Build the project:
	```bash
	make
	```

3. Run Minishell:
	```bash
	./minishell
	```

### Note:
The project uses the `readline` library for line editing. Functions from this library can cause memory leaks when used with `valgrind`. To avoid this, run the program with the following command from the project's root directory:
```bash
valgrind --suppressions=$PWD/readline.supp ./minishell
```
