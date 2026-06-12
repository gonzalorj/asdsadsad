/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:26:13 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:27:26 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	rotate(t_player *p, double a)
{
	double	x_old;
	double	plane_old;

	x_old = p->look_dir_x;
	plane_old = p->camera_plane_x;
	p->look_dir_x = p->look_dir_x * cos(a) - p->look_dir_y * sin(a);
	p->look_dir_y = x_old * sin(a) + p->look_dir_y * cos(a);
	p->camera_plane_x = p->camera_plane_x * cos(a) - p->camera_plane_y * sin(a);
	p->camera_plane_y = plane_old * sin(a) + p->camera_plane_y * cos(a);
}

static int	press_event(int code, t_scene *s)
{
	if (code == XK_Escape)
		exit_event(s);
	else if (code == XK_w || code == XK_W)
		s->key.w = 1;
	else if (code == XK_a || code == XK_A)
		s->key.a = 1;
	else if (code == XK_s || code == XK_S)
		s->key.s = 1;
	else if (code == XK_d || code == XK_D)
		s->key.d = 1;
	else if (code == XK_Left)
		s->key.left = 1;
	else if (code == XK_Right)
		s->key.right = 1;
	return (0);
}

static int	release_event(int code, t_scene *s)
{
	if (code == XK_w || code == XK_W)
		s->key.w = 0;
	else if (code == XK_a || code == XK_A)
		s->key.a = 0;
	else if (code == XK_s || code == XK_S)
		s->key.s = 0;
	else if (code == XK_d || code == XK_D)
		s->key.d = 0;
	else if (code == XK_Left)
		s->key.left = 0;
	else if (code == XK_Right)
		s->key.right = 0;
	return (0);
}

static int	move_loop(t_scene *s)
{
	if (s->key.w)
		walk_forwards(s);
	if (s->key.a)
		walk_left(s);
	if (s->key.s)
		walk_backwards(s);
	if (s->key.d)
		walk_right(s);
	if (s->key.left)
		rotate(&s->player, -RS);
	if (s->key.right)
		rotate(&s->player, RS);
	render(s);
	return (0);
}

void	events(t_scene *scene)
{
	mlx_hook(scene->wdw, 2, 1L << 0, press_event, scene);
	mlx_hook(scene->wdw, 3, 1L << 1, release_event, scene);
	mlx_hook(scene->wdw, 17, 0L, exit_event, scene);
	mlx_loop_hook(scene->mlx, move_loop, scene);
}
