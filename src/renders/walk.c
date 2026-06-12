/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:22:12 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:23:03 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	test_move(t_scene *s, double x, double y)
{
	if (s->map.matrix[(int)s->player.player_y][(int)x] != '1')
		s->player.player_x = x;
	if (s->map.matrix[(int)y][(int)s->player.player_x] != '1')
		s->player.player_y = y;
}

void	walk_forwards(t_scene *s)
{
	double	x;
	double	y;

	x = s->player.player_x + s->player.look_dir_x * MS;
	y = s->player.player_y + s->player.look_dir_y * MS;
	test_move(s, x, y);
}

void	walk_left(t_scene *s)
{
	double	x;
	double	y;

	x = s->player.player_x - s->player.camera_plane_x * MS;
	y = s->player.player_y - s->player.camera_plane_y * MS;
	test_move(s, x, y);
}

void	walk_backwards(t_scene *s)
{
	double	x;
	double	y;

	x = s->player.player_x - s->player.look_dir_x * MS;
	y = s->player.player_y - s->player.look_dir_y * MS;
	test_move(s, x, y);
}

void	walk_right(t_scene *s)
{
	double	x;
	double	y;

	x = s->player.player_x + s->player.camera_plane_x * MS;
	y = s->player.player_y + s->player.camera_plane_y * MS;
	test_move(s, x, y);
}
