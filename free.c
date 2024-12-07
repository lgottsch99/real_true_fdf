/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:25:50 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 18:05:40 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_image(t_data *image)
{
	if (image->img)
		free(image->img);
	if (image->addr)
		free(image->addr);
}

void	free_coord_list(t_coord *nodes)
{
	t_coord	*tmp;

	while (nodes)
	{
		tmp = nodes;
		nodes = nodes->next;
		free(tmp);
	}
}

void	free_map(t_coord **map, int size)
{
	int		i;
	t_coord	*tmp;

	i = 0;
	while (i < size)
	{
		tmp = map[i];
		free_coord_list(tmp);
		i++;
	}
}

void	free_big(t_fdf *big)
{
	if (big->image && big->mlx && big->image->img)
	{
		ft_printf("freeing image\n");
		mlx_destroy_image(big->mlx, big->image->img);
		free(big->image);
	}
	if (big->window && big->mlx)
	{
		ft_printf("freeing window\n");
		mlx_destroy_window(big->mlx, big->window);
	}
	if (big->map)
	{
		ft_printf("freeing map\n");
		free_map(big->map, big->size_x);
		free(big->map);
	}
	if (big->mlx)
	{
		ft_printf("freeing mlx\n");
		mlx_destroy_display(big->mlx);
		free(big->mlx);
	}
}

void	free_everything(t_fdf *big)
{
	if (big)
		free_big(big);
	exit(1);
}
