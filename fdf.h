/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:12:04 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 21:20:17 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./full_libft/full_libft.h"
# include <math.h> //math fts like sin cos
# include "./mlx_linux/mlx.h" //minilibx for graphics rendering
# include <X11/keysym.h> //defines some keycodes, only needed on linux?
//for event macros like KeyPress 
//https://codebrowser.dev/kde/include/X11/X.h.html
//#include <X.h>
# include <fcntl.h>

# define WIDTH 1280
# define HEIGHT 720
# define MAX_HEIGHT 50 //for setting top color 

typedef struct s_schleife
{
	int	i;
	int	x;
	int	y;
	int	fehler;
}	t_schleife;

typedef struct s_bresen
{
	int	dx;
	int	dy;
	int	richtung_x;
	int	richtung_y;
}	t_bresen;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_coord
{
	int				x;
	int				y;
	int				height;
	struct s_coord	*next;
}	t_coord;

typedef struct s_crazy
{
	int		x;
	int		y;
	char	**split;
	t_list	*tmp;
	t_coord	*node;
}	t_crazy;

typedef struct s_line
{
	int	parallel_x;
	int	parallel_y;
	int	diagonal_x;
	int	diagonal_y;
	int	delta_slow;
	int	delta_fast;
}	t_line;

typedef struct s_fdf
{
	void	*mlx;
	t_data	*image;
	void	*window;
	t_coord	**map;
	int		size_x;
	int		size_y;
	int		highest_height;
	int		tile_size;
	int		color;
	int		max_color;
	int		off_x;
	int		off_y;
	int		buf_bottom;
	int		buf_left;
	int		buf_right;
}	t_fdf;

//color.c
int		create_color(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

//extra_color.c
int		add_shade(double distance, int color);
int		get_opposite(int color);

//gradient.c
float	function(int x, int y, t_coord *before_pix, t_coord *current_pix);
float	fraction(float x1, float x2, float x);
int		get_pix_color(t_coord *before_pix, t_coord *current_pix, int x, int y);
int		get_point_color(t_coord *point, t_fdf *big);

//hooks
int		quit_window(t_fdf *big);
int		destroy_esc(int keycode, t_fdf *big);

//parse_map.c
void	parse_map(t_fdf *big, char *argv[]);

//create_image.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_stuff(t_fdf *big);

//draw lines.c
void	draw_lines(t_fdf *big, t_coord *current,
			t_coord	*one_before, t_coord *up_pix);
t_coord	*get_pix_coord(t_fdf *big, t_coord *point);

//utils.c
int		count_x(t_list	*map);
t_coord	*getlastcoord(t_coord **coords);
void	add_to_list(t_coord **coords, t_coord *list);
int		calc_tilesize(t_fdf *big);
int		count(char *s);
t_coord	**create_coord_list_ptrs(t_fdf *big);

//bresenham_extra.c
void	x_fast(t_bresen *pack, t_line *initializing);
void	y_fast(t_bresen *pack, t_line *initializing);
int		get_direction(int delta);
void	actually_draw(t_fdf *big, t_schleife *s,
			t_coord *before_pix, t_coord *current_pix);
t_line	*get_line_data_needed(t_bresen *bresen);

//free.c
void	free_image(t_data *image);
void	free_map(t_coord **map, int size);
void	free_coord_list(t_coord *nodes);
void	free_big(t_fdf *big);
void	free_everything(t_fdf *big);

//free-extra
void	free_list(t_list *list);
void	free_split(char **split);
void	free_pix(t_coord *current_pix, t_coord *before_pix);
void	free_create_list(t_fdf *big, char *trimmed, t_list *list);
void	free_fill_coords(t_fdf *big, t_list *list, t_coord **coords, int x);

#endif