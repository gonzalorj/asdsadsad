#include "../include/cub3d.h"

static void build_ray(t_scene *scene, t_ray *ray, double cam)
{
	ray->dir_x = scene->player.look_dir_x + scene->player.camera_plane_x * cam;
	ray->dir_y = scene->player.look_dir_y + scene->player.camera_plane_y * cam;
	if (ray->dir_x == 0.0)
		ray->dir_x = MARGIN;
	if (ray->dir_y == 0.0)
		ray->dir_y = MARGIN;
	ray->map_x = (int)scene->player.player_x;
	ray->map_y = (int)scene->player.player_y;
	ray->d_dist_x = fabs(1.0 / ray->dir_x);
	ray->d_dist_y = fabs(1.0 / ray->dir_y);
}

void init_ray_dda(t_scene *s, t_ray *r)
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

static void dda(t_scene *s, t_ray *r)
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

static void get_dist(t_scene *s, double cam)
{
	t_ray *r;
	double dis;

	r = &s->ray;
	build_ray(s, r, cam);
	init_ray_dda(s, r);
	dda(s, r);
	if (r->side == 0)
		dis = r->map_x - s->player.player_x + (1 - r->step_x) * 0.5;
	else
		dis = r->map_y - s->player.player_y + (1 - r->step_y) * 0.5;
	if (r->side == 0)
		r->wall_dist = dis / r->dir_x;
	else
		r->wall_dist = dis / r->dir_y;
	if (r->wall_dist < 0.01)
		r->wall_dist = 0.01;

}

void get_rays(t_scene *scene)
{
	int 	x;
	double 	cam;

	x = 0;
	while(x < WDW_WIDTH)
	{
		cam = 2.0 * x / (double)WDW_WIDTH - 1.0;
		ft_memset(&scene->ray, 0, sizeof(t_ray));
		get_dist(scene, cam);
		get_wall(scene, x);
		x++;
	}
}