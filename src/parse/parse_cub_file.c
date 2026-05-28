# include "cub3d.h"

/*
** count_lines:
** Primera pasada sobre el archivo.
** Cuenta cuántas líneas lógicas devuelve get_next_line().
**
** Idea importante:
** - get_next_line() devuelve una línea completa o NULL.
** - una línea vacía del fichero NO es NULL; normalmente es "\n".
** - NULL significa EOF o error de lectura.
**
** Por eso aquí contamos líneas reales del .cub, no "trozos" de lectura.
**
** También es importante liberar cada 'line':
** - get_next_line() reserva memoria dinámica
** - si no la liberas aquí, tendrás una fuga por cada línea leída
**
** Al terminar, el fd queda al final del fichero (EOF).
** Por eso luego habrá que cerrar y reabrir, o hacer lseek().
*/
static int	count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

/*
** strdup_without_newline:
** Duplica una línea quitando el '\n' final si existe.
**
** Ejemplos:
** - "NO ./a.xpm\n" -> "NO ./a.xpm"
** - "\n"           -> ""
** - "111111"       -> "111111"
**
** Observación:
** - aquí usar strlen(line) es válido porque esta función solo se llama
**   desde fill_lines_array() dentro de un while(line), así que line != NULL.
** - si se reutilizara desde otro sitio sin esa garantía, entonces sí habría riesgo.
**
** Detalle de memoria:
** - reservamos len_line + 1 para poder terminar la nueva string en '\0'
** - el '\0' NO lo pone malloc; lo ponemos nosotros
*/
static char	*strdup_without_newline(const char *line)
{
	size_t	len_line;
	char	*clean_line;
	size_t	i;

	len_line = strlen(line);
	if (len_line > 0 && line[len_line - 1] == '\n')
		len_line--;
	clean_line = malloc(sizeof(char) * (len_line + 1));
	if (!clean_line)
		return (NULL);
	i = 0;
	while (i < len_line)
	{
		clean_line[i] = line[i];
		i++;
	}
	clean_line[i] = '\0';
	return (clean_line);
}

/*
** fill_lines_array:
** Segunda pasada sobre el fichero.
** Ahora sí guardamos cada línea del .cub en el array 'lines'.
**
** 'lines' es, en la práctica, una copia en memoria del archivo:
** - cada lines[i] es una línea sin '\n'
** - el array termina en NULL
**
** Ejemplo:
** lines[0] = "NO ./north.xpm"
** lines[1] = "F 220,100,0"
** lines[2] = "1111"
** ...
** lines[last] = NULL
**
** Importante:
** - primero duplicamos la línea
** - luego liberamos la línea original de get_next_line
**
** Si strdup_without_newline() falla:
** - lines[i] queda en NULL
** - parser_error(NULL, lines, ...) puede liberar con free_lines(lines)
** - esto es seguro si 'lines' se creó inicializado a NULL
**   (por eso ft_calloc es mejor que malloc simple aquí)
*/
static void	fill_lines_array(int fd, char **lines)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines[i] = strdup_without_newline(line);
		free(line);
		if (!lines[i])
			parser_error(NULL, lines,
				"Malloc failed while storing .cub file lines");
		i++;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
}

/*
** read_cub_lines:
** Carga el .cub completo en memoria como char **.
**
** Flujo:
** 1. open() del fichero
** 2. primera pasada: contar líneas
** 3. close()
** 4. reservar array de punteros
** 5. segundo open()
** 6. segunda pasada: rellenar el array
** 7. close()
** 8. devolver lines
**
** ¿Por qué dos pasadas?
** Porque queremos saber cuántas líneas hay antes de reservar el array exacto.
** Alternativa: reallocs sucesivos. Aquí se ha elegido simplicidad.
**
** ¿Por qué cerrar tras count_lines()?
** Porque ese fd ya quedó en EOF.
** Si lo reutilizaras sin reposicionarlo, no leerías nada en la segunda pasada.
**
** ¿Por qué ft_calloc en vez de malloc?
** Porque así todos los punteros arrancan en NULL.
** Eso hace seguro llamar a parser_error(NULL, lines, ...) incluso si falla
** el segundo open() antes de haber llenado el array.
**
** Nota de proyecto:
** - usar calloc() directa no encaja con la lista de funciones externas permitidas,
**   pero libft sí está autorizada, así que ft_calloc propia sí tiene sentido. 
*/
char	**read_cub_lines(const char *filename)
{
	int		fd;
	int		line_count;
	char	**lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parser_error(NULL, NULL, "Could not open .cub file");

	line_count = count_lines(fd);
	close(fd);

	if (line_count == 0)
		parser_error(NULL, NULL, ".cub file is empty");

	/*
	** Con malloc simple habría que inicializar todo el array a NULL a mano
	** antes de poder pasarlo con seguridad a free_lines() en rutas de error.
	*/
	lines = ft_calloc(line_count + 1, sizeof(char *));
	if (!lines)
		parser_error(NULL, NULL, "ft_calloc for lines array has failed");

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		/*
		** Aquí pasar 'lines' a parser_error ya es seguro porque ft_calloc lo dejó
		** completamente inicializado a NULL.
		*/
		parser_error(NULL, lines, "Could not reopen .cub file");
	}

	fill_lines_array(fd, lines);
	close(fd);
	return (lines);
}