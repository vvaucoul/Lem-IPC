/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:18:26 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/22 14:00:29 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

static void sig_handler(int sig)
{
    if (sig == SIGINT || SIGSEGV)
    {
        CLEAR_LINE();
        printf(COLOR_YELLOW"Quit visualizer mode...\n"COLOR_RESET);
        exit(EXIT_SUCCESS);
    }
}
bool init_visualizer_signals(void)
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        return (display_perror("signal"));
    if (signal(SIGSEGV, sig_handler) == SIG_ERR)
        return (display_perror("signal"));
    return (true);
}

bool check_shm(void)
{
    if (shmget(IPC_KEY, sizeof(t_game), 0666) == -1)
        return (false);
    return (true);
}

Point get_terminal_size(void)
{
    struct winsize w;
    Point size;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return ((Point){0, 0});
    size.x = w.ws_col;
    size.y = w.ws_row;
    return (size);
}

int display_error(const char *str)
{
    fprintf(stderr, COLOR_RED"%s\n"COLOR_RESET, str);
    return (1);
}

int display_perror(const char *str)
{
    perror(str);
    return (1);
}