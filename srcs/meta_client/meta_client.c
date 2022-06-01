/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:39:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 13:21:01 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

static bool get_ipc(void)
{
    if ((Net_IPC.shm_id = shmget(IPC_KEY, (sizeof(Map) * ((MAP_SIZE_X + 1) * (MAP_SIZE_Y + 1))), 0666)) == -1)
        return (display_perror("shmget"));
    else if ((Net_IPC.shm = shmat(Net_IPC.shm_id, NULL, 0)) == NULL)
        return (display_perror("shmat"));
    return (true);
}
static bool get_msg(void)
{
    if ((Net_IPC.msg_id = msgget(IPC_KEY, 0666)) == -1)
        return (display_perror("msgget"));
    else
        return (true);
}
static bool get_semaphores(void)
{
    if ((Net_IPC.sem_id = semget(IPC_KEY, 1, 0666 | IPC_CREAT)) == -1)
        return (display_perror("semget"));
    else
        return (true);
}

bool meta_client(void)
{
    if (get_ipc() == false)
        return (false);
    if (get_msg() == false)
        return (false);
    if (get_semaphores() == false)
        return (false);
    return (true);
}
