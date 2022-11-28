#include "../includes/minishell.h"

/*
void window_size()
{
    // Add signal to when window size gets changed.
    // It will rl_replace_line() to the current stored prompt
}
    mini()->WINDOW_handler = signal(SIGCONT, SIG_)
void WINDOW_handler(int signum)
{
    rl_replace_line();
}
*/


// Handle ctrl
void ignore_signal_for_shell()
{
	mini()->signalset = TRUE;
	
	// ignore "Ctrl-C" -> alterar para dar display a um nvo prompt numa nova linha
    mini()->SIGINT_handler = signal(SIGINT, SIG_IGN);


	// ignore "Ctrl-\"
    signal(SIGQUIT, SIG_IGN);

    //ignore "Ctrl-D"
    mini()->SIGINT_handler = signal(SIGINT, SIG_IGN);
    //signal(SIGABRT, SIG_IGN);
}