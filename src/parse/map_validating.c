#include "../../include/cub3d.h"

static bool check_char(char *s)
{
	char *valid;
	int i;

	valid = "NWES 01";
	i = 0;
	while(s[i])
	{
		if(!ft_strchr(valid, s[i]))
			return (1);
		i++;
	}
	return (0);
}

static int count_player(char *s)
{
	char *valid;
	int 	i;
	int 	n;

	valid = "NWES";
	i = 0;
	n = 0;
	while (s[i])
	{
		if(ft_strchr(valid, s[i]))
			n++;
		i++;
	}
	return (n);
}

void check_map_lines(t_scene *scene, t_node *head)
{
	t_node *curr;
	int		n;

	if(!head)
		parser_error(scene, NULL, "Missing node.");
	n = 0;
	curr = head;
	while(curr)
	{
		if(check_char(curr->line))
			parser_error(scene, NULL, "Invalid characters.");
		n += count_player(curr->line);
		curr = curr->next;
	}
	if(n != 1)
		parser_error(scene, NULL, "Only 1 player allowed.");
}

static void check_map_enclosure(int y, int x, t_scene *scene)
{
	int	u;
	int	d;
	int	l;
	int	r;

	if (y == 0 || y >= scene->map.height - 1 || x == 0 || x >= scene->map.width - 1)
	{
		if (ft_strchr("NSWE", scene->map.matrix[y][x]))
			parser_error(scene,NULL, "Invalid map.");
		else if (scene->map.matrix[y][x] == '0')
			parser_error(scene,NULL, "Invalid map");
		
	}
	u = scene->map.matrix[y - 1][x];
	d = scene->map.matrix[y + 1][x];
	l = scene->map.matrix[y][x - 1];
	r = scene->map.matrix[y][x + 1];
	if (u == ' ' || d == ' ' || l == ' ' || r == ' ')
		parser_error(scene,NULL, "Map isnt fully surrounded by walls.");
}

void check_surroundings(t_scene *scene)
{
	int y;
	int x;
	char cell;

	y = 0;
	while(y < scene->map.height)
	{
		x = 0;
		while(x < scene->map.width)
		{
			cell = scene->map.matrix[y][x];
			if(ft_strchr("0NSEW", cell))
				check_map_enclosure(y, x, scene);
			x++;
		}
		y++;
	}
}