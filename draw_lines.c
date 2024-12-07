/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:01:28 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 21:16:36 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	schleife(t_fdf *big, t_line *initializing,
			t_coord *before_pix, t_coord *current_pix);

//(M_PI / 60 -> math.h benutzt bogenmass um an gradzahl zu kommen
t_coord	*get_pix_coord(t_fdf *big, t_coord *point)
{
	t_coord	*pix;

	pix = (t_coord *)malloc(sizeof(t_coord));
	if (!pix)
	{
		ft_printf("error malloc pix\n");
		return (NULL);
	}
	pix->x = big->off_x + ((point->x + point->y)
			* (big->tile_size * sin(M_PI / 6))) - point->height;
	pix->y = big->off_y + ((point->x - point->y)
			* (big->tile_size * cos(M_PI / 6)));
	pix->y = 2 * big->off_y - pix->y;
	pix->next = NULL;
	pix->height = get_point_color(point, big);
	return (pix);
}

void	init_bresen(t_bresen *bresen, t_coord *current_pix, t_coord *before_pix)
{
	bresen->dx = current_pix->x - before_pix->x;
	bresen->dy = current_pix->y - before_pix->y;
	bresen->richtung_x = get_direction(bresen->dx);
	bresen->richtung_y = get_direction(bresen->dy);
	if (bresen->dx < 0)
		bresen->dx = -1 * bresen->dx;
	if (bresen->dy < 0)
		bresen->dy = -1 * bresen->dy;
}

void	bresenham(t_fdf *big, t_coord *current, t_coord *point_before)
{
	t_bresen	bresen;
	t_coord		*current_pix;
	t_coord		*before_pix;
	t_line		*initializing;

	current_pix = get_pix_coord(big, current);
	if (!current_pix)
		free_everything(big);
	before_pix = get_pix_coord(big, point_before);
	if (!before_pix)
	{
		free(current_pix);
		free_everything(big);
	}
	init_bresen(&bresen, current_pix, before_pix);
	initializing = get_line_data_needed(&bresen);
	if (!initializing)
	{
		free_pix(current_pix, before_pix);
		free_everything(big);
	}
	schleife(big, initializing, before_pix, current_pix);
	free_pix(current_pix, before_pix);
	free(initializing);
}

void	schleife(t_fdf *big, t_line *initializing,
		t_coord *before_pix, t_coord *current_pix)
{
	t_schleife	s;

	s.x = before_pix->x;
	s.y = before_pix->y;
	s.fehler = initializing->delta_fast / 2;
	s.i = 0;
	while (s.i < initializing->delta_fast)
	{
		s.fehler = s.fehler - initializing->delta_slow;
		if (s.fehler < 0)
		{
			s.fehler = s.fehler + initializing->delta_fast;
			s.x = s.x + initializing->diagonal_x;
			s.y = s.y + initializing->diagonal_y;
		}
		else
		{
			s.x = s.x + initializing->parallel_x;
			s.y = s.y + initializing->parallel_y;
		}
		actually_draw(big, &s, before_pix, current_pix);
		s.i++;
	}
}

void	draw_lines(t_fdf *big, t_coord *current,
		t_coord *one_before, t_coord *up_pix)
{
	if (current->x == 0)
	{
		if (current->y == 0)
			return ;
		else
			bresenham(big, one_before, current);
	}
	else
	{
		if (current->y == 0)
			bresenham(big, up_pix, current);
		else
		{
			bresenham(big, up_pix, current);
			bresenham(big, one_before, current);
		}
	}
}
