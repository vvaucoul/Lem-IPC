/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_host_init_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:24:44 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/25 13:01:36 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

void setup_game_map(void)
{
    for (size_t y = 0; y < MAP_SIZE_Y; y++)
    {
        for (size_t x = 0; x < MAP_SIZE_X; x++)
        {
            Get_Game()->map[y][x] = (Map){(Point){y, x}, -1};
        }
    }
    for (size_t i = 0; i < GAME_MAX_PLAYER; i++)
        Get_Game()->players[i] = (Player){0, 0, false};
    Get_Game()->nb_teams = 0;
    Get_Game()->nb_players = 0;
}