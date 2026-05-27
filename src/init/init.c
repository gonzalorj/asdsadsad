# include "cub3d.h"

/*
** init_scene:
** Inicializa toda la estructura de la escena con valores seguros antes de
** empezar el parseo del fichero .cub.
*/
void	init_scene(t_scene *scene)
{
	scene->tex.north = NULL;
	scene->tex.south = NULL;
	scene->tex.west = NULL;
	scene->tex.east = NULL;
	scene->floor = (t_rgb){0, 0, 0, 0};
	scene->ceiling = (t_rgb){0, 0, 0, 0};
	scene->map.grid = NULL;
	scene->map.width = 0;
	scene->map.height = 0;
	scene->player = (t_player){-1, -1, 0};
}