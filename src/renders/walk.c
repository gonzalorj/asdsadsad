/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:22:12 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:52:50 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Comprueba si el jugador puede moverse a la nueva posición sin
** atravesar paredes.
**
** Se hace una comprobación por ejes (X e Y por separado) para
** permitir deslizamiento suave contra las paredes.
**
** Si la celda no es '1' (pared), se actualiza la posición.
*/
static void	test_move(t_scene *s, double x, double y)
{
	if (s->map.matrix[(int)s->player.player_y][(int)x] != '1')
		s->player.player_x = x;

	if (s->map.matrix[(int)y][(int)s->player.player_x] != '1')
		s->player.player_y = y;
}

/*
** Movimiento hacia delante.
** Se avanza en la dirección en la que el jugador está mirando
** (look_dir), multiplicado por la velocidad MS.
*/
void	walk_forwards(t_scene *s)
{
	double	x;
	double	y;

	x = s->player.player_x + s->player.look_dir_x * MS;
	y = s->player.player_y + s->player.look_dir_y * MS;
	test_move(s, x, y);
}

/*
** Movimiento lateral hacia la izquierda (strafe left).
** Usa el plano de cámara, que es perpendicular a la dirección
** de visión del jugador.
*/
void	walk_left(t_scene *s)
{
	double	x;
	double	y;

	x = s->player.player_x - s->player.camera_plane_x * MS;
	y = s->player.player_y - s->player.camera_plane_y * MS;
	test_move(s, x, y);
}

/*
** Movimiento hacia atrás.
** Es el inverso del vector de dirección del jugador.
*/
void	walk_backwards(t_scene *s)
{
	double	x;
	double	y;

	x = s->player.player_x - s->player.look_dir_x * MS;
	y = s->player.player_y - s->player.look_dir_y * MS;
	test_move(s, x, y);
}

/*
** Movimiento lateral hacia la derecha (strafe right).
** Es el inverso del movimiento a la izquierda sobre el plano de cámara.
*/
void	walk_right(t_scene *s)
{
	double	x;
	double	y;

	x = s->player.player_x + s->player.camera_plane_x * MS;
	y = s->player.player_y + s->player.camera_plane_y * MS;
	test_move(s, x, y);
}
