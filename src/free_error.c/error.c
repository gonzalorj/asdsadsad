# include "cub3d.h"

/*
** FREE_TEXTURE_PATHS:
** - PROPÓSITO: libera la memoria de los punteros a rutas de texturas.
** - LÓGICA: libera cada una de las 4 texturas (north, south, west, east)
**   y asigna NULL a cada puntero para evitar use-after-free.
** - NOTA: función auxiliar de liberación; sin errores.
*/
/*static void	free_texture_paths(t_scene *scene)
{
	free(scene->tex.north);
	free(scene->tex.south);
	free(scene->tex.west);
	free(scene->tex.east);
	scene->tex.north = NULL;
	scene->tex.south = NULL;
	scene->tex.west = NULL;
	scene->tex.east = NULL;
}*/

// static void	free_map_data(t_scene *scene)
// {
// 	int	i;

// 	i = 0;
// 	if (!scene->map.grid)
// 		return ;
// 	while (scene->map.grid[i])
// 	{
// 		free(scene->map.grid[i]);
// 		i++;
// 	}
// 	free(scene->map.grid);
// 	scene->map.grid = NULL;
// }

/*
** FREE_SCENE:
** - PROPÓSITO: libera toda la memoria asociada a la estructura escena.
** - LÓGICA: comprueba NULL, llama a free_texture_paths() y comentariza
**   libre del mapa (aun no implementado completamente).
** - NOTA: punto de entrada para liberación de escena en caso de error.
*/


/*
** FREE_LINES:
** - PROPÓSITO: libera el array de líneas leídas del archivo .cub.
** - LÓGICA: itera sobre el array, libera cada cadena, y luego libera el
**   array en sí mismo.
** - NOTA: maneja NULL de forma segura; detiene si lines es NULL.
*/
static void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

/*
** PARSER_ERROR:
** - PROPÓSITO: limpia recursos, muestra mensaje de error y termina el programa.
** - LÓGICA: libera escena (scene) y array de líneas (lines), escribe error
**   a stderr (fd 2), y llama a exit(EXIT_FAILURE).
** - NOTA: punto de salida obligatoria para cualquier error de parsing;
**   no retorna (exit termina el programa).
** - ERRORES DETECTADOS: todos los errores del parser convergen aquí.
*/
void	parser_error(t_scene *scene, char **lines, const char *msg)
{
	exit_event(scene);
	free_lines(lines);
	write(2, "Error: ", 7);
	if (msg)
	{
		write(2, msg, c3d_strlen(msg));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}