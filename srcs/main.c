/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:34:10 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:33:39 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

Lemipc _g_lemipc;

static bool execution(void)
{
    _g_lemipc.authority = get_net_authority();
    if (_g_lemipc.authority == NET_AUTHORITY_HOST)
    {
        if ((meta_host()) == false)
            return (false);
    }
    else if (_g_lemipc.authority == NET_AUTHORITY_CLIENT)
    {
        if ((meta_client()) == false)
            return (false);
    }
    else
        return (false);

    setup_game();
    init_signals();

    if ((game_handler() == false))
        return (false);
    if (IS_HOST() == true)
        setup_player_placement();
    usleep(GAME_DELAY);
    while (1)
    {
        if (IS_HOST() == true && ARG_IS_ENABLE(ARG_S) == true)
            host_display_board_game();
        if ((check_shared_memory()) == false)
            return (false);
        ia_movement();
        usleep(GAME_DELAY);
    }
    return (true);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return (display_help());
    else
    {
        init_lemipc();
        if ((check_arguments(argc, argv)) == false)
            return (EXIT_FAILURE);
        else if ((execution()) == false)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}