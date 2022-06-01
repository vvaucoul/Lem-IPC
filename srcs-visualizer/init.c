/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:13:09 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/22 15:09:44 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

static char *get_dots(void)
{
    char *dots[3] = {
        ".",
        "..",
        "..."};
    static int i = 0;

    if (i == 3)
        i = 0;
    return (dots[i++]);
}

bool init_visualizer(void)
{
    printf(COLOR_YELLOW "Initializing visualizer...\n" COLOR_RESET);

    _g_visu.shm_id = -1;
    srand(time(NULL));
    if ((init_visualizer_signals()) == false)
        return (false);
    do
    {
        CLEAR_LINE();
        printf(COLOR_YELLOW "Waiting for host%s\n" COLOR_RESET, get_dots());
        _g_visu.shm_id = shmget(IPC_KEY, sizeof(t_game), 0666);
        usleep(GAME_DELAY);
        MOVE_LINE_UP(1);
    } while (_g_visu.shm_id < 0);
    if ((_g_visu.game = (t_game *)shmat(_g_visu.shm_id, NULL, 0)) == NULL)
        return (display_perror("shmat"));
    return (true);
}