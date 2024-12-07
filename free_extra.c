/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:15:24 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 19:45:53 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_pix(t_coord *current_pix, t_coord *before_pix)
{
	free(current_pix);
	free(before_pix);
}

void	free_create_list(t_fdf *big, char *trimmed, t_list *list)
{
	if (trimmed)
		free(trimmed);
	if (list)
		free_list(list);
	free_everything(big);
}

void	free_fill_coords(t_fdf *big, t_list *list, t_coord **coords, int x)
{
	free_list(list);
	free_map(coords, x);
	free_everything(big);
}
