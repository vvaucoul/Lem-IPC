/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:59:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/22 12:19:59 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

Visu _g_visu;
MLX _g_mlx;

static int display_visu_help(void)
{
    printf("Usage: ./lemipc-visualizer [OPTION]\n");
    printf("  lemipc-visualizer: use it to visualize the game with graphic visual.\n  Two options are available. BASH to see the game in bash mode and MLX to see the game with the minilibx\n\n");
    printf("  [OPTIONS]:\n    -h, --help: display this help.\n    -b, --bash: display the game in bash mode.\n    -m, --mlx: display the game with the minilibx.\n");
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (display_visu_help());
    else if (ft_strcmp(argv[1], "-h") == 0 || ft_strcmp(argv[1], "--help") == 0)
        return (display_visu_help());
    else if (ft_strcmp(argv[1], "-b") == 0 || ft_strcmp(argv[1], "--bash") == 0)
        return (bash_mode());
    else if (ft_strcmp(argv[1], "-m") == 0 || ft_strcmp(argv[1], "--mlx") == 0)
        return (mlx_mode());
    else
        return (display_visu_help());
    return (1);
}