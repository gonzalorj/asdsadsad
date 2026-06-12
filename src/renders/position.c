/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:17:37 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:51:41 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Configura la dirección inicial del jugador mirando al Norte.
** El vector de dirección apunta hacia arriba en el mapa y el
** plano de cámara se establece perpendicular a dicha dirección.
*/
static void	get_no(t_scene *scene)
{
	scene->player.look_dir_x = 0.0;
	scene->player.look_dir_y = -1.0;
	scene->player.camera_plane_x = 0.66;
	scene->player.camera_plane_y = 0.0;
}

/*
** Configura la dirección inicial del jugador mirando al Sur.
** El vector de dirección apunta hacia abajo en el mapa y el
** plano de cámara se ajusta para mantener el campo de visión.
*/
static void	get_so(t_scene *scene)
{
	scene->player.look_dir_x = 0.0;
	scene->player.look_dir_y = 1.0;
	scene->player.camera_plane_x = -0.66;
	scene->player.camera_plane_y = 0.0;
}

/*
** Configura la dirección inicial del jugador mirando al Oeste.
** El vector de dirección apunta a la izquierda y el plano de
** cámara se coloca perpendicular a dicha orientación.
*/
static void	get_we(t_scene *scene)
{
	scene->player.look_dir_x = -1.0;
	scene->player.look_dir_y = 0.0;
	scene->player.camera_plane_x = 0.0;
	scene->player.camera_plane_y = -0.66;
}

/*
** Configura la dirección inicial del jugador mirando al Este.
** El vector de dirección apunta a la derecha y el plano de
** cámara se ajusta para el raycasting.
*/
static void	get_ea(t_scene *scene)
{
	scene->player.look_dir_x = 1.0;
	scene->player.look_dir_y = 0.0;
	scene->player.camera_plane_x = 0.0;
	scene->player.camera_plane_y = 0.66;
}

/*
** Inicializa la orientación del jugador según el carácter
** encontrado en el mapa ('N', 'S', 'E' o 'W').
** Cada dirección establece tanto el vector de visión como
** el plano de cámara utilizado durante el raycasting.
*/
void	get_directions(t_scene *scene, char dir)
{
	if (dir == 'N')
		get_no(scene);
	else if (dir == 'S')
		get_so(scene);
	else if (dir == 'W')
		get_we(scene);
	else if (dir == 'E')
		get_ea(scene);
}
