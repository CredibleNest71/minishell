# minishell

A small Unix shell in C, modelled on bash. Team project at 42 Vienna.

## Features

- Interactive prompt with command history (GNU readline)
- Single and double quotes
- Environment variable expansion, including `$?` for the last exit status
- Pipes: `ls -l | grep .c | wc -l`
- Redirections: `<`, `>`, `>>` and here-documents with `<<`
- Built-ins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling like bash: `Ctrl-C` shows a new prompt, `Ctrl-D` exits, `Ctrl-\` does nothing
- Executables found through `PATH`

## Build and run

Requires the readline library (`sudo apt install libreadline-dev` on Debian/Ubuntu).

```sh
make
./minishell
```

```
minitrap: echo "Hello $USER" | tr a-z A-Z > out.txt
minitrap: cat << EOF
> exit status was $?
> EOF
```

`make valgrind` runs the shell under valgrind and hides readline's own leaks (copy `valgrind_ignore_leaks.txt` to your home directory first).

## How it works

1. **Tokenizer**: splits the input line into words and operators, keeping quoted parts together
2. **Syntax check**: rejects input such as `| ls` or `cat <`
3. **Expansion**: replaces `$VAR` and `$?`, then removes the quotes
4. **Execution**: builds a pipeline, sets up the redirections and here-docs, and runs built-ins in the shell process or forks for external commands

## Structure

```
src/
├── main/        prompt loop and signals
├── parser/      tokenizer, syntax check, expansion
├── execution/   pipelines, redirections, here-docs, PATH lookup
└── built-ins/   echo, cd, pwd, export, unset, env, exit
minilib/         own C library (libft subset)
```

## Team

Ildiko Jasmin Schmutzer and Moritz Resch.

My part: the parser (tokenizer, syntax check and variable expansion).
