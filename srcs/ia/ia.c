/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:00:20 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:42:57 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

static int get_distance(Point location, Point destination)
{
    return (abs(location.x - destination.x) + abs(location.y - destination.y));
}
Point get_player_location(int player_id)
{
    for (size_t y = 0; y < MAP_SIZE_Y; y++)
    {
        for (size_t x = 0; x < MAP_SIZE_X; x++)
        {
            if (Get_Game()->map[y][x].id == player_id)
                return ((Point){x, y});
        }
    }
    return ((Point){-1, -1});
}

static void ia_checker(int current_player_id)
{
    if ((check_player_is_dead(current_player_id)) == true)
    {
        remove_player();
        UNLOCK();
        printf(COLOR_YELLOW "Player [%d] die...\n" COLOR_RESET, current_player_id);
        exit(EXIT_SUCCESS);
    }
    else if ((check_team_won()) == true)
    {
        remove_player();
        UNLOCK();
        printf(COLOR_YELLOW "Team [%ld] won...\n" COLOR_RESET, _g_lemipc.team);
        exit(EXIT_SUCCESS);
    }
    else if ((check_match_nul()) == true)
    {
        remove_player();
        UNLOCK();
        printf(COLOR_YELLOW "No team won, match nul...\n" COLOR_RESET);
        exit(EXIT_SUCCESS);
    }
    else if ((check_timeout()) == true)
    {
        remove_player();
        UNLOCK();
        printf(COLOR_YELLOW "Timeout. Not enough time to finish the game...\n" COLOR_RESET);
        delete_all();
        exit(EXIT_SUCCESS);
    }
}

void ia_movement(void)
{
    LOCK();

    int current_player_id = _g_lemipc.id;
    Point current_location = get_player_location(current_player_id);
    Point target_destination;
    int distance = MAP_MAX_DISTANCE;
    int target_id = -1;

    ia_checker(current_player_id);
    for (size_t i = 0; i < GAME_MAX_PLAYER; i++)
    {
        int player_id = i;
        Point current_target_destination = get_player_location(player_id);

        if (current_target_destination.x == -1 || current_target_destination.y == -1 ||
            GET_PLAYER_TEAM(player_id) == GET_PLAYER_TEAM(current_player_id) ||
            player_id == current_player_id)
            continue;
        else
        {
            int current_distance = get_distance(current_location, current_target_destination);
            if (current_distance < distance)
            {
                distance = current_distance;
                target_destination = current_target_destination;
                target_id = player_id;
            }
        }
    }
    if (target_id >= 0)
    {
        Movement movement = set_player_movement(current_player_id, target_destination);
        update_player_location(current_player_id, movement);
    }
    else
    {
        Movement movement = set_player_random_movement(current_player_id);
        update_player_location(current_player_id, movement);
    }
    ia_checker(current_player_id);
    UNLOCK();
}