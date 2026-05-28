# include "cub3d.h"


static char	*skip_spaces(char *line)
{
	while (*line && c3d_isspace(*line))
		line++;
	return (line);
}

static char *rgb_syntax(char *trimmed, int rgb)
{
    char *s;

    if (rgb < 0 || rgb > 255)
        return ("Number must be in between 0-255 range");
    s = skip_spaces(trimmed);
    if (*s == '-' || *s == '+')
        return ("Invalid format");
    if (!ft_isdigit(*s))
        return ("Invalid format");
    while (ft_isdigit(*s))
        s++;
    s = skip_spaces(s);
    if (*s != '\0')
        return ("Invalid format");
    return (NULL);
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
	return (rgb);
}

static int	load_colour(t_scene *scene, char *line, char **splits)
{
	int red;
	int green;
	int blue;

	red = parse_rgb(ft_strtrim(splits[0], " \t"), scene, splits, line);
	green = parse_rgb(ft_strtrim(splits[1], " \t"), scene, splits, line);
	blue = parse_rgb(ft_strtrim(splits[2], " \t"), scene, splits, line);
	return ((red << 16) | (green << 8) | blue);
}

int	parse_colour_line(t_scene *scene,char *line, int *path)
{
	char *s;
	int rgb;
	char **splits;

	if(*path != -42)
	{
		free(line);
		parser_error(scene, NULL, "Duplicated rgb configuration");
	}
	s = line;
	++line;
	splits = ft_split(line, ',');
	if(!splits || !splits[0] || !splits[1] || !splits[2] || splits[3])
	{
		free(s);
		parser_error(scene, splits, "3 numbers are needed");
	}
	rgb = load_colour(scene, s, splits);
	free_split(splits);
	return (rgb);
}



	