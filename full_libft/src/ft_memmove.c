/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:08:16 by lgottsch          #+#    #+#             */
/*   Updated: 2024/11/28 17:31:10 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../full_libft.h"

/*
The  memmove()  function  copies n bytes from memory area src to memory
       area dest.  The memory areas may overlap: copying takes place as though
       the  bytes in src are first copied into a temporary array that does not
       overlap src or dest, and the bytes are then copied from  the  temporary
       array to dest.
*/

static void	ft_backward(unsigned char *temp_d, unsigned char *temp_s, size_t n)
{
	while (n > 0)
	{
		temp_d[n - 1] = temp_s[n - 1];
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*temp_d;
	unsigned char	*temp_s;

	temp_d = (unsigned char *)dest;
	temp_s = (unsigned char *)src;
	i = 0;
	if ((temp_d == temp_s) || n == 0)
		return (dest);
	if (temp_d < temp_s)
	{
		while (i < n)
		{
			temp_d[i] = temp_s[i];
			i++;
		}
	}
	else if (temp_s < temp_d)
	{
		ft_backward(temp_d, temp_s, n);
	}
	return (dest);
}
