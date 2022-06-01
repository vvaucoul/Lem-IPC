/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:20:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/27 15:10:21 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemipc.h"

/*******************************************************************************
 *                                    UTILS                                    *
 ******************************************************************************/

static bool check_team(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i++;
    }
    _g_lemipc.team = ft_atoi(str);
    return (true);
}

static int return_error_buffer(const char *str)
{
    char buffer[BUFFER_ERROR_SIZE];

    ft_bzero(buffer, BUFFER_ERROR_SIZE);
    sprintf(buffer, ERROR_INVALID_ARGUMENT, str);
    return (display_error(buffer));
}

static char *move_till_next_delim(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == ARGUMENT_DELIM)
        i++;
    return (str + i);
}

static bool add_argument_to_lemipc(size_t index)
{
    _g_lemipc.options[index] = true;
    return (true);
}

static bool check_argument(const char *str)
{
    const char *arguments[7] = ARGUMENTS_LIST;
    const size_t arguments_len[ARGUMENTS_SIZE] = ARGUMENTS_LEN;

    for (size_t i = 0; i < ARGUMENTS_SIZE; i++)
    {
        if (ft_strncmp(str, arguments[i], arguments_len[i]) == 0)
        {
            if (i == ARG_PTS || i == ARG_TTS)
            {
                int value = 0;
                if ((sscanf(str, arguments[i], &value)) == 0)
                    return (false);
                if ((i == ARG_PTS && (value < 4 || value > GAME_MAX_PLAYER - 1)) ||
                    (i == ARG_TTS && (value < 2 || value > GAME_MAX_TEAM)))
                    return (false);
                else
                {
                    if (i == ARG_PTS)
                        _g_lemipc.pts = value;
                    else if (i == ARG_TTS)
                        _g_lemipc.tts = value;
                    return (add_argument_to_lemipc(i));
                }
            }
            else if (ft_strlen(str) <= arguments_len[i])
                return (add_argument_to_lemipc(i));
        }
    }
    return (false);
}

/*******************************************************************************
 *                                   CHECKER                                   *
 ******************************************************************************/

bool check_arguments(size_t argc, char **argv)
{
    if (check_team(argv[1]) == false)
        return (display_error(ERROR_INVALID_TEAM));
    for (size_t i = 2; i < argc; i++)
    {
        if (ft_strlen(argv[i]) >= BUFFER_ERROR_SIZE)
            return (display_error(ERROR_INVALID_ARGUMENT_LENGTH));
        if (argv[i][0] == ARGUMENT_DELIM)
        {
            if ((check_argument(move_till_next_delim(argv[i]))) == false)
                return (return_error_buffer(argv[i]));
        }
        else
            return (return_error_buffer(argv[i]));
    }
    return (true);
}