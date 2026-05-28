/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:57:36 by gorodrig          #+#    #+#             */
/*   Updated: 2024/03/28 13:11:05 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_str_cnt(const char *s, char c)
{
	int		is_word;
	size_t	str_num;

	str_num = 0;
	is_word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			is_word = 0;
		else if (is_word == 0)
		{
			str_num++;
			is_word = 1;
		}
		s++;
	}
	return (str_num);
}

static int	ft_mem_possible(char **str_array, int pos, size_t mem)
{
	int	i;

	i = 0;
	str_array[pos] = malloc(mem);
	if (!str_array[pos])
	{
		while (i < pos)
		{
			free(str_array[i]);
			i++;
		}
		free(str_array);
		return (1);
	}
	return (0);
}

static int	ft_cpy(char **str_array, const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (ft_mem_possible(str_array, i, len + 1))
				return (1);
			ft_strlcpy(str_array[i], s - len, len + 1);
		}
		i++;
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	size_t	str_num;
	char	**str_array;

	if (!s)
		return (NULL);
	str_num = 0;
	str_num = ft_str_cnt(s, c);
	str_array = malloc((str_num + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	str_array[str_num] = NULL;
	if (ft_cpy(str_array, s, c))
		return (NULL);
	return (str_array);
}
