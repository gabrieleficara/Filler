/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:14:05 by gficara           #+#    #+#             */
/*   Updated: 2018/02/17 16:29:38 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libftprintf/includes/ft_printf.h"
# include <fcntl.h>

typedef struct		s_data
{
	char			**board;
	int				**heatmap;
	int				size_b[2];
	char			**piece;
	int				size_p[2];
	char			player[2];
	int				fd;
	int				result[2];
	int				re_value;
}					t_data;

char	**defpiece(int coor[2], t_data data);
void	defboard(int coor[2], t_data *data, int usage);
void	placeit(t_data data);
void	modmap(t_data *data, char let);

#endif
