#include "../includes/minishell.h"

extern int g_exit_status;

void sig_block(int signo)
{
    (void)signo;
    signal(SIGINT, SIG_IGN);
    g_exit_status = 130;
}

void sig_block_c(int signo)
{
    (void)signo;
    signal(SIGINT, SIG_IGN);
    g_exit_status = 130;
    string()->_putchar_fd('\n', 1);
}

void sigint_handler(int signum) 
{
	(void) signum;
	g_exit_status = 130;
	string()->_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void sigquit_handler(int signum)
{
    (void) signum;
    rl_replace_line("", 0);
	rl_redisplay();
}

void sigterm_handler(int signum)
{
    (void) signum;
    g_exit_status = 127;
    string()->_putchar_fd('\n', 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

