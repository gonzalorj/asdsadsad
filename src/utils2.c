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


