/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42campus>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:15:42 by gorodrig          #+#    #+#             */
/*   Updated: 2024/03/26 14:13:53 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	ch;

	ch = (char )c;
	while (*str)
	{
		if (*str == ch)
			return ((char *) str);
		str++;
	}
	if (ch == '\0')
		return ((char *) str);
	return (NULL);
}
