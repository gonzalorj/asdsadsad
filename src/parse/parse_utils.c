/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:14:00 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:14:00 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

size_t	c3d_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	safe_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
	{
		write(2, "Error: NULL pointer.\n",
			sizeof("Error: NULL pointer.\n") - 1);
		if (!s1 && !s2)
			parser_error(NULL, NULL, "Both s1 and s2 are NULL.");
		else if (!s1)
			parser_error(NULL, NULL, "s1 is NULL in safe_strncmp.");
		else if (!s2)
			parser_error(NULL, NULL, "s2 is NULL in safe_strncmp.");
	}
	return (strncmp(s1, s2, n));
}

char	*c3d_trim_spaces(const char *s)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trim;

	start = 0;
	while (s[start] && c3d_isspace(s[start]))
		start++;
	end = c3d_strlen(s);
	while (end > start && c3d_isspace(s[end - 1]))
		end--;
	trim = malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (NULL);
	i = 0;
	while (start < end)
		trim[i++] = s[start++];
	trim[i] = '\0';
	return (trim);
}
