/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:21:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:22:30 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../../includes/lemipc.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

#define PROCESS "./lemipc"
#define PROCESS_ARGS "%d"

int n;
pid_t pids[256];

static void sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        for (size_t i = 0; i < (size_t)n; i++)
        {
            kill(pids[i], SIGINT);
        }       
        exit(EXIT_SUCCESS);
    }
}

static bool signals(void)
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        perror("signal");
        return (false);
    }
    return (true);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: ./lemipc-processus <N-Processus> <N-Teams>\n");
        return (EXIT_FAILURE);
    }
    else
    {
        n = atoi(argv[1]);
        if ((signals()) == false)
            return (EXIT_FAILURE);
        int teams = atoi(argv[2]);
        if (n < 1 || n > 254)
        {
            fprintf(stderr, COLOR_RED "N-Processus must be between 1 and 254\n" COLOR_RESET);
            return (EXIT_FAILURE);
        }
        else if (teams < 1 || teams > 32)
        {
            fprintf(stderr, COLOR_RED "N-Teams must be between 1 and 32\n" COLOR_RESET);
            return (EXIT_FAILURE);
        }
        else if ((msgget(IPC_KEY, 0666)) == -1)
        {
            fprintf(stderr, COLOR_RED "Error: launch the server before cprocess !\n" COLOR_RESET);
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Clients: %d\n", n);
            printf("Teams: %d\n", teams);

            for (int i = 0; i < n; i++)
            {
                pid_t pid = fork();

                if (pid == -1)
                {
                    fprintf(stderr, "Fork failed\n");
                    return (EXIT_FAILURE);
                }
                else if (!pid)
                {
                    char buffer[4] = {0};

                    sprintf(buffer, PROCESS_ARGS, ((i + 1) % teams) + 1);
                    if ((execvp(PROCESS, (char *[]){PROCESS, buffer, NULL})) == -1)
                    {
                        fprintf(stderr, "Exec failed\n");
                        perror("execvp");
                        return (EXIT_FAILURE);
                    }
                    return (EXIT_SUCCESS);
                }
                else
                {
                    printf("Start Client: %d\n", i);
                    pids[i] = pid;
                }
                usleep(GAME_DELAY / 100);
            }

            for (int i = 0; i < n; i++)
            {
                waitpid(pids[i], NULL, 0);
            }
        }
    }
    return (0);
}