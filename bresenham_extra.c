/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:59:37 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 18:00:20 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_fast(t_bresen *pack, t_line *initializing)
{
	initializing->parallel_x = pack->richtung_x;
	initializing->diagonal_x = pack->richtung_x;
	initializing->parallel_y = 0;
	initializing->diagonal_y = pack->richtung_y;
	initializing->delta_slow = pack->dy;
	initializing->delta_fast = pack->dx;
}

void	y_fast(t_bresen *pack, t_line *initializing)
{
	initializing->parallel_x = 0;
	initializing->diagonal_x = pack->richtung_x;
	initializing->parallel_y = pack->richtung_y;
	initializing->diagonal_y = pack->richtung_y;
	initializing->delta_slow = pack->dx;
	initializing->delta_fast = pack->dy;
}

int	get_direction(int delta) //bestimme in welche richtung auf achse gehen muss
{
	if (delta < 0)
		return (-1);
	if (delta > 0)
		return (1);
	return (0);
}

void	actually_draw(t_fdf *big, t_schleife *s,
		t_coord *before_pix, t_coord *current_pix)
{
	int	color;

	color = get_pix_color(before_pix, current_pix, s->x, s->y);
	if (s->x < HEIGHT && s->x > 0 && s->y < WIDTH && s->y > 0)
		my_mlx_pixel_put(big->image, s->x, s->y, color);
}

t_line	*get_line_data_needed(t_bresen *bresen)
{
	t_line	*initializing;

	initializing = (t_line *)malloc(sizeof(t_line));
	if (!initializing)
	{
		ft_printf("error malloc initializing\n");
		return (NULL);
	}
	if (bresen->dx > bresen->dy)
		x_fast(bresen, initializing);
	else
		y_fast(bresen, initializing);
	return (initializing);
}
