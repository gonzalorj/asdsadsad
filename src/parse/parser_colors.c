# include "cub3d.h"

/*
** skip_spaces:
** Propósito: salta caracteres de espacio al inicio de una cadena.
** Lógica: avanza el puntero mientras encuentre espacios según c3d_isspace().
** Retorna: puntero al primer caracter no-espacio.
** Nota: función utilitaria, no genera errores.
*/
static char	*skip_spaces(char *line)
{
	while (*line && c3d_isspace(*line))
		line++;
	return (line);
}

/*
** search_line_for_colours:
** Propósito: extrae y valida un componente RGB (0-255) desde una cadena.
** Lógica: salta espacios, lee dígitos acumulando su valor, comprueba rango,
** y retorna el componente sin consumir el separador (responsabilidad de expect_comma).
**
** Errores que controla:
** [1] no hay dígitos (valor vacío)
** [2] el valor numérico supera 255
** NOTA: no valida la coma posterior; eso lo hace expect_comma().
*/
static char *rgb_syntax(char *trimmed, int rgb)
{
	int i = 0;

	if(rgb < 0 || rgb > 255)
		return("Number must be in between 0-255 range");
	skip_spaces(trimmed[i]);
	if(trimmed[i] == '-' || trimmed[i] == '+')
		return("Invalid format");
	if(!ft_isdigit(trimmed[i]))
		return("Invalid format");
	while(ft_isdigit(trimmed[i]))
		i++;
	skip_spaces(trimmed[i]);
	if(trimmed[i] != '\0')
		return("Invalid format");
	return(NULL);
}

static int parse_rgb(char *trimmed, t_scene *scene, char **splits, char *line)
{
	char *ret;
	int rgb;

	rgb = ft_atoi(trimmed);
	ret = rgb_syntax(trimmed, rgb);
	if(ret != NULL)
	{
		free(line);
		free(trimmed);
		parser_error(scene, splits, ret);
	}
	free(trimmed);
	return (n);
}

/*
** expect_comma:
** Propósito: valida que el siguiente carácter sea una coma (separador RGB).
** Lógica: comprueba el carácter actual, y si es coma, lo consume avanzando el puntero.
**
** Errores que controla:
** [3] el separador no es una coma (formato RGB inválido)
*/
static void	expect_comma(char **line, t_scene *scene, char **lines)
{
	if (**line != ',')
		/* [3] */
		parser_error(scene, lines, "RGB format must be: R,G,B");
	(*line)++; /* CORRECCION: la coma se consume aquí */
}

/*
** load_colour:
** Propósito: guarda un color ya validado (R, G, B) en su destino (piso o techo).
** Lógica: copia los tres componentes y marca el color como asignado (is_set=1).
** Nota: función auxiliar de persistencia, sin validación de errores.
*/
static void	load_colour(t_scene *scene, char *line, char **splits)
{
	int red;
	int green;
	int blue;

	red = parse_rgb(ft_strtrim(splits[0], " \t"), scene, splits, line);
	green = parse_rgb(ft_strtrim(splits[1], " \t"), scene, splits, line);
	blue = parse_rgb(ft_strtrim(splits[2], " \t"), scene, splits, line);
	return ((red << 16) | (green << 8) | blue);
}

/*
** parse_colour_line:
** Propósito: procesa una línea de color (F=piso, C=techo) desde el archivo .cub.
** Lógica: valida el identificador, comprueba que no esté duplicado, y luego
** lee los tres componentes RGB en secuencia, validando formato y rango en cada paso.
** Al final, guarda el color en la escena.
**
** Errores que controla:
** [4] identificador inválido (no es F ni C)
** [5] color (piso o techo) ya fue definido previamente
** [1] falta un componente RGB (delegado a search_line_for_colours)
** [2] componente RGB supera 255 (delegado a search_line_for_colours)
** [3] falta separador coma entre componentes (delegado a expect_comma)
** [6] sobran caracteres tras el último componente
*/
int	parse_colour_line(t_scene *scene,char *line, int *path)
{
	char *s;
	int rgb;
	char **splits;

	if(*path != -1)
	{
		free(line);
		parser_error(scene, NULL, "Duplicated rgb configuration");
	}
	s = line;
	++line;
	splits = ft_split(line, ',');
	if(!splits || !splits[0] || !splits[1] || splits[2] || splits[3])
	{
		free(s);
		parser_error(scene, splits, "3 numbers are needed");
	}
	rgb = load_colour;
	free_split(splits);
	return (rgb);
}



	