/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:05:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 12:31:16 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

static int exit_mlx_mode(int key, void *param)
{
    (void)param;
    (void)key;
    if (_g_mlx.mlx_image.img_ptr)
    {
        if ((mlx_destroy_image(_g_mlx.mlx_ptr, _g_mlx.mlx_image.img_ptr)) == -1)
            display_perror("mlx_destroy_image");
    }
    if ((mlx_clear_window(_g_mlx.mlx_ptr, _g_mlx.window)) == -1)
        display_perror("mlx_clear_window");
    if ((mlx_destroy_window(_g_mlx.mlx_ptr, _g_mlx.window)) == -1)
        display_perror("mlx_destroy_window");
    if ((mlx_destroy_display(_g_mlx.mlx_ptr)) == -1)
        display_perror("mlx_destroy_display");
    if (_g_mlx.mlx_ptr)
        free(_g_mlx.mlx_ptr);
    exit(EXIT_SUCCESS);
}

static void mlx_draw_pixel(int x, int y, int color)
{
    if (x < MLX_RES_X && y < MLX_RES_Y &&
        x >= 0 && y >= 0)
        ft_memcpy(_g_mlx.mlx_image.img_data + 4 * MLX_RES_X * y + x * 4, &color, sizeof(int));
}

static int mlx_set_color(int red, int green, int blue)
{
    return (red << 16 | green << 8 | blue);
}

static void mlx_draw_square(size_t sx, size_t sy, size_t w, size_t h, int color)
{
    for (size_t y = sy; y < sy + h; ++y)
    {
        for (size_t x = sx; x < sx + w; ++x)
        {
            mlx_draw_pixel(x, y, color);
        }
    }
}

static void mlx_fill_image(int color)
{
    mlx_draw_square(0, 0, MLX_RES_X, MLX_RES_Y, color);
}

static bool init_mlx(void)
{
    if ((_g_mlx.mlx_ptr = mlx_init()) == NULL)
        return (display_perror("mlx_init"));
    if ((_g_mlx.window = mlx_new_window(_g_mlx.mlx_ptr, MLX_RES_X, MLX_RES_Y, MLX_WINDOW_NAME)) == NULL)
        return (display_perror("mlx_new_window"));
    if ((_g_mlx.mlx_image.img_ptr = mlx_new_image(_g_mlx.mlx_ptr, MLX_RES_X, MLX_RES_Y)) == NULL)
        return (display_perror("mlx_new_image"));
    if ((_g_mlx.mlx_image.img_data = mlx_get_data_addr(_g_mlx.mlx_image.img_ptr, &_g_mlx.mlx_image.bpp, &_g_mlx.mlx_image.size_line, &_g_mlx.mlx_image.endian)) == NULL)
        return (display_perror("mlx_get_data_addr"));
    else
    {
        mlx_fill_image(MLX_COLOR_BLACK);
        mlx_put_image_to_window(_g_mlx.mlx_ptr, _g_mlx.window, _g_mlx.mlx_image.img_ptr, 0, 0);
    }
    return (true);
}

static int get_team_color(int team_id)
{
    static int team_color[GAME_MAX_TEAM];
    static bool init = false;

    if (init == false)
    {
        ft_bzero(team_color, sizeof(int) * GAME_MAX_TEAM);
        for (size_t i = 0; i < GAME_MAX_TEAM; i++)
            team_color[i] = mlx_set_color(rand() % 255, rand() % 255, rand() % 255);
        init = true;
    }
    else
        return (team_color[team_id]);
    return (0);
}

static int draw_visualizer(void *ptr)
{
    (void)ptr;
    if ((check_shm()) == false)
    {
        printf(COLOR_YELLOW "Exit visualizer " COLOR_CYAN "[MLX MODE]\n" COLOR_RESET);
        exit_mlx_mode(0, NULL);
    }
    mlx_fill_image(MLX_COLOR_BLACK);
    for (size_t y = 0; y < MAP_SIZE_Y; ++y)
    {
        for (size_t x = 0; x < MAP_SIZE_X; x++)
        {
            int id_stored = GET_VISU_GAME()->map[y][x].id;
            if (id_stored >= 0)
            {
                int color = get_team_color(GET_VISU_GAME()->players[id_stored].team);
                mlx_draw_square(x * MLX_SCALE_X, y * MLX_SCALE_Y, MLX_SCALE_X, MLX_SCALE_Y, color);
            }
        }
    }
    mlx_put_image_to_window(_g_mlx.mlx_ptr, _g_mlx.window, _g_mlx.mlx_image.img_ptr, 0, 0);
    return (0);
}

int mlx_mode(void)
{
    if ((init_visualizer()) == false)
        return (EXIT_FAILURE);
    CLEAR_SCREEN();
    printf("\n");
    MOVE_LINE_UP(1);
    if ((init_mlx()) == false)
    {
        exit_mlx_mode(0, NULL);
        return (EXIT_FAILURE);
    }
    mlx_hook(_g_mlx.window, 17, (1L << 17), exit_mlx_mode, NULL);
    mlx_loop_hook(_g_mlx.mlx_ptr, draw_visualizer, NULL);
    mlx_loop(_g_mlx.mlx_ptr);
    return (0);
}