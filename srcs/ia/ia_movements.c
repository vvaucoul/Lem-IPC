/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_movements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:15:58 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/26 20:09:55 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

static void get_neight_placements_valid(int player_id, bool neights[4])
{
    Point player_location = get_player_location(player_id);
    ft_bzero(neights, 4);

    if (Get_Game()->map[player_location.y][player_location.x + 1].id == -1 && player_location.x + 1 < MAP_SIZE_X)
        neights[RIGHT] = true;
    else
        neights[RIGHT] = false;
    if (Get_Game()->map[player_location.y][player_location.x - 1].id == -1 && player_location.x - 1 > 0)
        neights[LEFT] = true;
    else
        neights[LEFT] = false;
    if (Get_Game()->map[player_location.y + 1][player_location.x].id == -1 && player_location.y + 1 < MAP_SIZE_Y)
        neights[DOWN] = true;
    else
        neights[DOWN] = false;
    if (Get_Game()->map[player_location.y - 1][player_location.x].id == -1 && player_location.y - 1 > 0)
        neights[UP] = true;
    else
        neights[UP] = false;
}

static Movement get_player_movement(int player_id, Point destination)
{
    Point player_location = get_player_location(player_id);

    if (player_location.x < destination.x)
    {
        if (player_location.y < destination.y)
            return (get_random_integer(0, 1) == 0 ? RIGHT : DOWN);
        else if (player_location.y > destination.y)
            return (get_random_integer(0, 1) == 0 ? RIGHT : UP);
        else
            return (RIGHT);
    }
    else if (player_location.x > destination.x)
    {
        if (player_location.y < destination.y)
            return (get_random_integer(0, 1) == 0 ? LEFT : DOWN);
        else if (player_location.y > destination.y)
            return (get_random_integer(0, 1) == 0 ? LEFT : UP);
        else
            return (LEFT);
    }
    else
    {
        if (player_location.y < destination.y)
            return (DOWN);
        else if (player_location.y > destination.y)
            return (UP);
        else
            return (NONE);
    }
    return (NONE);
}

static Movement get_random_valid_neight(bool neights[4])
{
    int random_neight = get_random_integer(0, 3);
    bool valid = false;
    Movement movement;

    FOR_EACH_MOVEMENT(movement)
    {
        if (neights[movement] == true)
        {
            valid = true;
            break;
        }
    }
    if (valid == false)
        return (NONE);
    while (neights[random_neight] == false)
        random_neight = get_random_integer(0, 3);
    return (random_neight);
}

Movement set_player_random_movement(int player_id)
{
    bool neights[4];

    get_neight_placements_valid(player_id, neights);
    return (get_random_valid_neight(neights));
}

Movement set_player_movement(int player_id, Point destination)
{
    Movement movement;
    bool neights[4];

    movement = get_player_movement(player_id, destination);
    get_neight_placements_valid(player_id, neights);
    if (neights[movement] == false)
        return (get_random_valid_neight(neights));
    return (movement);
}