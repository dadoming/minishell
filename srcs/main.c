#include "../includes/minishell.h"

// man 2 ioctl_tty

sh_t *mini(void)
{
    static sh_t mini;

    return (&mini);
}

int check_input(int argc, char** argv)
{
    return (argc == 1 && string()->_compare_n(argv[0], "./minishell", 12) == 0);
}

int init(char **envp)
{
    //variable struct init
    if(!envp)
        return (FALSE);
    mini()->var.env_p = envp;
    mini()->var.cwd = getcwd(0, 512);
    mini()->var.logname = getenv("LOGNAME");

    
    //signal init
    mini()->signalset = FALSE;
    return (TRUE);
}

void close_program(void)
{
    //if(mini()->var.cwd)
      //  free(mini()->var.cwd);
    return ;
}

// Returns the inode number of a file descriptor
int get_inode(int fd)
{
    struct stat buf;
    int ret;

    ret = fstat(fd, &buf);
    if (ret < 0)
    {
        perror("fstat");
        return (-1);
    }
    return (buf.st_ino);
}

// Handle ctrl
void ignore_signal_for_shell()
{
	mini()->signalset = TRUE;
	
	// ignore "Ctrl-C" -> alterar para dar display a um novo prompt numa nova linha
    mini()->SIGINT_handler = signal(SIGINT, SIG_IGN);
	
	// ignore "Ctrl-\"
    signal(SIGQUIT, SIG_IGN);

    //ignore "Ctrl-D"
    mini()->SIGINT_handler = signal(SIGINT, SIG_IGN);
    //signal(SIGABRT, SIG_IGN);
}



void split_args(char *buff)
{
    mini()->argcount = string()->_arg_count(buff);
    mini()->argvalue = string()->_split(buff, ' ');
}

void helper_print(int i)
{
    printf("cwd : %s\n", mini()->var.cwd);
    printf("argc: %d\n", mini()->argcount);
    printf("argv: ");
    while (mini()->argvalue[i] != 0)
        printf("%s ", mini()->argvalue[i++]);
    printf("\n");
}

int _is_directory(char *path)
{
    struct stat sb;

    if(stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
        return (1);
    return (0);
}

// Não funciona porque é necessário criar a própria shell com as
// suas próprias variaveis. Não é possível alterar as variáveis dentro do kernel.
void change_d(void)
{
    if(mini()->argcount > 0)
    {
        if(string()->_compare(mini()->argvalue[0], "cd") == 0 \
            && string()->_compare(mini()->argvalue[1], "..") == 0)
        {
            if(chdir(mini()->var.cwd) == -1)
                perror("..->chdir");
        }
        else if(string()->_compare(mini()->argvalue[0], "cd") == 0 \
            && _is_directory(mini()->argvalue[1]) == 1)
        {
            if(chdir(mini()->argvalue[1]) == -1)
                perror("path->chdir");
            printf("pwd : %s\n", getenv("PWD"));
        }
    }
}

// -> Load path at execution time and only change it when cd is executed. 
//      path does not need to be verified each loop

int main(int argc, char** argv, char** envp)
{
    // Checks execution
    if(check_input(argc, argv) == FALSE)
        return (printf("Wrong Input. Enter ./minishell\n"));

    // Inits program information
    if(init(envp) == FALSE)
    {
        close_program();
        return (1);
    }

    char *buffer = NULL;
    ignore_signal_for_shell();
    while (1)
    {
        print_prompt();
        buffer = readline("\e[1;33m$\e[0m ");
        if(string()->_length(buffer) > 0)
            add_history(buffer);
        if(string()->_compare(buffer, "exit") == 0)
        {
            free(buffer);
            break;
        }
        // Gets argv and argc from minishell
        split_args(buffer);

        // Prints the input on screen
        change_d();
        helper_print(0);
        

        free(mini()->argvalue);
        free(buffer);
    }

    // Frees all memory in program
    close_program();

    return (0);
}
