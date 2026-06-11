#include "../include/cub3d.h"


int txtr_x(t_ray *r, t_img *wall, t_player *player)
{
    double wall_x;
    int x;

    if (r->side == 0)
        wall_x = player->player_y + r->wall_dist * r->dir_y;
    else
        wall_x = player->player_x + r->wall_dist * r->dir_x;

    wall_x -= floor(wall_x);

    x = (int)(wall_x * wall->w);
    if ((r->side == 0 && r->dir_x > 0) ||
        (r->side == 1 && r->dir_y < 0))
        x = wall->w - x - 1;

    return limit_n(x, 0, wall->w - 1);
}

int	txtr_y(int y, int height, int txtr_h)
{
	int		start;
	double	pos_wall;
	int		txtr_y;

	start = (WDW_HEIGHT - height) / 2;
	pos_wall = (double)(y - start) / height;
	txtr_y = (int)(pos_wall * txtr_h);
	txtr_y = limit_n(txtr_y, 0, txtr_h - 1);
	return (txtr_y);
}

static void asign_path_to_img(t_scene *scene, t_img *txtr, char *path)
{
	txtr->img = mlx_xpm_file_to_image(scene->mlx, path, &txtr->w, &txtr->h);
	if(!txtr->img)
		parser_error(scene, NULL, "Mlx loading image fail.");
	if (txtr->w > MAX_TXTR || txtr->h > MAX_TXTR)
		parser_error(scene, NULL, "Texture too large.");
	txtr->addr = mlx_get_data_addr(txtr->img, &txtr->bpp, &txtr->len, &txtr->endian);
	if (!txtr->addr)
		parser_error(scene, NULL, "Texture address failed");
}

void load_imgs(t_scene *scene)
{
	asign_path_to_img(scene, &scene->txtr.no, scene->map.no_txtr);
	asign_path_to_img(scene, &scene->txtr.so, scene->map.so_txtr);
	asign_path_to_img(scene, &scene->txtr.ea, scene->map.ea_txtr);
	asign_path_to_img(scene, &scene->txtr.we, scene->map.we_txtr);
}