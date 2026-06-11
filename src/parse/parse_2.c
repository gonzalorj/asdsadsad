/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:18:58 by gorodrig          #+#    #+#             */
/*   Updated: 2026/06/11 10:18:58 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!c3d_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
		return (0);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	parse_identify_line(t_scene *s, char *line)
{
	if (safe_strncmp(line, "NO", 2) == 0 && c3d_isspace(line[2]))
		parse_texture_line(s, line, &s->map.no_txtr);
	else if (safe_strncmp(line, "SO", 2) == 0 && c3d_isspace(line[2]))
		parse_texture_line(s, line, &s->map.so_txtr);
	else if (safe_strncmp(line, "WE", 2) == 0 && c3d_isspace(line[2]))
		parse_texture_line(s, line, &s->map.we_txtr);
	else if (safe_strncmp(line, "EA", 2) == 0 && c3d_isspace(line[2]))
		parse_texture_line(s, line, &s->map.ea_txtr);
	else if (safe_strncmp(line, "F", 1) && c3d_isspace(line[1]))
		s->map.f_color = parse_colour_line(s, line, &s->map.f_color);
	else if (safe_strncmp(line, "C", 1) && c3d_isspace(line[1]))
		s->map.c_color = parse_colour_line(s, line, &s->map.c_color);
	else
	{
		free(line);
		parser_error(s, NULL, "Invalid line");
	}
}

int	is_info_line(char *s)
{
	while (*s == ' ' || *s == '\t')
		++s;
	return (!ft_strncmp(s, "NO", 2)
		|| !ft_strncmp(s, "SO", 2)
		|| !ft_strncmp(s, "WE", 2)
		|| !ft_strncmp(s, "EA", 2)
		|| !ft_strncmp(s, "F ", 2)
		|| !ft_strncmp(s, "C ", 2));
}

void	parse_divide_cub_lines(t_scene *scene, char *line, int *start, int *end)
{
	if (is_empty_line(line))
	{
		if (*start && !(*end))
			*end = 1;
		return ;
	}
	if (*end)
	{
		free(line);
		parser_error(scene, NULL, "Lines after map");
	}
	if (!(*end) && is_info_line(line))
		parse_identify_line(scene, line);
	else if (is_map_line(line))
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
