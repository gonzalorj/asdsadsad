/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42campus>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:56:52 by gorodrig          #+#    #+#             */
/*   Updated: 2024/03/27 11:14:37 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!str || start >= ft_strlen(str))
		return (ft_strdup(""));
	if (len == 0)
		return (ft_strdup(""));
	if (len > (ft_strlen(str + start)))
		len = ft_strlen(str + start);
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (len-- && *str)
	{
		new[i++] = str[start++];
	}
	new[i] = '\0';
	return (new);
}
