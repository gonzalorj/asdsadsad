/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:03:39 by gorodrig          #+#    #+#             */
/*   Updated: 2026/06/11 10:04:19 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	get_matrix_size(t_scene *scene)
{
	t_node	*curr;
	int		w;
	int		h;

	curr = scene->map.list;
	w = 0;
	h = 0;
	while (curr && !is_empty_line(curr->line))
	{
		h++;
		if ((int)ft_strlen(curr->line) > w)
			w = ft_strlen(curr->line);
		curr = curr->next;
	}
	scene->map.height = h;
	scene->map.width = w;
}

static void	fill_matrix(t_scene *scene)
{
	t_node	*curr;
	int		i;
	int		len;

	i = 0;
	curr = scene->map.list;
	while (scene->map.height > i && curr)
	{
		scene->map.matrix[i] = malloc((scene->map.width + 1));
		if (!scene->map.matrix[i])
			parser_error(scene, NULL, "Malloc matrix failed.");
		len = ft_strlen(curr->line);
		ft_memset(scene->map.matrix[i], ' ', scene->map.width);
		ft_memcpy(scene->map.matrix[i], curr->line, len);
		scene->map.matrix[i][scene->map.width] = '\0';
		curr = curr->next;
		i++;
	}
}

void	build_matrix(t_scene *scene)
{
	get_matrix_size(scene);
	scene->map.matrix = malloc(sizeof(char *) * (scene->map.height + 1));
	if (!scene->map.matrix)
		parser_error(scene, NULL, "Malloc matrix failed.");
	fill_matrix(scene);
	scene->map.matrix[scene->map.height] = NULL;
}
