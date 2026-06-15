/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:24:22 by gonza             #+#    #+#             */
/*   Updated: 2026/06/15 22:05:48 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	limit_n(int n, int min, int max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}

static int	pixel_rgb(t_img *wall, int x_txtr, int y_txtr)
{
	int		bpp;
	char	*s;

	bpp = wall->bpp / 8;
	s = wall->addr + y_txtr * wall->len + x_txtr * bpp;
	return (*(int *)s);
}

static void	get_wall_bounds(int *start, int *end, int height)
{
	*start = WDW_HEIGHT / 2 - height / 2;
	if (*start < 0)
		*start = 0;
	*end = WDW_HEIGHT / 2 + height / 2;
	if (*end >= WDW_HEIGHT)
		*end = WDW_HEIGHT - 1;
}

static void	get_column(t_scene *s, t_img *wall, int x, int height)
{
	int	x_txtr;
	int	y_txtr;
	int	rgb;
	int	start;
	int	end;

	get_wall_bounds(&start, &end, height);
	x_txtr = txtr_x(&s->ray, wall, &s->player);
	while (start <= end)
	{
		y_txtr = txtr_y(start, height, wall->h);
		rgb = pixel_rgb(wall, x_txtr, y_txtr);
		draw_pixel(&s->image, x, start, rgb);
		start++;
	}
}

void	get_wall(t_scene *s, int x)
{
	t_ray	*r;
	int		height;

	r = &s->ray;
	height = (int)(WDW_HEIGHT / r->wall_dist);
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
