/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 13:26:12 by gficara           #+#    #+#             */
/*   Updated: 2018/02/19 19:20:29 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	modmap(t_data *data, char let)
{
	int		pnt[2];
	int		assval[2];

	pnt[0] = -1;
	pnt[1] = -1;
	while (++pnt[0] < data->size_b[0])
	{
		while (++pnt[1] < data->size_b[1])
			if (let == data->board[pnt[0]][pnt[1]])
			{
				assval[0] = -1;
				assval[1] = -1;
				while (++assval[0] < data->size_b[0])
				{
					while (++assval[1] < data->size_b[1])
						data->heatmap[assval[0]][assval[1]] += (data->size_b[0]
								- ft_abs(pnt[0] - assval[0])) + (data->size_b[1]
									- ft_abs(pnt[1] - assval[1]));
					assval[1] = -1;
				}
			}
		pnt[1] = -1;
	}
}
