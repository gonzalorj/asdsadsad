/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42campus>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:15:45 by gorodrig          #+#    #+#             */
/*   Updated: 2024/03/13 14:15:47 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*copy;

	i = 0;
	copy = (unsigned char *)str;
	while (i < n)
	{
		copy[i] = (unsigned char)c;
		i++;
	}
	return (copy);
}
