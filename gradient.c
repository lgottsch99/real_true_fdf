/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:55:28 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 18:09:04 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	fraction(float x1, float x2, float x)
{
	if (x1 != x2)
		return ((x - x1) / (x2 - x1));
	return (0);
}

float	function(int x, int y, t_coord *before_pix, t_coord *current_pix)
{
	int		dx;
	int		dy;
	float	fraction_value;

	dx = current_pix->x - before_pix->x;
	dy = current_pix->y - before_pix->y;
	if (abs(dx) > abs(dy))
		fraction_value = fraction(before_pix->x, current_pix->x, x);
	else
		fraction_value = fraction(before_pix->y, current_pix->y, y);
	return (fraction_value);
}

//color value stored in ->height
int	get_pix_color(t_coord *before_pix, t_coord *current_pix, int x, int y)
{
	t_rgb	before;
	t_rgb	current;
	int		new_r;
	int		new_g;
	int		new_b;

	before.r = get_r(before_pix->height);
	before.g = get_g(before_pix->height);
	before.b = get_b(before_pix->height);
	current.r = get_r(current_pix->height);
	current.g = get_g(current_pix->height);
	current.b = get_b(current_pix->height);
	new_r = before.r + (current.r - before.r)
		* function(x, y, before_pix, current_pix);
	new_g = before.g + (current.g - before.g)
		* function(x, y, before_pix, current_pix);
	new_b = before.b + (current.b - before.b)
		* function(x, y, before_pix, current_pix);
	return (create_color(0, new_r, new_g, new_b));
}

int	get_point_color(t_coord *point, t_fdf *big)
{
	int	distance;
	int	r;
	int	g;
	int	b;

	if (point->height < 0)
		distance = MAX_HEIGHT + abs(point->height);
	else
		distance = MAX_HEIGHT - point->height;
	r = get_r(big->max_color) - (2 * (255 / 100) * distance);
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	g = get_g(big->max_color) - (2 * (255 / 100) * distance);
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	b = get_b(big->max_color) + (2 * (255 / 100) * distance);
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	return (create_color(0, r, g, b));
}
