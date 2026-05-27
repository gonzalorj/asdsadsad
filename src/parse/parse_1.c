# include "cub3d.h"
/*
** Comprobaciones del parseo (vinculadas al flujo de parse_cub_file)
**
** check_cub_extension(filename):
**   - extensión válida ".cub"
**   - nombre no vacío / no ambiguo (evitar ".cub.bak", etc.)
**
** scene_init(scene):
**   - inicialización segura de la estructura (NULL, -1…)
**   - evita estados inconsistentes en caso de error
**
** read_file_lines(filename):
**   - el archivo existe
**   - se puede abrir (open OK)
**   - se puede leer completamente
**   - memoria correctamente reservada
**
** map_start = -1:
**   - valor sentinela para detectar ausencia de mapa
**
** parse_identifiers(scene, lines, &map_start):
**   - texturas (NO, SO, WE, EA):
**       · no duplicadas
**       · paths no vacíos y accesibles
**   - colores (F, C):
**       · formato R,G,B correcto
**       · valores en rango [0,255]
**       · sin caracteres extra
**   - todos los identificadores presentes
**   - orden libre correctamente gestionado
**   - líneas vacías permitidas antes del mapa
**   - detección del inicio del mapa (map_start)
**   - prohibidos identificadores después del mapa
**
** extract_map(scene, lines, map_start):
**   - el mapa existe (map_start != -1)
**   - copia correcta del mapa
**   - cálculo de width y height
**   - no líneas vacías dentro del mapa
**   - espacios tratados como parte del mapa
**
** validate_map(scene):
**   - caracteres válidos: 0, 1, N, S, E, W, espacio
**   - exactamente un jugador
**   - mapa cerrado:
**       · ningún 0/N/S/E/W toca espacio o fuera de rango
**   - coherencia estructural general
**
** free_lines(lines):
**   - liberación completa de memoria
**   - sin leaks en ejecución normal
**
** Resumen:
**   archivo válido
**   → identificadores completos y correctos
**   → mapa presente y bien formado
**   → mapa válido y cerrado
**   → sin fugas de memoria
*/

/*
** CHECK_CUB_EXTENSION:
** - PROPÓSITO: valida que el nombre del archivo termine exactamente en ".cub".
** - LÓGICA: comprueba que la longitud sea >= 5 y que los últimos 4 caracteres
**   sean exactamente ".cub" usando safe_strncmp().
** - ERRORES QUE CONTROLA:
**   [1] extensión no es ".cub" o nombre muy corto
*/
static void	check_cub_extension(const char *filename)
{
	size_t	len;

	len = c3d_strlen(filename);
	if (len < 5 || safe_strncmp(filename + (len - 4), ".cub", 4) != 0)
		/* [1] */
		parser_error(NULL, NULL, "Invalid file extension. Expected .cub");
}

char *get_lines(char *filename, t_scene *scene)
{
	char *line;

	scene->map.fd = open(filename, O_RDONLY);
	if (scene->map.fd < 0)
		parser_error(NULL, NULL, "File can't be opened");
	line = get_next_line(scene->map.fd);
	if(!line)
	{
		close(scene->map.fd);
		parser_error(scene, NULL, "File is empty");
	}
	return (line);
}

void trim_nl(char *line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	if (i > 0 && line[i - 1] == '\n')
		line[i - 1] = '\0';
}

static void	check_map_data(t_scene *scene)
{
	if (!scene->map.matrix|| !scene->map.no_txtr || !scene->map.so_txtr
		|| !scene->map.we_txtr || !scene->map.ea_txtr
		|| scene->map.f_color == -1 || scene->map.c_color == -1)
		parser_error(scene,"NULL", "Missing data");
}

void	parse_cub_file(t_scene *scene, char *filename)
{
	char *line;
	int	start;
	int end;
	
	line = get_lines(filename, scene);
	start = 0;
	end = 0;
	while(line)
	{
		trim_nl(line);
		parse_divide_cub_lines(scene, line, &start, &end);
		free(line);
		line = get_next_line(scene->map.fd);
	}
	close(scene->map.fd);
	check_map_lines(scene, scene->map.list);
	build_matrix(scene);
	check_surroundings(scene);
	check_map_data(scene);
	
}