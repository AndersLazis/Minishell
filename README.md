# Minishell

<p align="center">
  <img src="https://github.com/AndersLazis/AndersLazis/blob/main/assets/badges/minishelle.png" alt="Minishell 42 project badge"/>
</p>

Minishell is a 42 school team project to create a basic shell program in C. It implements redirections and pipes, as well as environment variable expansions and the `cd`, `echo`, `env`, `exit`, `export`, `pwd` and `unset` builtin commands.

## Status

Validated 4 Aug 2023. Grade: 100%.

## Usage

You should have readline library preinstalled!
Clone the repository https://github.com/AndersLazis/Minishell.git
```
git clone git@github.com:mcombeau/minishell.git
```

To compile:

```shell
cd minishell && make
```

To run the program:

```shell
./minishell
```

A prompt will appear. You may enter your commands to be executed.

## Supported Features

Minishell is a miniature shell program based on Bash. Minishell supports:
* Prompt display
* Command history (up and down arrows)
* System executables available from the environment (`ls`, `cat`, `grep`, etc.)
* Local executables (`./minishell`)
* Builtin commands :
  * `echo` (and option `-n`)
  * `cd` (with only a relative or absolute path)
  * `pwd` (no options)
  * `export` (no options)
  * `unset` (no options)
  * `env` (no options or arguments)
  * `exit` (with exit number but no other options) 
* Pipes `|` which redirect output from one command to input for the next
* Redirections:
  * `>` redirects output
  * `>>` redirects output in append mode
  * `<` redirects input
  * `<< DELIMITER` displays a new prompt, reads user input until reaching `DELIMITER`, redirects user input to command input (does not update history)
* Environment variables (i.e. `$USER` or `$VAR`) that expand to their values.
  * `$?` expands to the exit status of the most recently executed foreground pipeline.
* User keyboard signals:
  * `ctrl-c` displays a new prompt line.
  * `ctrl-d` exits minishell
  * `ctrl-\` does nothing

However, Minishell does not support `\`, `;`, `&&`, `||`, or wildcards.

---
### Useful Resources for the Minishell Project

* [Bash reference manual](https://www.gnu.org/software/bash/manual/bash.html)
* Introduction to Systems Programming: a Hands-on Approach, [Chapter 5. Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [Stephen Brennan's Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* The Open Group Base Specifications, [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [A Guide to Unix Shell Quoting](https://rg1-teaching.mpi-inf.mpg.de/unixffb-ss98/quoting-guide.html)
* [Austin Tripp's Quick Tutorial on Bash Quotes](https://www.austintripp.ca/blog/2019/07/18/bash-quotes)
