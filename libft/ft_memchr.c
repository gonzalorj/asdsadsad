/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42campus>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:59:59 by gorodrig          #+#    #+#             */
/*   Updated: 2024/03/20 12:04:47 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*string;
	unsigned char	let;

	i = 0;
	string = (unsigned char *)str;
	let = (unsigned char)c;
	while (i < n)
	{
		if (string[i] == let)
			return (string + i);
		i++;
	}
	return (NULL);
}
