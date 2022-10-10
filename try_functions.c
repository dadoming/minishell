#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

/**
 *  readline(char* prompt)                  ->  will read from the terminal and return it. Keybindings work like emacs.
 *                                              It will cause bytes to be allocated and when using Valgrind it will appear
 *                                              as "Still reachable", that is not a memory leak! A memory leak is bytes lost 
 *                                              that are not reachable. - https://stackoverflow.com/questions/55196451/gnu-readline-enormous-memory-leak
 * 
 *  add_history(char *buffer)               ->  adds buffer to history 
 *  
 *  rl_clear_history(void)                  ->  clears history.
 * 
 *  rl_on_new_line(void)                    ->  "Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline."
 *                                              Maybe to use when terminal executes some command?
 *  
 *  rl_redisplay(void)                      ->  "Change what's displayed on the screen to reflect the current contents of rl_line_buffer."
 *  
 *  rl_replace_line()                       -> Não encontrei nada na net.
 *  
 *  getcwd(char* buffer, sizeof(buffer))    -> initialize a buffer with size [256] cause most likely it will never surpass that
 * 
 *  chdir(const char* path)                 -> Changes directory to path specified 
 * 
 *  isatty(int fd)                          -> tests if fd is reffering to a terminal. 1 if yes, otherwise 0 and errno is set to indicate error
 * 
 *  ttyname(int fd)                         -> returns a pointer to the pathname string of the terminal device that is open on the fd 
 * 
 *  ttyslot()                               -> returns the fd of the current terminal, >>> check man for more data <<< !!!!!!
 * 
 *  getenv(const char* name)                -> returns the value of the passed name variable in envp
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
 *  kill
 *  exit 
 *  unlink
 *  execve
 *  dup
 *  dup2
 *  pipe
 *  strerror
 *  perror
 *   
 * 
 *  estudar ioctl requests
 *  ioctl -> stands for input output control?
 * 
 * 
 *  estudar directories functions
 *  opendir
 *  readdir
 *  closedir
 * 
 *  
 *  estudar terminal attributes and control functions 
 *  tcsetattr
 *  tcgetattr
 *  tgetent
 *  tgetflag
 *  tgetnum
 *  tgetstr
 *  tgoto
 *  tputs
 *                                  
 *  
 *  estudar stat functions
 *  stat
 *  lstat 
 *  fstat
 *  
 * 
 * 
 *  estudar signals
 *  signal
 *  sigemptyset
 *  sigaction
 *  sigaddset
 *  
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
    char cwd[256];
    
    printf("\nCurrent Working Directory:    %s\n", getcwd(cwd, sizeof(cwd)));

    printf("Terminal File Descriptor :    %s\n\n", ttyname(ttyslot()));
    while (1)
    {
        // Reads line from prompt
        rl_line_buffer = readline("test: ");
        
        // Changes directory of current calling process to previous directory
        if (strcmp(rl_line_buffer, "..") == 0)
        {
            if (chdir("..") == 0)
            {
                printf("%s\n", getcwd(cwd, sizeof(cwd)));
            }    
        }
        
        // If something was written, add it to the history
        if(strlen(rl_line_buffer) > 0)
            add_history(rl_line_buffer);
        
        // If exit was written, then exit loop
        if(strcmp(rl_line_buffer, "exit") == 0)
            break;
        free(rl_line_buffer);
    }
    rl_clear_history();
    free(rl_line_buffer);
    return (0);
}
