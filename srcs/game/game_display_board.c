/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_display_board.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:42:22 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/20 17:57:43 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

void host_display_board_game(void)
{
    CLEAR_SCREEN();
    for (size_t y = 0; y < MAP_SIZE_Y; y++)
    {
        for (size_t x = 0; x < MAP_SIZE_X; x++)
        {
            int id_stored = Get_Game()->map[y][x].id;

            if (id_stored >= 0)
                printf(COLOR_RED "[%ld]" COLOR_RESET, GET_PLAYER_TEAM(id_stored));
            else
                printf(COLOR_WHITE "[.]" COLOR_RESET);
        }
        printf("\n");
    }
    for (size_t y = 0; y < MAP_SIZE_Y; y++)
    {
        CLEAR_LINE();
        MOVE_LINE_UP(MAP_SIZE_Y);
    }
}