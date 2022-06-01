/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:40:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:30:14 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
#define LEMIPC_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <signal.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

#include "libft.h"

/*******************************************************************************
 *                                    UTILS                                    *
 ******************************************************************************/

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_WHITE "\x1b[37m"
#define COLOR_RESET "\x1b[0m"

#define BLINK "\x1b[5m"
#define BOLD "\x1b[1m"
#define UNDERLINE "\x1b[4m"
#define DIM "\x1b[2m"

#define CLEAR_LINE() printf("\33[2K\r")
#define CLEAR_SCREEN() printf("\033[2J\033[H")
#define MOVE_LINE_UP(x) printf("\033[%dA", x)
#define MOVE_LINE_DOWN(x) printf("\033[%dB", x)
#define MOVE_COLUMN_RIGHT(x) printf("\033[%dC", x)
#define MOVE_COLUMN_LEFT(x) printf("\033[%dD", x)

#define GET_PLAYER_TEAM(player_id) (Get_Game()->players[player_id].team)
#define NB_PLAYERS() (Get_Game()->nb_players)

/*******************************************************************************
 *                                   ERRORS                                    *
 ******************************************************************************/

#define ERROR_INVALID_TEAM "invalid team."
#define ERROR_INVALID_ARGUMENT "invalid argument <%s>."
#define ERROR_INVALID_ARGUMENT_LENGTH "an argument is too long."

#define BUFFER_ERROR_SIZE 256

/*******************************************************************************
 *                                  ARGUMENTS                                  *
 ******************************************************************************/

#define ARGUMENTS_LIST                            \
    {                                             \
        "h", "help", "s", "c", "pts:%d", "tts:%d" \
    }
#define ARGUMENTS_LEN    \
    {                    \
        1, 4, 1, 1, 4, 4 \
    }
#define ARGUMENTS_SIZE 6
#define ARGUMENT_DELIM '-'

#define ARG_H 0
#define ARG_S 2
#define ARG_C 3
#define ARG_PTS 4
#define ARG_TTS 5

#define BUFFER_ARG_SIZE 5
#define ARG_IS_ENABLE(arg) (_g_lemipc.options[arg] == true)

/*******************************************************************************
 *                             MAP - CONFIGURATION                             *
 ******************************************************************************/

#define MAP_SIZE_X 60
#define MAP_SIZE_Y 42
#define GAME_MAX_TEAM 32
#define GAME_MAX_PLAYER 256
#define GAME_DELAY 100000
#define MAP_MAX_DISTANCE MAP_SIZE_X *MAP_SIZE_Y
#define GAME_TIMEOUT 60

/*******************************************************************************
 *                           IPCS - MSG - SEMAPHORES                           *
 ******************************************************************************/

#define IPC_KEY (key_t) getuid()
#define IPC_SIZE (size_t)(sizeof(Get_Game()->map) * 2)
#define LOCK() sem_lock()
#define UNLOCK() sem_unlock()
#define MESSAGE_LENGTH 32

#define MSG_START_GAME "START"
#define SIZEOF_MSG (sizeof(msg.mtext))

/*******************************************************************************
 *                                 STRUCTURES                                  *
 ******************************************************************************/

enum e_ia_movement
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = 4
};

#define Movement enum e_ia_movement
#define FOR_EACH_MOVEMENT(movement) \
    for (movement = UP; movement <= RIGHT; movement++)

enum e_net_authority
{
    NET_AUTHORITY_HOST,
    NET_AUTHORITY_CLIENT,
    NET_AUTHORITY_NONE
};

#define NET_AUTHORITY enum e_net_authority
#define IS_HOST() (_g_lemipc.authority == NET_AUTHORITY_HOST)

typedef struct s_point
{
    int x;
    int y;
} t_point;

#define Point t_point

typedef struct message
{
    long mtype;
    char mtext[MESSAGE_LENGTH];
} t_msg;

#define MSG t_msg

typedef struct s_game_player
{
    size_t id;
    size_t team;
    bool is_valid;
} t_game_player;

#define Player t_game_player

typedef struct s_map
{
    Point pos;
    int id; // Player ID if occupied
} t_map;

#define Map t_map

typedef struct s_game
{
    size_t nb_teams;
    size_t nb_players;
    Map map[MAP_SIZE_Y][MAP_SIZE_X];
    Player players[GAME_MAX_PLAYER];
} t_game;

#define Game t_game

typedef struct s_ipc
{
    // Message queue
    int msg_id;

    // Shared Memory
    int shm_id;
    void *shm;

    // Semaphores
    int sem_id;
} t_ipc;

typedef struct s_lemipc
{
    bool options[ARGUMENTS_SIZE];
    size_t pts;
    size_t tts;

    size_t team;
    size_t id;

    t_ipc net_ipc;
    NET_AUTHORITY authority;

} t_lemipc;

#define Lemipc t_lemipc
extern Lemipc _g_lemipc;

#define Net_IPC _g_lemipc.net_ipc
#define Get_Game() ((Game *)(_g_lemipc.net_ipc.shm))

/*******************************************************************************
 *                                META - DATAS                                 *
 ******************************************************************************/

bool meta_host(void);
bool meta_client(void);

/*******************************************************************************
 *                                    GAME                                     *
 ******************************************************************************/

void setup_game(void);
void setup_game_map(void);
void remove_player(void);
void setup_player_placement(void);
bool game_handler(void);
void host_display_board_game(void);
void update_player_location(int player_id, Movement movement);

/*******************************************************************************
 *                                     IA                                      *
 ******************************************************************************/

void ia_movement(void);
Point get_player_location(int player_id);
Movement set_player_movement(int player_id, Point destination);
Movement set_player_random_movement(int player_id);
bool check_player_is_dead(int player_id);
bool check_team_won(void);
bool check_match_nul(void);
bool check_timeout(void);

/*******************************************************************************
 *                              CHECK - ARGUMENTS                              *
 ******************************************************************************/

bool check_arguments(size_t argc, char **argv);

/*******************************************************************************
 *                               LEMIPC - UTILS                                *
 ******************************************************************************/

bool init_signals(void);

void init_lemipc(void);
NET_AUTHORITY get_net_authority(void);
MSG create_msgqueue(const char *str, int type);
int get_random_integer(int min, int max);
bool check_shared_memory(void);

bool sem_lock(void);
bool sem_unlock(void);
bool delete_all(void);

int display_help(void);
int display_error(const char *str);
int display_perror(const char *str);

#endif