This was a group project and it was done with Ricardo Garcia

## Minishell

Minishell is a minimal Unix shell implemented in C, designed to replicate core shell functionalities and provide a hands-on understanding of shell. 
It supports command parsing, execution, pipelines, redirections, environment variable management, and several built-in commands.

We divided the project into 2 big parts parsing/execution and Builtin-ins.
I choose to do the parsing/execution and to achive that i divided what i needed to do into smaller problems to be easier to manage.

Syntax Check

    It detects unclosed quotes, misplaced pipes/redirections, usage of unsuppported operators (&& and ||);
    Reports error message and avoid running on unecessary inputs.

Tokenization 

    It keeps track of quotes to avoid splitting words;
    It splits input into tokens: words, pipes, redirections;
    Returns all possible tokens at the end and skips spaces.

Binary Tree (AST) Building

    Recursive Descent Parsing :
      Pipes: parse_pipe recursively splits the token stream at pipe tokens, creating a binary tree where each pipe is a node.
      Redirections: parse_redirect handles redirection tokens (<, >, >>, <<), building subtrees for each redirection.
      Commands: parse_command collects consecutive WORD tokens as command arguments and creates command nodes.

Node Types: 

      Each node (t_tree) has a type (PIPE, REDIRECT_L, REDIRECT_R, APPEND, HEREDOC, WORD, etc.).
      Arguments: Command nodes store argument arrays, in position 0 is the cmd.
      Redirection Info: Redirection nodes store file info and heredoc filenames.

BINARY TREE EXAMPLE

Input line: cat file.txt | grep hello > out.txt

          PIPE
          "|"
         /    \
     CMD       REDIR_OUT
    "cat"         ">"
     ARG         /   \
   file.txt    CMD   FILENAME
             "grep"  "out.txt"
              ARG
            "hello"


Executing the tree:
   

1 Heredoc Execution

    It detects how many heredocs are there in the input line;
    Detects the EOF,
    Creates a temporary file,
    All heredocs are handled  in a child process,
    Expandes variables inside heredoc if EOF not quoted.

        
2 Expansions

    Checks the tree for nodes that need expanding.
    Replaces with necessary info from variables.
    It handles for exemple : "$VAR", "$?", "$0";

3 Pipe Handling

      Set up pipes between commands when a PIPE node is encountered.
      Uses fork(), pipe(), and dup2() to connect child processes;

4 Redirection Handling

      Apply input/output redirections as specified by REDIRECT nodes.
      It performs the command linked to the redirect token te correct stdin/stdout;

5 Built-in Command Execution

      Detect and execute built-in commands directly in the shell process.
  
6 External Command Execution

      Fork child processes and use execve to run external cmds.

7 Process Synchronization

      Wait for all child processes to finish and collect their exit statuses.

After finishing this part me and ricardo worked together on setting :

Signal Handling

    SIGINT (Ctrl+C)
    SIGQUIT (Ctrl+):
    Safe Handling during heredoc, builtins, execution phases.

Exit Code

    Set the correct exit code;
    By expanding $? exit codes can be checked;

 
 Build & Run

make
./minishell
