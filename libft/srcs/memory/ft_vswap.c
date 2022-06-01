/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:21:43 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 10:23:33 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_vswap(void **ptr, void **ptr2)
{
    void *tmp = *ptr;

    *ptr = *ptr2;
    *ptr2 = tmp;
}