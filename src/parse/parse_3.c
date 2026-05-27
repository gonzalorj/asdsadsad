#include "../include/cub3d.h"

void append_node(t_scene *scene, char *line, t_node **head)
{
	t_node *current;
	t_node *new;

	new = malloc(sizeof(t_node));
	if(!new)
		parser_error(scene, NULL, "Malloc fail");
	new->line = ft_strdup(line);
	new->next = NULL;
	if(!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while(current->next)
		current = current->next;
	current->next = new;
}
