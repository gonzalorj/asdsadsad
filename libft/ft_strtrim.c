/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42campus>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:37:11 by gorodrig          #+#    #+#             */
/*   Updated: 2024/03/21 16:21:55 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str1, const char *set)
{
	size_t	end_size;
	size_t	start_size;

	start_size = 0;
	if (!str1 || !set)
		return (NULL);
	while (ft_strchr((char *)set, str1[start_size]) && str1[start_size])
		start_size++;
	end_size = ft_strlen(str1);
	while (end_size != 0 && ft_strchr((char *)set, str1[end_size - 1]))
		end_size--;
	if (start_size >= end_size)
		return (ft_substr("", 0, 0));
	return (ft_substr(str1, start_size, end_size - start_size));
}
