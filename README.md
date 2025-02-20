# Minishell

Minishell is a fully-featured, bash-inspired lightweight shell implemented in C. It replicates many common shell functionalities while adding its own unique features. Designed as both a robust shell and an educational project, Minishell demonstrates shell internals, systems programming concepts, and advanced features such as environment variable and wildcard expansion, piping, redirection, signal handling, heredoc support, and readline integration.

## Project Overview

Minishell aims to provide a complete shell experience with extended capabilities:
- **Custom Shell Environment:** A fully functional shell with its own parsing, execution, and error handling routines.
- **Advanced Features:** Implements environment variable expansion, wildcard expansion, built-in commands (e.g., `cd`, `exit`, `export`), piping, redirection, and heredoc support.
- **Robust Signal Handling:** Manages system signals to ensure smooth and controlled operation.
- **Readline Integration:** Utilizes GNU Readline for improved command-line editing and history management.
- **Modular Codebase:** Organized into multiple source files (e.g., `minishell.c`, `helpers.c`, `dollar_expansion_1.c`, etc.) to make the implementation easier to understand and maintain.

## Features

- **Environment Variable & Wildcard Expansion:** Dynamic substitution of environment variables and file matching using wildcards.
- **Built-in Commands:** Comprehensive built-in commands including, but not limited to, `cd`, `exit`, and `export`.
- **Piping & Redirection:** Supports complex command chaining with pipes and I/O redirection.
- **Heredoc Support:** Allows multi-line input for commands requiring heredoc functionality.
- **Signal Handling:** Gracefully handles signals to maintain shell stability.
- **Readline Integration:** Enhances user experience with line editing and command history.

## Installation & Usage

### Prerequisites
- **GCC Compiler**
- **GNU Readline Library**  
  *(On macOS, install via Homebrew: `brew install readline`)*


### Cloning and Building
1. **Clone the repository:**
   ```bash
   git clone https://github.com/Poider/Minishell-Bash-inspired-Lightweight-Shell.git
   cd Minishell-Bash-inspired-Lightweight-Shell/MiniShellFiles
   ```

2. **Build the project:**
   ```bash
   make
   ```
   This command compiles all source files and generates the `minishell` executable.

### Running Minishell
Start the shell by executing:
```bash
./minishell
```

## Outcome

When you run Minishell, you will see a prompt like to the following:

```bash
$ ./minishell
minishell> 
```

From here, you can:
- **Execute Commands:** Type standard commands like `ls`, `pwd`, or any built-in command.
- **Use Environment Variables:** For example, `echo $HOME` will display your home directory.
- **Chain Commands with Pipes & Redirection:** Execute commands such as:
  ```bash
  minishell> ls -l | grep ".c" > c_files.txt
  ```
- **Utilize Heredoc:** Input multi-line commands when needed.
- **Navigate Directories:** Change directories with `cd` and manage your shell session interactively.

A typical session looks like this:

```bash
minishell> echo "Welcome to Minishell!"
Welcome to Minishell!
minishell> cd /usr/bin
minishell> ls | grep gcc
gcc-10
gcc-11
minishell> exit
```

Minishell handles parsing, expansion, execution, and error reporting, offering a smooth and intuitive user experience.

## Contribution Guidelines

Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a feature branch.
3. Commit your changes with clear and descriptive messages.
4. Open a pull request detailing your changes and suggestions.

For significant changes, please open an issue first to discuss your proposed modifications.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
