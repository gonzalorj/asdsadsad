/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42campus>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:24:36 by gorodrig          #+#    #+#             */
/*   Updated: 2024/03/21 16:04:54 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t n)
{
	size_t			i;
	size_t			p;

	i = 0;
	p = 0;
	if (!*substr)
	{
		return ((char *)str);
	}
	while (str[i] && (i + p) < n)
	{
		if (str[i] == substr[0])
		{
			while (str[i + p] == substr[p] && (i + p) < n)
			{
				if (substr[p + 1] == '\0')
					return ((char *)&str[i]);
				p++;
			}
		}
		i++;
	}
	return (NULL);
}
