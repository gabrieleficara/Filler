/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:03:26 by gficara           #+#    #+#             */
/*   Updated: 2018/02/21 17:54:51 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				foundstar(t_data data, int coor[2], int start[2], int star)
{
	if (data.piece[coor[0]][coor[1]] == '*')
	{
		if (start[0] + coor[0] < 0 || start[1] + coor[1] < 0 ||
				start[0] + coor[0] >= data.size_b[0] ||
				start[1] + coor[1] >= data.size_b[1])
			return (-1);
		if (data.board[start[0] + coor[0]][start[1] + coor[1]] ==
				data.player[0] || data.board[start[0] +
				coor[0]][start[1] + coor[1]] == data.player[0]
				- 32)
			star++;
		if (data.board[start[0] + coor[0]][start[1] + coor[1]] ==
				data.player[1] || data.board[start[0] +
				coor[0]][start[1] + coor[1]] == data.player[1]
				- 32 || star > 1)
			return (-1);
	}
	return (star);
}

int				caniput(int start[2], t_data data)
{
	int		coor[2];
	int		star;
	int		value;

	value = 1;
	coor[0] = 0;
	coor[1] = 0;
	star = 0;
	while (coor[0] < data.size_p[0])
	{
		while (coor[1] < data.size_p[1])
		{
			if ((star = foundstar(data, coor, start, star)) == -1)
				return (0);
			if (data.piece[coor[0]][coor[1]] == '*')
				value += data.heatmap[start[0] + coor[0]][start[1] + coor[1]];
			coor[1]++;
		}
		coor[1] = 0;
		coor[0]++;
	}
	return ((star == 1) ? value : 0);
}

void			defboard(int *coor, t_data *data, int usage)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	if (usage == 1)
	{
		data->board = (char **)malloc(sizeof(char *) * coor[0]);
		while (i < coor[0])
		{
			get_next_line(data->fd, &new);
			data->board[i++] = ft_strdup(new + 4);
			ft_strdel(&new);
		}
		return ;
	}
	data->heatmap = (int **)malloc(sizeof(int *) * coor[0]);
	while (i < coor[0])
	{
		data->heatmap[i] = (int *)malloc(sizeof(int) * coor[1]);
		j = 0;
		while (j < coor[1])
			data->heatmap[i][j++] = 0;
		i++;
	}
}

char			**defpiece(int *coor, t_data data)
{
	int		i;
	char	**piece;

	i = 0;
	piece = (char **)malloc(sizeof(char *) * coor[0]);
	while (i < coor[0])
		get_next_line(data.fd, piece + (i++));
	return (piece);
}

void			placeit(t_data data)
{
	int		coor[2];
	int		value;

	value = 0;
	data.re_value = 0;
	coor[0] = -data.size_p[0];
	coor[1] = -data.size_p[1];
	data.result[0] = 1 - data.size_p[0];
	data.result[1] = 1 - data.size_p[1];
	while (++coor[0] < data.size_b[0])
	{
		while (++coor[1] < data.size_b[1])
			if ((value = caniput(coor, data)) > data.re_value)
			{
				data.re_value = value;
				data.result[0] = coor[0];
				data.result[1] = coor[1];
			}
		coor[1] = data.size_p[1] * -1;
	}
	ft_printf("%d %d\n", data.result[0], data.result[1]);
}
