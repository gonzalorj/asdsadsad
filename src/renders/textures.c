/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:19:48 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:52:36 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Calcula la coordenada X de la textura correspondiente al punto
** exacto donde el rayo impacta la pared.
**
** Idea:
** - Se obtiene la posición exacta del impacto (wall_x) dentro de la celda.
** - Se normaliza a rango [0,1] (solo la parte decimal).
** - Se escala al ancho de la textura.
**
** También se corrige la orientación dependiendo del lado de impacto
** para evitar que la textura salga invertida.
*/
int	txtr_x(t_ray *r, t_img *wall, t_player *player)
{
	double	wall_x;
	int		x;

	/*
	** Calcula el punto exacto de impacto del rayo sobre la pared.
	** Se usa X o Y según el lado impactado.
	*/
	if (r->side == 0)
		wall_x = player->player_y + r->wall_dist * r->dir_y;
	else
		wall_x = player->player_x + r->wall_dist * r->dir_x;

	/*
	** Nos quedamos solo con la parte decimal para obtener la
	** posición dentro de la celda [0, 1).
	*/
	wall_x -= floor(wall_x);

	/*
	** Escala esa posición al tamaño de la textura.
	*/
	x = (int)(wall_x * wall->w);

	/*
	** Corrige la orientación de la textura según el lado del impacto
	** para evitar que aparezca espejada.
	*/
	if ((r->side == 0 && r->dir_x > 0)
		|| (r->side == 1 && r->dir_y < 0))
		x = wall->w - x - 1;

	return (limit_n(x, 0, wall->w - 1));
}

/*
** Calcula la coordenada Y de la textura para un píxel concreto de la pared.
**
** - "y" es la coordenada de pantalla.
** - "height" es la altura de la pared proyectada.
** - "txtr_h" es la altura de la textura.
**
** Se mapea la posición del píxel dentro de la pared a la textura.
*/
int	txtr_y(int y, int height, int txtr_h)
{
	int		start;
	double	pos_wall;
	int		txtr_y;

	/*
	** Punto de inicio vertical de la pared en pantalla.
	*/
	start = (WDW_HEIGHT - height) / 2;

	/*
	** Normaliza la posición del píxel dentro de la pared [0,1].
	*/
	pos_wall = (double)(y - start) / height;

	/*
	** Escala esa posición a la altura de la textura.
	*/
	txtr_y = (int)(pos_wall * txtr_h);

	return (limit_n(txtr_y, 0, txtr_h - 1));
}

/*
** Carga una textura XPM desde disco y la convierte en imagen MLX.
**
** Pasos:
**   1. Cargar archivo XPM
**   2. Obtener ancho y alto
**   3. Obtener buffer de píxeles
**   4. Validar errores
*/
static void	asign_path_to_img(t_scene *scene, t_img *ttr, char *path)
{
	ttr->img = mlx_xpm_file_to_image(scene->mlx, path, &ttr->w, &ttr->h);
	if (!ttr->img)
		parser_error(scene, NULL, "Mlx loading image fail.");

	/*
	** Evita texturas excesivamente grandes que puedan romper el render.
	*/
	if (ttr->w > MAX_TXTR || ttr->h > MAX_TXTR)
		parser_error(scene, NULL, "Texture too large.");

	ttr->addr = mlx_get_data_addr(
		ttr->img,
		&ttr->bpp,
		&ttr->len,
		&ttr->endian
	);

	if (!ttr->addr)
		parser_error(scene, NULL, "Texture address failed");
}

/*
** Carga todas las texturas del mapa (N, S, E, W).
** Cada una se asocia a su estructura de imagen correspondiente.
*/
void	load_imgs(t_scene *scene)
{
	asign_path_to_img(scene, &scene->txtr.no, scene->map.no_txtr);
	asign_path_to_img(scene, &scene->txtr.so, scene->map.so_txtr);
	asign_path_to_img(scene, &scene->txtr.ea, scene->map.ea_txtr);
	asign_path_to_img(scene, &scene->txtr.we, scene->map.we_txtr);
}