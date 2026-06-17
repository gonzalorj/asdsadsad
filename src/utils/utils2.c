/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:34:55 by gonza             #+#    #+#             */
/*   Updated: 2026/06/17 09:55:48 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_texture_helper(t_scene *s, t_img *txtr)
{
	if (txtr->img)
	{
		mlx_destroy_image(s->mlx, txtr->img);
		txtr->img = NULL;
		txtr->addr = NULL;
	}
}

void	free_textures(t_scene *s)
{
	free_texture_helper(s, &s->txtr.no);
	free_texture_helper(s, &s->txtr.so);
	free_texture_helper(s, &s->txtr.we);
	free_texture_helper(s, &s->txtr.ea);
}

void	gnl_clear(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

int	end_comma(char *line)
{
	char	*s;
	char	*e;

	while (*line && c3d_isspace(*line))
		line++;
	s = line;
	if (*s == ',' || *s == '\0')
		return (1);
	e = s + ft_strlen(s) - 1;
	while (e < s && c3d_isspace(*e))
		e--;
	return (*e == ',');
}

int	double_comma(char *s)
{
	int	i;
	int	seen;

	i = 0;
	seen = 0;
	while (s[i])
	{
		if (s[i] == ',')
		{
			if (seen)
				return (1);
			seen = 1;
		}
		else if (!c3d_isspace(s[i]))
			seen = 0;
		i++;
	}
	return (0);
}
