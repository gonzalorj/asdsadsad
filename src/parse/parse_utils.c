#include "cub3d.h"


/*
** C3D_ISSPACE:
** - PROPÓSITO: determina si un carácter es un espacio según la definición del parser.
** - LÓGICA: comprueba si el carácter es ' ' (espacio) o está en el rango 9-13
**   (tab, newline, vertical tab, form feed, carriage return).
** - NOTA: usada en todo el parser para normalizar espacios en blanco.
*/
int	c3d_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/*
** C3D_STRLEN:
** - PROPÓSITO: calcula la longitud de una cadena, retornando 0 si la entrada es NULL.
** - LÓGICA: itera hasta encontrar '\0', con protección contra NULL.
** - NOTA: defensiva contra NULL; puede ocultar errores pero estabiliza el parser.
*/
size_t	c3d_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

/*
** STRLEN (estándar C):
** - PROPÓSITO: calcula la longitud de una cadena (estándar ISO C).
** - LÓGICA: itera hasta encontrar '\0'; crash si str es NULL.
** - NOTA: sin protección contra NULL; responsabilidad del llamador.
*/
size_t	strlen(const char* str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
** SAFE_STRNCMP:
** - PROPÓSITO: comparar cadenas de forma defensiva contra NULL pointers.
** - LÓGICA: valida ambas entradas; si alguna es NULL, escribe error stderr
**   y llama a parser_error() con el respectivo mensaje.
** - CONVENCIÓN para NULL (no es libc):
**   [1] ambas NULL         → parser_error()
**   [2] s1 NULL, s2 válido → parser_error()
**   [3] s1 válido, s2 NULL → parser_error()
**   [4] ambas válidas      → retorna strncmp(s1, s2, n)
*/
int	safe_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
	{
		write(2, "Error: safe_strncmp received, at least, one NULL pointer.\n",
			sizeof("Error: safe_strncmp received, at least, one NULL pointer.\n") - 1);
		if (!s1 && !s2)
			parser_error(NULL, NULL, "Both s1 and s2 are NULL in safe_strncmp.");
		else if (!s1)
			parser_error(NULL, NULL, "s1 is NULL in safe_strncmp.");
		else if (!s2)
			parser_error(NULL, NULL, "s2 is NULL in safe_strncmp.");
	}
	return (strncmp(s1, s2, n));
}

/*
** STRNCMP (estándar C):
** - PROPÓSITO: comparar n bytes de dos cadenas (estándar ISO C).
** - LÓGICA: compara carácter por carácter; retorna diferencia si hay mismatch,
**   0 si coinciden exactamente o se alcanza el límite n.
** - NOTA: sin protección contra NULL; crash si s1 o s2 es NULL.
*/
int	strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

// char	*c3d_strdup(const char *s)
// {
// 	size_t	i;
// 	char	*dup;

// 	dup = malloc(sizeof(char) * (c3d_strlen(s) + 1));
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }
/*
** C3D_TRIM_SPACES:
** - PROPÓSITO: elimina espacios en blanco del inicio y final de una cadena.
** - LÓGICA: localiza start (primer no-espacio) y end (posición post-último
**   no-espacio), aloca memoria, y copia solo los caracteres del rango [start, end).
** - ERRORES QUE CONTROLA:
**   [1] malloc falla → retorna NULL
** - NOTA: retorna nueva cadena dinámicamente asignada; responsabilidad del
**   llamador es liberarla.
*/
char	*c3d_trim_spaces(const char *s)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trim;

	start = 0;
	while (s[start] && c3d_isspace(s[start]))
		start++;
	end = c3d_strlen(s);
	while (end > start && c3d_isspace(s[end - 1]))
		end--;
	trim = malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (NULL);
	i = 0;
	while (start < end)
		trim[i++] = s[start++];
	trim[i] = '\0';
	return (trim);
}
