#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

/**
 *  readline(char* prompt)      ->  will read from the terminal and return it. Keybindings work like emacs.
 *                                  It will cause bytes to be allocated and when using Valgrind it will appear
 *                                  as "Still reachable", that is not a memory leak! A memory leak is bytes lost 
 *                                  that are not reachable. - https://stackoverflow.com/questions/55196451/gnu-readline-enormous-memory-leak
 * 
 *  add_history(char *buffer)   ->  adds buffer to history 
 *  
 *  rl_clear_history(void)      ->  clears history.
 * 
 *  rl_on_new_line(void)        ->  "Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline."
 *                                  Maybe to use when terminal executes some command?
 *  
 *  rl_redisplay(void)          ->  "Change what's displayed on the screen to reflect the current contents of rl_line_buffer."
 *  
 *  rl_replace_line() -> Não encontrei nada na net.
 *  
 *  printf
 *  malloc
 *  free
 *  write
 *  open
 *  read
 *  close
 *  fork
 *  wait
 *  waitpid
 *  
 *  wait3
 *  wait4
 *  
 *  access(file, macro)         -> returns 0 if permitted and -1 if not.  
 *             Macro: int R_OK
 *               Flag meaning test for read permission.
 *
 *             Macro: int W_OK
 *               Flag meaning test for write permission.
 *
 *             Macro: int X_OK
 *               Flag meaning test for execute/search permission.
 *
 *             Macro: int F_OK
 *               Flag meaning test for existence of the file.
 * 
 *  
 *  
 * 
 * 
 */

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    char *rl_line_buffer = NULL;
    while (1)
    {
        rl_line_buffer = readline("test: ");
        rl_redisplay();
        rl_on_new_line();
        if(strlen(rl_line_buffer) > 0)
            add_history(rl_line_buffer);
        if(strcmp(rl_line_buffer, "exit") == 0)
            break;
        free(rl_line_buffer);
    }
    
    rl_clear_history();
    free(rl_line_buffer);
    return (0);
}
