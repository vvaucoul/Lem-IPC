/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:33:04 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

/*******************************************************************************
 *                                   LEMIPC                                    *
 ******************************************************************************/

void init_lemipc(void)
{
    srand(time(NULL));
    ft_bzero(_g_lemipc.options, sizeof(_g_lemipc.options));
    _g_lemipc.pts = 4;
    _g_lemipc.tts = 2;
    _g_lemipc.team = 0;
    _g_lemipc.id = 0;
    _g_lemipc.net_ipc.msg_id = 0;
    _g_lemipc.net_ipc.shm_id = 0;
    _g_lemipc.net_ipc.shm = NULL;
    _g_lemipc.net_ipc.sem_id = 0;
    _g_lemipc.authority = NET_AUTHORITY_NONE;
}

NET_AUTHORITY get_net_authority(void)
{
    return ((msgget(IPC_KEY, 0666) == -1) ? NET_AUTHORITY_HOST : NET_AUTHORITY_CLIENT);
}

bool sem_lock(void)
{
    struct sembuf sops;

    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = 0;

    if (Net_IPC.sem_id == -1)
        return (false);
    semop(Net_IPC.sem_id, &sops, 1);
    return (true);
}

bool sem_unlock(void)
{
    struct sembuf sops;

    sops.sem_num = 0;
    sops.sem_op = 1;
    sops.sem_flg = 0;

    if (Net_IPC.sem_id == -1)
        return (false);
    semop(Net_IPC.sem_id, &sops, 1);
    return (true);
}

bool delete_all(void)
{
    if (shmctl(Net_IPC.shm_id, IPC_RMID, NULL) == -1)
        return (false);
    if (msgctl(Net_IPC.msg_id, IPC_RMID, NULL) == -1)
        return (false);
    if (semctl(Net_IPC.sem_id, 0, IPC_RMID, 0) == -1)
        return (false);
    printf(COLOR_YELLOW DIM "Deleting all shared memory, IPC and semaphores...\n" COLOR_RESET);
    return (true);
}

MSG create_msgqueue(const char *str, int type)
{
    MSG msg;

    ft_bzero(msg.mtext, sizeof(msg.mtext));
    ft_memcpy(msg.mtext, str, sizeof(msg.mtext));
    msg.mtype = type;
    return (msg);
}

int get_random_integer(int min, int max)
{
    int tmp;

    if (min > max)
    {
        tmp = min;
        min = max;
        max = tmp;
    }
    return ((rand() % ((max - min) + 1) + min));
}

bool check_shared_memory(void)
{
    if (shmget(IPC_KEY, sizeof(t_game), 0666) == -1)
        return (false);
    return (true);
}

/*******************************************************************************
 *                               LEMIPC - UTILS                                *
 ******************************************************************************/

int display_help(void)
{
    printf("Usage: ./lemipc [TEAM] [OPTIONS]...\n");
    printf("  Lemipc is a simple IPC game with multiple processus.\n");
    printf("  First execution: [HOST]\n");
    printf("  Second execution and more: [CLIENT]\n\n");
    printf("  [TEAM]: team number (1 to %d)\n", GAME_MAX_TEAM);
    printf("  [OPTIONS]:\n");
    printf("    -h: display this help\n");
    printf("    -s: display shared memory segment\n");
    printf("    -c: display communications between processus.\n");
    printf("    --pts:<n>: set the number of players to start the game. (Default: 4)\n");
    printf("    --tts:<n>: set the number of teams to start the game. (Default: 2)\n");
    printf("\n  Examples:\n");
    printf("    ./lemipc 1\n");
    printf("    ./lemipc 1 --tts:8\n");
    printf("    ./lemipc 1 --tts:8 --pts:4\n");
    return (0);
}

int display_error(const char *str)
{
    fprintf(stderr, "Error: %s\n", str);
    return (false);
}

int display_perror(const char *str)
{
    perror(str);
    return (false);
}