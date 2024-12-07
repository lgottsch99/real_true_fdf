/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:32:05 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 19:43:44 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	**create_coord_list_ptrs(t_fdf *big);
t_coord	*create_coord(int x, int y, char *str);
void	add_to_list(t_coord **coords, t_coord *list);
void	fill_coords(t_fdf *big, t_list *list, t_coord **coords);

static t_list	*create_list(t_fdf *big, int fd, t_list *list)
{
	char	*trimmed;
	char	*line;
	t_list	*node;

	trimmed = NULL;
	line = NULL;
	node = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trimmed = ft_strtrim(line, "\n");
		free(line);
		line = NULL;
		if (!trimmed)
			free_create_list(big, trimmed, list);
		node = ft_lstnew(trimmed);
		if (!node)
			free_create_list(big, trimmed, list);
		ft_lstadd_back(&list, node);
		node = NULL;
		trimmed = NULL;
	}
	return (list);
}

void	inner_loop(t_crazy *c, t_fdf *big, t_coord **coords, t_list *list)
{
	c->y = 0;
	while (c->y < big->size_y && c->split[c->y])
	{
		c->node = create_coord(c->x, c->y, c->split[c->y]);
		if (!c->node)
		{
			free_split(c->split);
			free_fill_coords(big, list, coords, c->x);
		}
		free(c->split[c->y]);
		add_to_list(&(coords[c->x]), c->node);
		c->node = NULL;
		c->y++;
	}
}

void	fill_coords(t_fdf *big, t_list *list, t_coord **coords)
{
	t_crazy	c;

	c.tmp = list;
	c.x = 0;
	while (c.x < big->size_x)
	{
		c.split = ft_split((char *)c.tmp->content, ' ');
		if (!c.split)
			free_fill_coords(big, list, coords, c.x);
		inner_loop(&c, big, coords, list);
		free(c.split);
		c.split = NULL;
		c.tmp = c.tmp->next;
		c.x++;
	}
}

t_coord	*create_coord(int x, int y, char *str)
{
	t_coord	*coord;

	coord = (t_coord *)malloc(sizeof(t_coord));
	if (!coord)
	{
		ft_printf("error malloc coord node\n");
		return (NULL);
	}
	coord->y = y;
	coord->x = x;
	coord->height = ft_atoi(str);
	coord->next = NULL;
	return (coord);
}

void	parse_map(t_fdf *big, char *argv[]) //read and create map structure
{
	t_list	*list;
	int		fd;

	list = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("error opening map\n");
		free_everything(big);
	}
	list = create_list(big, fd, list);
	big->size_x = ft_lstsize(list);
	big->size_y = count(list->content);
	big->map = create_coord_list_ptrs(big);
	if (!big->map)
	{
		free_list(list);
		free_everything(big);
	}
	fill_coords(big, list, big->map);
	free_list(list);
}
