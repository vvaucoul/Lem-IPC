/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:34:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:30:18 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

static char *game_handler_host(void)
{
    static int i = -1;
    char *_dots[3] = {".", "..", "..."};
    ++i;
    if (i > 2)
        i = 0;
    return (_dots[i]);
}

static void display_host_handler_infos(void)
{
    CLEAR_LINE();
    printf(COLOR_YELLOW DIM "\rWaiting for players%s\n" COLOR_RESET, game_handler_host());
    printf(COLOR_MAGENTA DIM "-----------------------------------------------------\n" COLOR_RESET);
    printf(COLOR_CYAN "Players: " COLOR_GREEN "[%zu]" COLOR_CYAN ", Teams: " COLOR_GREEN "[%zu]" COLOR_CYAN "\n" COLOR_RESET, Get_Game()->nb_players, Get_Game()->nb_teams);
    printf(COLOR_MAGENTA DIM "-----------------------------------------------------\n" COLOR_RESET);
    MOVE_LINE_UP(4);
}

static bool client_handler(void)
{
    while (1)
    {
        MSG msg;

        printf(COLOR_CYAN "[%zu] " COLOR_YELLOW "Waiting for message to start game\n" COLOR_RESET, _g_lemipc.id);
        msg = create_msgqueue(NULL, 0);
        if ((msgrcv(Net_IPC.msg_id, &msg, SIZEOF_MSG, 1, 0)) == -1)
            return (display_perror("msgrcv"));
        else if (check_shared_memory() == false)
            return (false);
        else if (ft_strcmp(msg.mtext, MSG_START_GAME) == 0)
        {
            if (ARG_IS_ENABLE(ARG_C))
                printf(DIM COLOR_WHITE "Receive message: [%s]\n", msg.mtext);
            break;
        }
        usleep(GAME_DELAY);
    }
    printf(COLOR_CYAN "[%zu] " COLOR_YELLOW "Game is starting...\n" COLOR_RESET, _g_lemipc.id);
    return (true);
}

static bool host_handler(void)
{
    CLEAR_SCREEN();
    printf(COLOR_CYAN "Waiting for " COLOR_GREEN "[%zu]" COLOR_CYAN " players and " COLOR_GREEN "[%zu]" COLOR_CYAN " teams\n\n" COLOR_RESET, _g_lemipc.pts, _g_lemipc.tts);
    while (Get_Game()->nb_players < _g_lemipc.pts ||
           Get_Game()->nb_teams < _g_lemipc.tts)
    {
        if (check_shared_memory() == false)
            return (false);
        display_host_handler_infos();
        usleep(GAME_DELAY);
    }
    display_host_handler_infos();
    MOVE_LINE_DOWN(4);
    usleep(GAME_DELAY);
    MSG msg;

    msg = create_msgqueue(MSG_START_GAME, 1);

    for (size_t i = 0; i < Get_Game()->nb_players; i++)
    {
        if ((msgsnd(Net_IPC.msg_id, &msg, SIZEOF_MSG, 0)) == -1)
            return (display_perror("msgsnd"));
        else if (ARG_IS_ENABLE(ARG_C))
            printf(DIM COLOR_WHITE "Send message: [%s] -> [%ld]\n", msg.mtext, i);
    }
    printf(COLOR_YELLOW "\rGame is starting !\n" COLOR_RESET);
    return (true);
}

bool game_handler(void)
{
    if (_g_lemipc.authority == NET_AUTHORITY_HOST)
    {
        if ((host_handler()) == false)
            return (false);
    }
    else if (_g_lemipc.authority == NET_AUTHORITY_CLIENT)
    {
        if ((client_handler()) == false)
            return (false);
    }
    return (true);
}