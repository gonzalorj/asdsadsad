/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:19:13 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:19:34 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_pixel(t_img *image, int x, int y, int rgb)
{
	int	pixel_i;

	if (x >= 0 && x < WDW_WIDTH && y >= 0 && y < WDW_HEIGHT)
	{
		pixel_i = (x * image->bpp / 8) + (y * image->len);
		*(int *)(image->addr + pixel_i) = rgb;
	}
}

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

void	render(t_scene *scene)
{
	put_floor_n_ceiling(scene);
	get_rays(scene);
	mlx_put_image_to_window(scene->mlx, scene->wdw, scene->image.img, 0, 0);
}
