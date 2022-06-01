/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:05:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 12:54:22 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

static void display_infos(void)
{
    printf(COLOR_CYAN "Players: [%zu]\n" COLOR_RESET, _g_visu.game->nb_players);
    printf(COLOR_CYAN "Teams: [%zu]\n" COLOR_RESET, _g_visu.game->nb_teams);
    printf(COLOR_CYAN "Map size: [%u * %u]\n\n" COLOR_RESET, MAP_SIZE_X, MAP_SIZE_Y);
}

static void print_color_by_team(size_t team)
{
    if (team == 0)
        printf(COLOR_RED);
    else if (team == 1)
        printf(COLOR_GREEN);
    else if (team == 2)
        printf(COLOR_YELLOW);
    else if (team == 3)
        printf(COLOR_BLUE);
    else if (team == 4)
        printf(COLOR_MAGENTA);
    else if (team == 5)
        printf(COLOR_CYAN);
    else if (team == 6)
        printf(COLOR_WHITE);
}

static void display_bash_board(void)
{
    for (size_t y = 0; y < MAP_SIZE_Y; y++)
    {
        for (size_t x = 0; x < MAP_SIZE_X; x++)
        {
            int id_stored = GET_VISU_GAME()->map[y][x].id;

            if (id_stored >= 0)
            {
                print_color_by_team(GET_VISU_PLAYER_TEAM(id_stored));
                printf("[%ld]" COLOR_RESET, GET_VISU_PLAYER_TEAM(id_stored));
            }
            else
                printf(COLOR_WHITE "[.]" COLOR_RESET);
        }
        printf("\n" COLOR_RESET);
    }
}

int bash_mode(void)
{
    Point term_size;

    term_size = get_terminal_size();
    if ((term_size.x < (MAP_SIZE_X * 3)) || term_size.y < (MAP_SIZE_Y))
        return (display_error(ERROR_TERMINAL_SIZE) | EXIT_FAILURE);
    if ((init_visualizer()) == false)
        return (EXIT_FAILURE);
    else
    {
        while (1)
        {
            if ((check_shm()) == false)
            {
                printf(COLOR_YELLOW "Exit visualizer " COLOR_CYAN "[BASH MODE]\n" COLOR_RESET);
                return (1);
            }
            CLEAR_SCREEN();
            display_infos();
            display_bash_board();
            usleep(GAME_DELAY / 2);
        }
    }
    return (0);
}