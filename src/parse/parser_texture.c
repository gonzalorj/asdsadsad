/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:16:56 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:16:56 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture_line(t_scene *scene, char *line, char **path)
{
	char	**splits;

	splits = ft_split(line, ' ');
	if (!splits || !splits[0] || !splits[1] || splits[2])
	{
		free(line);
		parser_error(scene, splits, "Invalid format");
	}
	if (*path)
	{
		free(line);
		parser_error(scene, splits, "Duplicated path");
	}
	*path = ft_strdup(splits[1]);
	if (!(*path))
	{
		free(line);
		parser_error(scene, splits, "Malloc fail");
	}
	free_split(splits);
}
