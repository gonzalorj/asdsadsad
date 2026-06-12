/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:25:52 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:25:52 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
