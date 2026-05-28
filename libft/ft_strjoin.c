/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42campus>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:54:39 by gorodrig          #+#    #+#             */
/*   Updated: 2024/03/26 14:14:18 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*cap;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	cap = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!cap)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	ft_strlcpy(cap, s1, s1_len + 1);
	ft_strlcpy((cap + s1_len), s2, s2_len + 1);
	return (cap);
}
