/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:28:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 14:47:45 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

static bool has_enough_team_to_die(int teams_stored[4])
{
    for (int i = 0; i < 4; i++)
    {
        size_t count = 0;
        for (int j = 0; j < 4; j++)
        {
            if (teams_stored[j] == teams_stored[i])
                count++;
        }
        if (count >= 2)
            return (true);
    }
    return (false);
}

static bool player_shoud_die(int player_id)
{
    Point player_location = get_player_location(player_id);
    size_t player_team = GET_PLAYER_TEAM(player_id);
    int teams_stored[4] = {-1, -1, -1, -1};

    int current_id = 0;
    size_t current_team = 0;
    size_t n = 0;

    if (player_location.x + 1 < MAP_SIZE_X)
    {
        if ((current_id = Get_Game()->map[player_location.y][player_location.x + 1].id) >= 0)
        {
            current_team = GET_PLAYER_TEAM(current_id);
            if (current_team != player_team)
            {
                teams_stored[RIGHT] = Get_Game()->players[current_id].team;
                ++n;
            }
        }
    }
    if (player_location.x - 1 >= 0)
    {
        if ((current_id = Get_Game()->map[player_location.y][player_location.x - 1].id) >= 0)
        {
            current_team = GET_PLAYER_TEAM(current_id);
            if (current_team != player_team)
            {
                teams_stored[LEFT] = Get_Game()->players[current_id].team;
                ++n;
            }
        }
    }
    if (player_location.y + 1 < MAP_SIZE_Y)
    {
        if ((current_id = Get_Game()->map[player_location.y + 1][player_location.x].id) >= 0)
        {
            current_team = GET_PLAYER_TEAM(current_id);
            if (current_team != player_team)
            {
                teams_stored[DOWN] = Get_Game()->players[current_id].team;
                ++n;
            }
        }
    }
    if (player_location.y - 1 >= 0)
    {
        if ((current_id = Get_Game()->map[player_location.y - 1][player_location.x].id) >= 0)
        {
            current_team = GET_PLAYER_TEAM(current_id);
            if (current_team != player_team)
            {
                teams_stored[UP] = Get_Game()->players[current_id].team;
                ++n;
            }
        }
    }
    return (n >= 2 && has_enough_team_to_die(teams_stored));
}

bool check_player_is_dead(int player_id)
{
    if (player_shoud_die(player_id) == true)
        return (true);
    return (false);
}

bool check_team_won(void)
{
    if (Get_Game()->nb_teams <= 1)
        return (true);
    return (false);
}

bool check_match_nul(void)
{
    if (Get_Game()->nb_teams == 2 && Get_Game()->nb_players == 2)
        return (true);
    else if (Get_Game()->nb_teams == Get_Game()->nb_players)
        return (true);
    return (false);
}

bool check_timeout(void)
{
    // debug, ca marche poooooooo
    static struct timeval start;
    static bool init = false;
    struct timeval current_time;

    if (init == false)
    {
        gettimeofday(&start, NULL);
        init = true;
    }

    gettimeofday(&current_time, NULL);
    if (current_time.tv_sec - start.tv_sec >= GAME_TIMEOUT)
        return (true);
    return (false);
}