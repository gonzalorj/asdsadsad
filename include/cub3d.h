/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonza <gonza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:38:49 by gonza             #+#    #+#             */
/*   Updated: 2026/06/12 15:38:49 by gonza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h> 
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define SCALE 15
# define TITLE "cub3d"
# define MAX_TXTR 1024
# define WDW_WIDTH 1280
# define WDW_HEIGHT 720
# define MARGIN 0.000001
# define MS 0.028
# define RS 0.04

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
	int	is_set;
}				t_rgb;

typedef struct s_ray
{
	double				dir_x;
	double				dir_y;
	int					map_x;
	int					map_y;
	double				s_dist_x;
	double				s_dist_y;
	double				d_dist_x;
	double				d_dist_y;
	int					step_x;
	int					step_y;
	int					side;
	int					touch;
	double				wall_dist;
}						t_ray;

typedef struct s_player
{
	double	player_x;
	double	player_y;

	double	look_dir_x;
	double	look_dir_y;

	double	camera_plane_x;
	double	camera_plane_y;
}				t_player;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}				t_textures;

typedef struct s_img
{
	void		*img;
	int			h;
	int			w;
	char		*addr;
	int			bpp;
	int			endian;
	int			len;
}				t_img;

typedef struct s_txtr
{
	t_img		no;
	t_img		so;
	t_img		ea;
	t_img		we;
}				t_txtr;

typedef struct s_key
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
}				t_key;

typedef struct s_node
{
	char				*line;
	struct s_node		*next;
}				t_node;

typedef struct s_map
{
	char		**matrix;
	int			width;
	int			height;
	int			f_color;
	int			c_color;
	int			fd;
	char		*no_txtr;
	char		*so_txtr;
	char		*we_txtr;
	char		*ea_txtr;
	t_node		*list;
}				t_map;

typedef struct s_scene
{
	t_txtr		txtr;
	t_rgb		floor;
	t_rgb		ceiling;
	t_player	player;
	int			map_scale;
	t_map		map;
	void		*mlx;
	void		*wdw;
	t_img		image;
	t_ray		ray;
	t_key		key;
}				t_scene;

void	parser_error(t_scene *scene, char **lines, const char *msg);
void	parse_cub_file(t_scene *scene, char *filename);
char	**read_cub_lines(const char *filename);
void	process_lines(t_scene *scene, char *line, int *start, int *end);
void	parse_texture_line(t_scene *scene, char *line, char **path);
int		parse_colour_line(t_scene *scene, char *line, int *path);
void	append_node(t_scene *scene, char *line, t_node **head);
size_t	strlen(const char *str);
size_t	c3d_strlen(const char *str);
int		strncmp(const char *s1, const char *s2, size_t n);
int		safe_strncmp(const char *s1, const char *s2, size_t n);
int		c3d_isspace(char c);
char	*c3d_trim_spaces(const char *s);
void	check_map_lines(t_scene *scene, t_node *head);
int		is_empty_line(const char *line);
void	build_matrix(t_scene *scene);
void	check_surroundings(t_scene *scene);
void	load_imgs(t_scene *scene);
void	get_directions(t_scene *scene, char dir);
int		limit_n(int n, int min, int max);
int		txtr_x(t_ray *r, t_img *wall, t_player *player);
int		txtr_y(int y, int height, int txtr_h);
void	draw_pixel(t_img *image, int x, int y, int rgb);
void	render(t_scene *scene);
void	walk_forwards(t_scene *s);
void	walk_left(t_scene *s);
void	walk_backwards(t_scene *s);
void	walk_right(t_scene *s);
int		exit_event(t_scene *scene);
void	events(t_scene *scene);
void	free_textures(t_scene *s);
void	get_wall(t_scene *s, int x);
void	get_rays(t_scene *scene);
void	gnl_clear(int fd);
int		end_comma(char *line);
int		double_comma(char *s);

#endif