*This project has been created as part of the 42 curriculum by aleriaza, dprudnik.*
>
# Description:

Minishell is a 42 School project where the goal is to build a small, functional UNIX-like shell in C. It recreates the core behavior of a command interpreter: displaying a prompt, reading and parsing user input, and executing programs by resolving them through the environment `PATH`. The project focuses on handling pipelines and I/O redirections, running both built-in commands and external executables, and properly managing processes, signals, and exit statuses.

## Instructions:

- Compilation Instructions

	`make ` or `make all` To compile entire program.

	`make re ` Recompile whole project.

	`make fclean ` Remove all obj files (obj directory) and executable.

	`make clean ` Remove only all obj files (and obj directory).


- Shell Execution Instructions

	Run `./minishell ` in the directory where it was compiled to start/execute Minishell.

> [!NOTE]
> If **Not** Compiled see above instructions to compile first.

- Minishell Use Instructions

	`minishell> <command> <options> <argument> ` 

	`minishell> exit` (or Ctrl-d) to Exit and close shell.



 ## Resources:

 AI Usage:
- Chatgpt was used in the research phase of the project to help understand certain requirements and aspects like forking or piping.
- Claude code was used to generate code for a many parts of the project and to generate tests.
- Ai was also used in debugging certain bugs.

 Learning Resources:

- [gnu.org/software/bash/manual](https://www.gnu.org/software/bash/manual/html_node/)

- [Youtube "Shell Program Explained"](https://www.youtube.com/watch?v=ubt-UjcQUYg)

- [Youtube Playlist "Unix Processes in C"](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)


 Additional (e.g., usage examples, feature list, technical choices, etc.).
