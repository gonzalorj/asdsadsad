#include "../include/cub3d.h"

static void get_no(t_scene *scene)
{
	scene->player.look_dir_x = 0.0;
	scene->player.look_dir_y = -1.0;
	scene->player.camera_plane_x = 0.66;
	scene->player.camera_plane_y = 0.0;
}

static void get_so(t_scene *scene)
{
	scene->player.look_dir_x = 0.0;
	scene->player.look_dir_y = 1.0;
	scene->player.camera_plane_x = -0.66;
	scene->player.camera_plane_y = 0.0;
}

static void get_we(t_scene *scene)
{
	scene->player.look_dir_x = -1.0;
	scene->player.look_dir_y = 0.0;
	scene->player.camera_plane_x = 0.0;
	scene->player.camera_plane_y = -0.66;
}

static void get_ea(t_scene *scene)
{
	scene->player.look_dir_x = 1.0;
	scene->player.look_dir_y = 0.0;
	scene->player.camera_plane_x = 0.0;
	scene->player.camera_plane_y = 0.66;
}

void get_directions(t_scene *scene, char dir)
{
	if(dir == 'N')
		get_no(scene);
	else if(dir == 'S')
		get_so(scene);
	else if(dir == 'W')
		get_we(scene);
	else if(dir == 'E')
		get_ea(scene);
}