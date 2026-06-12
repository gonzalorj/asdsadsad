/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:19:13 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:52:18 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Dibuja un píxel individual en la imagen.
**
** Convierte coordenadas (x, y) en un índice lineal dentro del buffer
** de la imagen y escribe el color en formato RGB.
**
** Se comprueba que el píxel esté dentro de la ventana para evitar
** escrituras fuera de memoria.
*/
void	draw_pixel(t_img *image, int x, int y, int rgb)
{
	int	pixel_i;

	if (x >= 0 && x < WDW_WIDTH && y >= 0 && y < WDW_HEIGHT)
	{
		/*
		** Cálculo del índice del píxel dentro del buffer:
		** - bpp / 8 = bytes por píxel
		** - len = tamaño de una fila en bytes
		*/
		pixel_i = (x * image->bpp / 8) + (y * image->len);

		*(int *)(image->addr + pixel_i) = rgb;
	}
}

/*
** Rellena la pantalla con cielo y suelo.
**
** Divide la pantalla horizontalmente:
**   - Parte superior: color del cielo
**   - Parte inferior: color del suelo
**
** Esto crea el fondo base sobre el que se dibuja el raycasting.
*/
static void	put_floor_n_ceiling(t_scene *scene)
{
	int	i;
	int	j;
	int	rgb;

	i = 0;
	while (i < WDW_HEIGHT)
	{
		j = 0;

		if (i < WDW_HEIGHT / 2)
			rgb = scene->map.c_color;
		else
			rgb = scene->map.f_color;

		while (j < WDW_WIDTH)
		{
			draw_pixel(&scene->image, j, i, rgb);
			j++;
		}
		i++;
	}
}

/*
** Función principal de renderizado por frame.
**
** Orden de ejecución:
**   1. Pintar fondo (suelo + cielo)
**   2. Lanzar raycasting para dibujar paredes
**   3. Volcar la imagen final en la ventana
*/
void	render(t_scene *scene)
{
	put_floor_n_ceiling(scene);
	get_rays(scene);
	mlx_put_image_to_window(scene->mlx, scene->wdw, scene->image.img, 0, 0);
}
