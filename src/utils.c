#include "../include/cub3d.h"


static int exit_helper(t_scene *scene, int code)
{
	if(!scene)
		exit(code);
	free_map(&scene->map);

	
}

int	exit_event(t_scene *scene)
{
	exit_code(scene, EXIT_SUCCESS);
	return (0);
}

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
	free_tab(map->matrix);
	free(map->no_txtr);
	free(map->so_txtr);
	free(map->we_txtr);
	free(map->ea_txtr);
	if (map->list)
	{
		free_tmp_list(map->list);
		map->list = NULL;
	}
}