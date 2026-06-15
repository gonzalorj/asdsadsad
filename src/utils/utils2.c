/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:34:55 by gonza             #+#    #+#             */
/*   Updated: 2026/06/15 22:06:17 by gonza            ###   ########.fr       */
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
