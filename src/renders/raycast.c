/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:18:17 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:52:01 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Construye el rayo correspondiente a una columna de pantalla.
** Se calcula la dirección del rayo combinando:
**   - Dirección del jugador (look_dir)
**   - Plano de cámara (camera_plane)
**   - Coordenada de cámara (cam), que va de -1 a 1
**
** Esto permite simular el campo de visión del jugador en 3D.
*/
static void	build_ray(t_scene *scene, t_ray *ray, double cam)
{
	ray->dir_x = scene->player.look_dir_x + scene->player.camera_plane_x * cam;
	ray->dir_y = scene->player.look_dir_y + scene->player.camera_plane_y * cam;

	/*
	** Evita divisiones por cero en el algoritmo DDA.
	** Si alguna dirección es exactamente 0, se fuerza un valor mínimo.
	*/
	if (ray->dir_x == 0.0)
		ray->dir_x = MARGIN;
	if (ray->dir_y == 0.0)
		ray->dir_y = MARGIN;

	/*
	** Celda del mapa donde se encuentra el jugador.
	** Se usa truncamiento porque el mapa es una grid de tiles.
	*/
	ray->map_x = (int)scene->player.player_x;
	ray->map_y = (int)scene->player.player_y;

	/*
	** Distancia que el rayo debe recorrer para cruzar una unidad
	** completa en el eje X o Y (parte clave del DDA).
	*/
	ray->d_dist_x = fabs(1.0 / ray->dir_x);
	ray->d_dist_y = fabs(1.0 / ray->dir_y);
}

/*
** Inicializa el algoritmo DDA (Digital Differential Analyzer).
** Determina en qué dirección avanzará el rayo en el grid
** y calcula la distancia inicial hasta la primera línea de celda.
*/
void	init_ray_dda(t_scene *s, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->s_dist_x = (s->player.player_x - r->map_x) * r->d_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->s_dist_x = (r->map_x + 1.0 - s->player.player_x) * r->d_dist_x;
	}

	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->s_dist_y = (s->player.player_y - r->map_y) * r->d_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->s_dist_y = (r->map_y + 1.0 - s->player.player_y) * r->d_dist_y;
	}
}

/*
** Ejecuta el algoritmo DDA para detectar la pared.
** El rayo avanza celda a celda hasta chocar con un '1' (pared).
**
** En cada iteración se avanza primero en el eje con menor distancia
** acumulada (X o Y).
*/
static void	dda(t_scene *s, t_ray *r)
{
	r->touch = 0;
	while (!r->touch)
	{
		if (r->s_dist_x < r->s_dist_y)
		{
			r->s_dist_x += r->d_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->s_dist_y += r->d_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (s->map.matrix[r->map_y][r->map_x] == '1')
			r->touch = 1;
	}
}

/*
** Calcula la distancia perpendicular a la pared impactada.
** Corrige el efecto “fish-eye” usando el lado impactado del DDA.
*/
static void	get_dist(t_scene *s, double cam)
{
	t_ray	*r;
	double	dis;

	r = &s->ray;
	build_ray(s, r, cam);
	init_ray_dda(s, r);
	dda(s, r);

	/*
	** Cálculo de distancia según el lado impactado:
	** side == 0 -> impacto en eje X
	** side == 1 -> impacto en eje Y
	*/
	if (r->side == 0)
		dis = r->map_x - s->player.player_x + (1 - r->step_x) * 0.5;
	else
		dis = r->map_y - s->player.player_y + (1 - r->step_y) * 0.5;

	if (r->side == 0)
		r->wall_dist = dis / r->dir_x;
	else
		r->wall_dist = dis / r->dir_y;

	/*
	** Evita distancias absurdamente pequeñas que puedan romper
	** el cálculo del renderizado.
	*/
	if (r->wall_dist < 0.01)
		r->wall_dist = 0.01;
}

/*
** Función principal del raycasting.
** Para cada columna de la pantalla:
**   1. Calcula el rayo
**   2. Ejecuta DDA para encontrar pared
**   3. Calcula distancia a la pared
**   4. Renderiza la columna correspondiente
*/
void	get_rays(t_scene *scene)
{
	int		x;
	double	cam;

	x = 0;
	while (x < WDW_WIDTH)
	{
		/*
		** cam va de -1 a 1 y representa la posición del rayo
		** dentro del campo de visión de la cámara.
		*/
		cam = 2.0 * x / (double)WDW_WIDTH - 1.0;

		ft_memset(&scene->ray, 0, sizeof(t_ray));
		get_dist(scene, cam);
		get_wall(scene, x);
		x++;
	}
}
