/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:19:48 by gonza             #+#    #+#             */
/*   Updated: 2026/06/15 22:05:38 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	txtr_x(t_ray *r, t_img *wall, t_player *player)
{
	double	wall_x;
	int		x;

	if (r->side == 0)
		wall_x = player->player_y + r->wall_dist * r->dir_y;
	else
		wall_x = player->player_x + r->wall_dist * r->dir_x;
	wall_x -= floor(wall_x);
	x = (int)(wall_x * wall->w);
	if ((r->side == 0 && r->dir_x > 0)
		|| (r->side == 1 && r->dir_y < 0))
		x = wall->w - x - 1;
	return (limit_n(x, 0, wall->w - 1));
}

int	txtr_y(int y, int height, int txtr_h)
{
	int		start;
	double	pos_wall;
	int		txtr_y;

	start = (WDW_HEIGHT - height) / 2;
	pos_wall = (double)(y - start) / height;
	txtr_y = (int)(pos_wall * txtr_h);
	return (limit_n(txtr_y, 0, txtr_h - 1));
}

static void	asign_path_to_img(t_scene *scene, t_img *ttr, char *path)
{
	ttr->img = mlx_xpm_file_to_image(scene->mlx, path, &ttr->w, &ttr->h);
	if (!ttr->img)
		parser_error(scene, NULL, "Mlx loading image fail.");
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

void	load_imgs(t_scene *scene)
{
	asign_path_to_img(scene, &scene->txtr.no, scene->map.no_txtr);
	asign_path_to_img(scene, &scene->txtr.so, scene->map.so_txtr);
	asign_path_to_img(scene, &scene->txtr.ea, scene->map.ea_txtr);
	asign_path_to_img(scene, &scene->txtr.we, scene->map.we_txtr);
}
