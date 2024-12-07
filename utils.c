/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:59:25 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 19:41:57 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//ignore height, subject says maps need to be properly formatted only
int	calc_tilesize(t_fdf *big)
{
	int	tile_size;
	int	fdf_width;
	int	fdf_height;
	int	w;
	int	h;

	fdf_width = 0;
	fdf_height = 0;
	w = 0;
	h = 0;
	tile_size = 1;
	while ((w < big->buf_right) && (h < big->buf_bottom))
	{
		w = big->buf_left + big->size_y * (tile_size * 2);
		h = big->off_x + big->size_x * (tile_size);
		if ((w < big->buf_right) && (h < big->buf_bottom))
		{
			fdf_width = w;
			fdf_height = h;
			tile_size++;
		}
	}
	return (tile_size);
}

int	count(char *s)//count words in s = y elements
{
	int	i;
	int	nr;

	nr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else
		{
			nr++;
			while (s[i] != ' ' && s[i])
				i++;
		}
	}
	return (nr);
}

void	add_to_list(t_coord **coords, t_coord *list)
{
	t_coord	*last;

	if (coords)
	{
		if (*coords)
		{
			last = getlastcoord(coords);
			if (last)
				last->next = list;
		}
		else
			*coords = list;
	}
}

t_coord	*getlastcoord(t_coord **coords)
{
	t_coord	*tmp;

	if (coords && *coords)
	{
		tmp = *coords;
		while (tmp->next)
			tmp = tmp->next;
		return (tmp);
	}
	return (NULL);
}

t_coord	**create_coord_list_ptrs(t_fdf *big)
{
	int		i;
	t_coord	**coord_list;

	coord_list = (t_coord **)malloc(sizeof(t_coord *) * big->size_x);
	if (!coord_list)
	{
		ft_printf("error malloc coord list\n");
		return (NULL);
	}
	i = 0;
	while (i < big->size_x)
	{
		coord_list[i] = NULL;
		i++;
	}
	return (coord_list);
}
