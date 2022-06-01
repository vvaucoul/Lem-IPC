/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:00:13 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/22 19:21:19 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "../lib/includes/mlx.h"
#include <sys/ioctl.h>

#define ERROR_TERMINAL_SIZE "Error: terminal size is too small."

#define MLX_RES_X 1600
#define MLX_RES_Y 900

#define MLX_SCALE_X (MLX_RES_X / MAP_SIZE_X)
#define MLX_SCALE_Y (MLX_RES_Y / MAP_SIZE_Y)

#define MLX_WINDOW_NAME "lemipc"

#define MLX_COLOR_BLACK 0x000000
#define MLX_COLOR_WHITE 0xFFFFFF
#define MLX_COLOR_RED 0xFF0000
#define MLX_COLOR_GREEN 0x00FF00
#define MLX_COLOR_BLUE 0x0000FF
#define MLX_COLOR_YELLOW 0xFFFF00
#define MLX_COLOR_MAGENTA 0xFF00FF
#define MLX_COLOR_CYAN 0x00FFFF

/*******************************************************************************
 *                                 STRUCTURES                                  *
 ******************************************************************************/

typedef struct s_mlx_image
{
    void *img_ptr;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
} t_mlx_image;

typedef struct s_mlx_viewport
{
    void *mlx_ptr;
    void *window;
    t_mlx_image mlx_image;
} t_mlx_viewport;

#define MLX t_mlx_viewport

typedef struct s_visualizer
{
    int shm_id;
    Game *game;
} t_visualizer;

#define Visu t_visualizer

extern Visu _g_visu;
extern MLX _g_mlx;

#define GET_VISU_GAME() _g_visu.game
#define GET_VISU_PLAYER_TEAM(id) (GET_VISU_GAME()->players[id].team)

/*******************************************************************************
 *                                  FUNCTIONS                                  *
 ******************************************************************************/

int bash_mode(void);
int mlx_mode(void);

bool init_visualizer(void);
bool init_visualizer_signals(void);

bool check_shm(void);
int display_perror(const char *str);
int display_error(const char *str);
Point get_terminal_size(void);
