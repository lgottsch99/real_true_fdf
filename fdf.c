/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:36:28 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 19:55:15 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_everything(t_fdf *big)
{
	big->mlx = NULL;
	big->image = NULL;
	big->window = NULL;
	big->map = NULL;
	big->size_x = 0;
	big->size_y = 0;
	big->highest_height = 0;
	big->tile_size = 0;
	big->color = 0;
	big->max_color = 0;
	big->off_x = 0.2 * HEIGHT;
	big->off_y = WIDTH / 2;
	big->buf_bottom = HEIGHT - big->off_x;
	big->buf_left = 0.1 * WIDTH;
	big->buf_right = WIDTH - big->buf_left;
}

static void	initialize(t_fdf *big) //initialize x connection, img, window
{
	initialize_everything(big);
	big->mlx = mlx_init();
	if (!big->mlx)
		exit(1);
	big->image = (t_data *)malloc(sizeof(t_data));
	if (!big->image)
	{
		ft_printf("image malloc error\n");
		free_everything(big);
	}
	big->image->img = mlx_new_image(big->mlx, WIDTH, HEIGHT);
	if (!big->image->img)
		free_everything(big);
	big->image->addr = mlx_get_data_addr(big->image->img,
			&big->image->bits_per_pixel,
			&big->image->line_length, &big->image->endian);
	if (!big->image->addr)
		free_everything(big);
	big->window = mlx_new_window(big->mlx, WIDTH, HEIGHT, "FDF");
	if (!big->window)
		free_everything(big);
}

void	hooks(t_fdf *big)
{
	mlx_hook(big->window, 2, 1L << 0, destroy_esc, big);
	mlx_hook(big->window, 17, 1L << 0, quit_window, big);
}

int	check_fdf(char *name)
{
	int	end;

	end = ft_strlen(name);
	if (name[end - 1] == 'f')
	{
		if (name[end - 2] == 'd')
		{
			if (name[end - 3] == 'f')
			{
				if (name[end - 4] == '.')
					return (1);
			}
		}
	}
	ft_printf("input not a .fdf file\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_fdf	big;

	if (argc != 2)
	{
		ft_printf("Usage: ./fdf mapfile.fdf\n");
		return (0);
	}
	if (!check_fdf(argv[1]))
		return (1);
	initialize(&big);
	big.max_color = create_color(0, 255, 255, 0);
	parse_map(&big, argv);
	big.tile_size = calc_tilesize(&big);
	draw_stuff(&big);
	hooks(&big);
	mlx_put_image_to_window(big.mlx, big.window, big.image->img, 0, 0);
	if (big.mlx)
		mlx_loop(big.mlx);
	return (0);
}
