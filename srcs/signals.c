#include "../includes/minishell.h"

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