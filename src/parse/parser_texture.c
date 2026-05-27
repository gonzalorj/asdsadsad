# include "cub3d.h"

/*
** SELECT_TEXTURE_MEMORY:
** - PROPÓSITO: devuelve la dirección de memoria del campo de textura que
**   corresponde al identificador recibido (NO, SO, WE o EA).
** - LÓGICA: compara el identificador con los cuatro tipos válidos y retorna
**   el puntero al campo apropiado, o NULL si no coincide.
** - NOTA: static porque solo se usa dentro de este archivo.
*/
static char	**select_texture_memory(t_scene *scene, char *path)
{
	if (path[0] == 'N' && path[1] == 'O' && path[2] == '\0')
		return (&scene->tex.north);
	if (path[0] == 'S' && path[1] == 'O' && path[2] == '\0')
		return (&scene->tex.south);
	if (path[0] == 'W' && path[1] == 'E' && path[2] == '\0')
		return (&scene->tex.west);
	if (path[0] == 'E' && path[1] == 'A' && path[2] == '\0')
		return (&scene->tex.east);
	return (NULL);
}

/*
** ENSURE_TEXTURE_FILE_EXISTS:
** - PROPÓSITO: valida que el archivo de textura exista y sea accesible.
** - LÓGICA: intenta abrir el archivo en modo lectura; retorna 1 si éxito,
**   0 si falla (file not found o permisos insuficientes).
** - ERRORES QUE CONTROLA:
**   [1] archivo de textura no existe o no es legible
*/
static int	ensure_texture_file_exists(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

/*
** PARSE_TEXTURE_LINE:
** - PROPÓSITO: procesa una línea de textura (NO/SO/WE/EA) desde el archivo .cub.
** - LÓGICA: valida el identificador, comprueba duplicados, extrae la ruta,
**   verifica que el archivo exista, y guarda el path en la escena.
** - ERRORES QUE CONTROLA:
**   [1] identificador no reconocido (distinto a NO, SO, WE, EA)
**   [2] textura ya definida previamente (duplicado)
**   [3] fallo en asignación de memoria (c3d_trim_spaces)
**   [4] ruta de textura vacía o solo espacios
**   [5] archivo de textura no existe o no es accesible
*/
void	parse_texture_line(t_scene *scene, char *line, char **path)
{
	char **splits;

	splits = ft_split(line, ' ');
	if(!splits || !splits[0] || !splits[1] || splits[2])
	{
		free(line);
		parser_error(scene, splits, "Invalid format");
	}
	if(*path)
	{
		free(line);
		parser_error(scene, splits, "Duplicated path");
	}
	*path = ft_strdup(splits[1]);
	if(!(*path))
	{
		free(line);
		parser_error(scene, splits, "Malloc fail");
	}
	free_split(splits);
}