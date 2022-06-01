/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:56:11 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:30:58 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

static void sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        CLEAR_LINE();
        printf("" COLOR_CYAN "[%zu] " COLOR_YELLOW "You left the game... " COLOR_RESET "\n", _g_lemipc.id);
        UNLOCK();
        delete_all();
        exit(EXIT_FAILURE);
    }
    else
        UNLOCK();
}

bool init_signals(void)
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        return (display_perror("signal"));
    return (true);
}