# include "cub3d.h"

/*
** IS_EMPTY_LINE:
** - PROPÓSITO: determina si una línea contiene solo espacios (según c3d_isspace).
** - LÓGICA: itera sobre caracteres; si encuentra uno que NO sea espacio, retorna 0;
**   si llega al final, retorna 1.
** - NOTA: filtro previo para separar líneas de identificadores del bloque mapa.
*/
int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
//DEBERIA PROTEGER line = NULL¿?
	while (line[i])
	{
		if (!c3d_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

//LA BUENA, o mejor
// int	is_map_line(char *line)
// {
// 	int	i;
// 	int	has_map_char;

// 	i = 0;
// 	has_map_char = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
// 			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
// 			has_map_char = 1;
// 		else if (line[i] != ' ')
// 			return (0);
// 		i++;
// 	}
// 	return (has_map_char);
// }

/*
** IS_MAP_LINE:
** - PROPÓSITO: valida si una línea pertenece al bloque del mapa.
** - LÓGICA: comprueba que todos los caracteres sean válidos: '0', '1',
**   'N', 'S', 'E', 'W', o espacios literales ' ' (no isspace global).
** - NOTA: válidos según subject; cualquier otro carácter invalida la línea.
*/
static int	is_map_line(char *line)
{
	int	i;

	i = 0;
// En el mapa solo son válidos los espacios literales ' ', no todos los caracteres de isspace(). 
	while (line[i] == ' ')
		i++;
// Las líneas vacías o formadas solo por espacios se filtran antes de llamar a esta función; en cub3d_isspace().
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W' || line[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

/*
** PARSE_IDENTIFY_LINE:
** - PROPÓSITO: detecta y delega el procesamiento de líneas de identificador.
** - LÓGICA: comprueba si la línea es una textura (NO/SO/WE/EA) o color (F/C),
**   y la envía a su función de parseo especializada.
** - ERRORES QUE CONTROLA:
**   [1] línea no coincide con identificadores válidos (textura ni color)
*/
static void	parse_identify_line(t_scene *scene,char *line)
{
//TEXTURES
	if (safe_strncmp(line, "NO", 2) == 0 && c3d_isspace(line[2]))
		parse_texture_line(scene, scene->map.no_txtr, "NO");
	else if (safe_strncmp(line, "SO", 2) == 0 && c3d_isspace(line[2]))
		parse_texture_line(scene, scene->map.so_txtr, "SO");
	else if (safe_strncmp(line, "WE", 2) == 0 && c3d_isspace(line[2]))
		parse_texture_line(scene, scene->map.we_txtr, "WE");
	else if (safe_strncmp(line, "EA", 2) == 0 && c3d_isspace(line[2]))
		parse_texture_line(scene, scene->map.ea_txtr, "EA");
//COLORS	
	else if (line[0] == 'F' && c3d_isspace(line[1]))
		scene->map.f_color = parse_colour_line(scene, line, &scene->map.f_color);
	else if (line[0] == 'C' && c3d_isspace(line[1]))
		scene->map.c_color = parse_colour_line(scene, line, &scene->map.c_color);
	else
	{
		free(line);
		parser_error(scene, NULL,  "Invalid line");
	}
}

/*
** ARE_ALL_ELEMENTS_PRESENT:
** - PROPÓSITO: valida que todos los elementos requeridos del archivo .cub estén definidos.
** - LÓGICA: comprueba presencia del mapa (map_start >= 0), las 4 texturas,
**   y los 2 colores (floor y ceiling).
** - ERRORES QUE CONTROLA:
**   [1] no se encontró sección de mapa
**   [2] falta alguna textura (NO, SO, WE, EA)
**   [3] falta color de piso o techo
*/
static void	are_all_elements_present(t_scene *scene, char **lines, int *map_start)
{
	if (*map_start < 0)
		/* [1] */
		parser_error(scene, lines, "Map missing");
	if (!scene->tex.north || !scene->tex.south || !scene->tex.west || !scene->tex.east)
		/* [2] */
		parser_error(scene, lines, "One or more texture paths are missing");
	if (!scene->floor.is_set || !scene->ceiling.is_set)
		/* [3] */
		parser_error(scene, lines, "Floor or ceiling colour is missing");
}

/*
** PARSE_DIVIDE_CUB_LINES:
** - PROPÓSITO: divide el contenido del archivo .cub en secciones de identificadores y mapa.
** - LÓGICA: itera sobre líneas, salta líneas vacías, detecta el inicio del mapa,
**   procesa identificadores hasta encontrar la primera línea de mapa, y verifica
**   que todos los elementos requeridos estén presentes.
** - ERRORES QUE CONTROLA:
**   [1] falta mapa, texturas o colores (delegado a are_all_elements_present)
*/
void	parse_divide_cub_lines(t_scene *scene, char *line, int *start, int *end)
{
	if(is_empty_line(line))
	{
		if(*start && !(*end))
			*end = 1;
		return ;
	}
	if(*end)
	{
		free(line);
		parser_error(scene, NULL, "Lines after map");
	}
	if(!(*end) && is_map_line(line))
		parse_identify_line(line, scene);
	else if(is_map_line(line))
	{
		*start = 1;
		append_node(scene, line, &scene->map.list);
	}
	else
	{
		free(line);
		parser_error(scene, NULL, "Invalid line");
	}
}