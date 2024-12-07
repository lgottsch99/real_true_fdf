/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:39:37 by lgottsch          #+#    #+#             */
/*   Updated: 2024/12/07 18:10:56 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	quit_window(t_fdf *big)
{
	ft_printf("x window\n");
	free_everything(big);
	exit (0);
}

//int is passed by internal event handler
int	destroy_esc(int keycode, t_fdf *big)
{
	ft_printf("esc window\n");
	if (keycode == XK_Escape)
		free_everything(big);
	exit(0);
}
