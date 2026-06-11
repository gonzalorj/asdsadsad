/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:05:43 by gorodrig          #+#    #+#             */
/*   Updated: 2026/06/11 10:05:43 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_lines(char *filename, t_scene *scene)
{
	char	*line;

	scene->map.fd = open(filename, O_RDONLY);
	if (scene->map.fd < 0)
		parser_error(NULL, NULL, "File can't be opened");
	line = get_next_line(scene->map.fd);
	if (!line)
	{
		close(scene->map.fd);
		parser_error(scene, NULL, "File is empty");
	}
	return (line);
}

void	trim_nl(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	while (i > 0 && (line[i - 1] == '\n' || line[i - 1] == '\r'))
		line[--i] = '\0';
}

static void	check_map_data(t_scene *scene)
{
	if (!scene->map.matrix || !scene->map.no_txtr || !scene->map.so_txtr
		|| !scene->map.we_txtr || !scene->map.ea_txtr
		|| scene->map.f_color == -42 || scene->map.c_color == -42)
		parser_error(scene, NULL, "Missing data");
}

void	parse_cub_file(t_scene *scene, char *filename)
{
	char	*line;
	int		start;
	int		end;

	line = get_lines(filename, scene);
	start = 0;
	end = 0;
	while (line)
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
