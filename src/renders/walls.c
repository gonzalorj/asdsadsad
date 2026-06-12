/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:24:22 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:53:09 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Limita un valor entero dentro de un rango [min, max].
**
** Se usa principalmente para evitar accesos fuera de los límites
** de texturas o coordenadas de pantalla.
*/
int	limit_n(int n, int min, int max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}

/*
** Obtiene el color (RGB) de un píxel dentro de una textura.
**
** Convierte coordenadas (x, y) en un offset dentro del buffer
** de la imagen y devuelve el valor del píxel.
*/
static int	pixel_rgb(t_img *wall, int x_txtr, int y_txtr)
{
	int		bpp;
	char	*s;

	bpp = wall->bpp / 8;

	/*
	** Acceso directo al buffer de la imagen:
	** y * line_length + x * bytes_per_pixel
	*/
	s = wall->addr + y_txtr * wall->len + x_txtr * bpp;

	return (*(int *)s);
}

/*
** Calcula los límites verticales donde se dibuja la pared en pantalla.
**
** El objetivo es centrar la pared en la pantalla según su altura
** proyectada y recortar si se sale de los límites.
*/
static void	get_wall_bounds(int *start, int *end, int height)
{
	*start = WDW_HEIGHT / 2 - height / 2;
	if (*start < 0)
		*start = 0;

	*end = WDW_HEIGHT / 2 + height / 2;
	if (*end >= WDW_HEIGHT)
		*end = WDW_HEIGHT - 1;
}

/*
** Dibuja una columna vertical de pared en pantalla.
**
** Para cada píxel vertical:
**   - Calcula la coordenada Y en la textura
**   - Obtiene el color del píxel de la textura
**   - Lo dibuja en la imagen final
*/
static void	get_column(t_scene *s, t_img *wall, int x, int height)
{
	int	x_txtr;
	int	y_txtr;
	int	rgb;
	int	start;
	int	end;

	get_wall_bounds(&start, &end, height);

	/*
	** Coordenada X fija de la textura para toda la columna.
	*/
	x_txtr = txtr_x(&s->ray, wall, &s->player);

	while (start <= end)
	{
		y_txtr = txtr_y(start, height, wall->h);
		rgb = pixel_rgb(wall, x_txtr, y_txtr);
		draw_pixel(&s->image, x, start, rgb);
		start++;
	}
}

/*
** Selecciona la textura correcta según el lado impactado por el rayo
** y la dirección del impacto.
**
** Luego calcula la altura proyectada de la pared y la dibuja como columna.
*/
void	get_wall(t_scene *s, int x)
{
	t_ray	*r;
	int		height;

	r = &s->ray;

	/*
	** Proyección de la altura de la pared:
	** cuanto más lejos, más pequeña aparece.
	*/
	height = (int)(WDW_HEIGHT / r->wall_dist);

	/*
	** Selección de textura según dirección del impacto:
	**
	** side == 0 -> impacto en eje X (pared este/oeste)
	** side == 1 -> impacto en eje Y (pared norte/sur)
	*/
	if (r->side == 0)
	{
		if (r->map_x > s->player.player_x)
			get_column(s, &s->txtr.ea, x, height);
		else
			get_column(s, &s->txtr.we, x, height);
	}
	else
	{
		if (r->map_y > s->player.player_y)
			get_column(s, &s->txtr.so, x, height);
		else
			get_column(s, &s->txtr.no, x, height);
	}
}
