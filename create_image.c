/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:12:20 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 16:56:11 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * data->line_length + y * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	update(t_coord **current, t_coord **one_before, t_coord **upper)
{
	if (*current)
		*one_before = *current;
	if (*upper && (*upper)->next)
		*upper = (*upper)->next;
	if ((*current)->next)
		*current = (*current)->next;
}

void	draw_stuff(t_fdf *big)
{
	t_coord	*current;
	t_coord	*one_before;
	t_coord	*upper;
	int		x;
	int		y;

	current = big->map[0];
	one_before = NULL;
	upper = NULL;
	x = 0;
	while (x < big->size_x && big->map[x])
	{
		current = big->map[x];
		if (x > 0)
			upper = big->map[x - 1];
		y = 0;
		while (y < big->size_y)
		{
			draw_lines(big, current, one_before, upper);
			update(&current, &one_before, &upper);
			y++;
		}
		x++;
	}
}
