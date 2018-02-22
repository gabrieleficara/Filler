/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:25:27 by gficara           #+#    #+#             */
/*   Updated: 2018/02/21 17:54:55 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	delbp(t_data *data, int usage)
{
	int		i;

	if (usage == 0)
	{
		i = -1;
		while (++i < data->size_b[0])
			ft_strdel(data->board + i);
		free(data->board);
		i = -1;
		while (++i < data->size_p[0])
			ft_strdel(data->piece + i);
		free(data->piece);
		return ;
	}
	i = -1;
	while (++i < data->size_b[0])
		free(data->heatmap[i]);
	free(data->heatmap);
}

int		*getdata(int *yx, char *line)
{
	yx[0] = 0;
	yx[1] = 0;
	while (*line && yx[1] == 0)
	{
		if (*line >= '0' && *(line) <= '9')
		{
			yx[(yx[0] == 0) ? 0 : 1] = ft_atoi(line);
			while (*line >= '0' && *line <= '9' && yx[1] == 0)
				line++;
		}
		else
			line++;
	}
	return (yx);
}

void	putpiece(t_data data, char player)
{
	char		*line;
	static int	first = 0;

	data.player[0] = (player == 1) ? 'o' : 'x';
	data.player[1] = (player == 2) ? 'o' : 'x';
	get_next_line(data.fd, &line);
	if (line)
		ft_strdel(&line);
	defboard(data.size_b, &data, 1);
	if (first++ == 0)
	{
		colre(&data);
		modmap(&data, data.player[1] - 32);
	}
	modmap(&data, data.player[1]);
	get_next_line(data.fd, &line);
	getdata(data.size_p, line);
	if (line)
		ft_strdel(&line);
	data.piece = defpiece(data.size_p, data);
	placeit(data);
	delbp(&data, 0);
}

int		start(t_data data)
{
	int		i;
	char	*name;
	char	*tmp;

	name = NULL;
	tmp = NULL;
	i = 0;
	while (get_next_line(data.fd, &name) > 0)
	{
		if (name[0] == '$' && ft_strstr(name, "gficara") != NULL)
		{
			if ((tmp = ft_strchr(name, 'p')))
			{
				i = tmp[1] - '0';
				ft_strdel(&name);
				return (i);
			}
			else
				ft_strdel(&name);
		}
	}
	return (0);
}

int		main(void)
{
	char	*line;
	t_data	data;
	int		player;

	data.fd = 0;
	player = start(data);
	data.size_b[0] = 0;
	while (get_next_line(data.fd, &line) > 0)
	{
		if (ft_strncmp(line, "Plat", 3) == 0)
		{
			if (data.size_b[0] == 0)
			{
				getdata(data.size_b, line);
				defboard(data.size_b, &data, 0);
			}
			putpiece(data, player);
		}
		if (line)
			ft_strdel(&line);
	}
	if (data.size_b[0] != 0)
		delbp(&data, 1);
	return (0);
}
