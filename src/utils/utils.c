/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:27:38 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:34:44 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_nodes(t_node *head)
{
	t_node	*current;
	t_node	*tmp;

	current = head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->line);
		free(tmp);
	}
}

void	free_map(t_map *map)
{
	free_split(map->matrix);
	free(map->no_txtr);
	free(map->so_txtr);
	free(map->we_txtr);
	free(map->ea_txtr);
	if (map->list)
	{
		free_nodes(map->list);
		map->list = NULL;
	}
}

static int	exit_helper(t_scene *scene, int code)
{
	if (!scene)
		exit(code);
	free_map(&scene->map);
	free_textures(scene);
	if (scene->image.img)
		mlx_destroy_image(scene->mlx, scene->image.img);
	if (scene->wdw)
		mlx_destroy_window(scene->mlx, scene->wdw);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	exit(code);
}

int	exit_event(t_scene *scene)
{
	exit_helper(scene, EXIT_SUCCESS);
	return (0);
}
