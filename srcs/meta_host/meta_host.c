/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_host.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:38:20 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/20 13:21:43 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

static bool create_ipc(void)
{
    if ((Net_IPC.shm_id = shmget(IPC_KEY, IPC_SIZE, 0666 | IPC_CREAT)) == -1)
        return (display_perror("shmget"));
    else
    {
        if ((Net_IPC.shm = shmat(Net_IPC.shm_id, NULL, 0)) == NULL)
            return (display_perror("shmat"));
        return (true);
    }
}

static bool create_msg(void)
{
    if ((Net_IPC.msg_id = msgget(IPC_KEY, 0666 | IPC_CREAT)) == -1)
        return (display_perror("msgget"));
    else
        return (true);
}

static bool create_semaphores(void)
{
    if ((Net_IPC.sem_id = semget(IPC_KEY, 1, 0666 | IPC_CREAT)) == -1)
        return (display_perror("semget"));
    else
    {
        if ((semctl(Net_IPC.sem_id, 0, SETVAL, 1)) == -1)
            return (display_perror("semctl"));
        return (true);
    }
}

bool meta_host(void)
{
    if (create_ipc() == false)
        return (false);
    if (create_msg() == false)
        return (false);
    if (create_semaphores() == false)
        return (false);
    setup_game_map();
    return (true);
}