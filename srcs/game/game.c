/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:21:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:06:51 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

static void set_nb_team(size_t current_team)
{
    for (size_t i = 0; i < GAME_MAX_PLAYER; i++)
    {
        if (Get_Game()->players[i].team == current_team)
            return;
    }
    Get_Game()->nb_teams++;
}

static void set_id(void)
{
    _g_lemipc.id = Get_Game()->nb_players;
    Get_Game()->nb_players++;
}

static void pop_back_game_player(size_t id)
{
    for (size_t i = 0; i < GAME_MAX_PLAYER; i++)
    {
        if (Get_Game()->players[i].id == id)
        {
            Point player_location = get_player_location(id);
            Get_Game()->players[i].id = -1;
            Get_Game()->players[i].team = 0;
            Get_Game()->players[i].is_valid = false;
            if (player_location.x >= 0 && player_location.y >= 0)
                Get_Game()->map[player_location.y][player_location.x].id = -1;
            break;
        }
    }
}

static void push_back_game_player(size_t id, size_t team)
{
    for (size_t i = 0; i < GAME_MAX_PLAYER; i++)
    {
        if (Get_Game()->players[i].is_valid == false)
        {
            Get_Game()->players[i].id = id;
            Get_Game()->players[i].team = team;
            Get_Game()->players[i].is_valid = true;
            return;
        }
    }
}

void setup_game(void)
{
    LOCK();
    set_id();
    set_nb_team(_g_lemipc.team);
    push_back_game_player(_g_lemipc.id, _g_lemipc.team);
    UNLOCK();
}

void remove_player_by_id(size_t id)
{
    Get_Game()->nb_players--;
    if (Get_Game()->nb_players == 0)
    {
        UNLOCK();
        delete_all();
        return;
    }
    else
        pop_back_game_player(id);
}

void remove_player(void)
{
    Get_Game()->nb_players--;
    if (Get_Game()->nb_players == 0)
    {
        delete_all();
        return;
    }
    else
    {
        pop_back_game_player(_g_lemipc.id);
        for (size_t i = 0; i < GAME_MAX_PLAYER; i++)
        {
            if (Get_Game()->players[i].team == _g_lemipc.team && i != _g_lemipc.id)
                return;
        }
        Get_Game()->nb_teams--;
    }
}

void update_player_location(int player_id, Movement movement)
{
    Point location = get_player_location(player_id);

    switch (movement)
    {
    case UP:
    {
        Get_Game()->map[location.y - 1][location.x].id = player_id;
        Get_Game()->map[location.y][location.x].id = -1;
        break;
    }
    case DOWN:
    {
        Get_Game()->map[location.y + 1][location.x].id = player_id;
        Get_Game()->map[location.y][location.x].id = -1;
        break;
    }
    case LEFT:
    {
        Get_Game()->map[location.y][location.x - 1].id = player_id;
        Get_Game()->map[location.y][location.x].id = -1;
        break;
    }
    case RIGHT:
    {
        Get_Game()->map[location.y][location.x + 1].id = player_id;
        Get_Game()->map[location.y][location.x].id = -1;
        break;
    }
    default:
        break;
    }
}

void setup_player_placement(void)
{
    LOCK();
    for (size_t i = 0; i < Get_Game()->nb_players; i++)
    {
        Point location;
        do
        {
            location.x = get_random_integer(1, MAP_SIZE_X - 1);
            location.y = get_random_integer(1, MAP_SIZE_Y - 1);
        } while (Get_Game()->map[location.y][location.x].id >= 0);
        Get_Game()->map[location.y][location.x].id = i;
    }
    UNLOCK();
    printf(COLOR_YELLOW "[%ld] End players placement: %ld\n" COLOR_RESET, _g_lemipc.id, Get_Game()->nb_players);
}