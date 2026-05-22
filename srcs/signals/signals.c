/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:14:39 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/22 16:08:20 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#include "minishell.h"

volatile sig_atomic_t g_last_signal = 0;

/* Move to a new line and reset the current input */
static void sigint_prompt_handler(int sig)
{
    (void)sig;
    g_last_signal = SIGINT;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

/* Helper to install handler */
static void set_action(int signo, void (*handler)(int), int flags)
{
    struct sigaction	sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = flags;
    sigaction(signo, &sa, NULL);
}

/* Parent at prompt */
void signals_set_interactive(void)
{
    set_action(SIGINT, sigint_prompt_handler, SA_RESTART);
    set_action(SIGQUIT, SIG_IGN, 0);
}

/* Parent while children are running */
void signals_set_parent_waiting(void)
{
    set_action(SIGINT, SIG_IGN, 0);
    set_action(SIGQUIT, SIG_IGN, 0);
}

/* Child before exec */
void signals_set_child_exec(void)
{
    set_action(SIGINT, SIG_DFL, 0);
    set_action(SIGQUIT, SIG_DFL, 0);
}
