# shell-cpp

A Unix-style command-line shell written from scratch in C++. It reads commands in a loop, parses them with a hand-written tokenizer, runs built-in commands itself, and launches external programs using `fork`, `execvp` and `wait`.

Built as part of the [CodeCrafters "Build Your Own Shell"](https://app.codecrafters.io/courses/shell/overview) challenge.

## Features

- **Interactive prompt (REPL):** shows a `$ ` prompt, reads a line, runs it, and repeats until `exit`.
- **Built-in commands**
  - `echo`: prints its arguments, with full quote handling
  - `pwd`: prints the current working directory
  - `cd`: changes directory; supports `cd` (go to `$HOME`), `cd ~` and `cd ~/path`
  - `type`: tells whether a command is a shell built-in or an executable found in `$PATH`
  - `exit`: quits the shell
- **External programs:** any program found in `$PATH` (such as `ls`, `cat`, `grep`) is run in a child process created with `fork()` and `execvp()`, and the shell waits for it to finish.
- **Custom tokenizer** that handles:
  - single quotes (`'...'`): everything inside is literal
  - double quotes (`"..."`): spaces are kept, and `\"`, `\$`, `\\` are escaped
  - backslash escapes outside quotes (`\ ` for a literal space)
- **Error handling:** reports a missing `$HOME`, failed `cd`/`getcwd` calls, and unknown commands.

## How it works

1. **Read:** `std::getline` reads one line of input.
2. **Tokenize:** `tokenise()` walks the line character by character and tracks whether it is inside single quotes, inside double quotes, or after a backslash, then splits it into arguments.
3. **Dispatch:** if the first word is a built-in, the shell runs it directly.
4. **Otherwise run externally:** the shell calls `fork()`. The child calls `execvp()` to replace itself with the requested program, and the parent calls `wait()` until it finishes.
5. **Prompt again.**

`type` searches the directories listed in `$PATH` and uses `access(path, X_OK)` to check whether a matching executable exists.

## Getting started

### Prerequisites

- A C++ compiler (`g++` or `clang++`)
- [CMake](https://cmake.org/)
- Linux or macOS (uses POSIX calls such as `fork`, `execvp`, `chdir`)

### Build and run

```bash
git clone https://github.com/deepak-sharma01/shell-cpp.git
cd shell-cpp

./your_program.sh
```

`your_program.sh` builds the project with CMake and starts the shell. To build manually:

```bash
cmake -B build -S .
cmake --build build
```

## Usage examples

```text
$ echo "Hello,   World"
Hello,   World
$ echo 'single quotes keep \n literal'
single quotes keep \n literal
$ type echo
echo is a shell builtin
$ type ls
ls is /usr/bin/ls
$ type notacommand
notacommand: not found
$ pwd
/home/user/shell-cpp
$ ls
CMakeLists.txt  README.md  src  ...
$ exit
```

Directory navigation:

```text
cd /tmp      # absolute path
cd ~         # home directory
cd ~/Documents
cd           # also goes to $HOME
```

## Project structure

```text
shell-cpp/
├── src/
│   └── main.cpp          # REPL, built-ins, tokenizer, process creation
├── CMakeLists.txt        # build configuration
├── vcpkg.json            # dependency manifest
├── your_program.sh       # build-and-run helper script
└── README.md
```

## What I learned

- How a shell reads, parses and executes commands
- Process creation and control with `fork`, `execvp` and `wait`
- Working with environment variables (`PATH`, `HOME`) and the file system (`getcwd`, `chdir`, `access`)
- Writing a state-based parser for quotes and escape characters
- Building a C++ project with CMake

## Planned improvements

- Input/output redirection (`>`, `>>`, `2>`)
- Pipes (`|`)
- Command history and tab completion
- Splitting the code into separate files (tokenizer, built-ins, utilities)

## Author

**Deepak Sharma** · [GitHub](https://github.com/deepak-sharma01)
