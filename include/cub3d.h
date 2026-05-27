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
//# include "../libft/src/get_next_line/get_next_line.h"

#define SCALE 15
#define TITLE "cub3d"
#define MAX_TXTR 1024
#define WDW_WIDTH 1024
#define WDW_HEIGHT 1024
#define MARGIN 0.000001
#define MS 0.01
#define RS 0.01

/*
** s_rgb: Almacena valores RGB de un color (piso/techo)
** - r:      Valor rojo (0-255)
** - g:      Valor verde (0-255)
** - b:      Valor azul (0-255)
** - is_set: Flag indicando si se definió este color (1 = definido, 0 = no)
*/
typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
	int	is_set;
}t_rgb;

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

/*
** s_player: Posición inicial y orientación del jugador en el mapa
** - row: Fila de inicio del jugador (coordenada Y en el mapa)
** - col: Columna de inicio del jugador (coordenada X en el mapa)
** - dir: Dirección inicial ('N' norte, 'S' sur, 'E' este, 'O' oeste)
*/

typedef struct s_player
{
	double	player_x;
	double	player_y;

	double	look_dir_x;
	double	look_dir_y;

	double	camera_plane_x;
	double	camera_plane_y;
}	t_player;

/*
** s_map: Representa el mapa del nivel
** - grid:   Array bidimensional de caracteres (mapa en 2D)
**           Caracteres: '0'=vacio, '1'=pared, 'N'/'S'/'E'/'O'=jugador
** - width:  Ancho del mapa (máximo número de columnas)
** - height: Alto del mapa (número total de filas)
*/
typedef struct s_map
{
	char	**matrix;
	int		width;
	int		height;
	int		f_color;
	int		c_color;
	int		fd;
	char	*no_txtr;
	char	*so_txtr;
	char	*we_txtr;
	char	*ea_txtr;
	t_node		*list;
}t_map;

/*
** s_textures: Almacena rutas a archivos de textura para cada pared
** - no: Textura para pared NORTE (North)
** - so: Textura para pared SUR (South)
** - we: Textura para pared OESTE (West)
** - ea: Textura para pared ESTE (East)
*/
typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}t_textures;

/*
** s_scene: Estructura principal que contiene TODA la información del juego
** - tex:     Texturas de las 4 paredes (north, south, west, east)
** - floor:   Color RGB del piso
** - ceiling: Color RGB del techo
** - map:     Mapa del nivel (grid, dimensiones)
** - player:  Posición inicial y dirección del jugador
**
** RELACIÓN CON EL ARCHIVO .CUB:
** Todo lo definido en el archivo de configuración se parsea y almacena aquí
** para ser utilizado por el motor de raycasting en el programa principal.
*/

typedef struct s_txtr
{
	t_img		no;
	t_img		so;
	t_img 		ea;
	t_img		we;
}
				t_txtr;
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

typedef struct s_key
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
}						t_key;

typedef struct s_scene
{
	t_txtr		txtr;
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;
	t_player	player;
	int 		map_scale;
	int			controls;
	t_map		map;
	void		*mlx;
	void		*wdw;
	t_img		image;
	t_ray		ray;
	t_key		key;
}t_scene;

typedef struct s_node
{
	char				*line;
	struct s_node	*next;
}						t_node;





// INIT
void	init_scene(t_scene *scene);

// ERROR + FREE
//void	free_texture_paths(t_scene *scene)
//void	free_map_data(t_scene *scene)
//void	free_scene(t_scene *scene);
//void	free_lines(char **lines);
void	parser_error(t_scene *scene, char **lines, const char *msg);

// PARSE ENTRY
//void	check_cub_extension(const char *filename);
void	parse_cub_file(t_scene *scene, char *filename);

// PARSE FILE LOAD
char	**read_cub_lines(const char *filename);
//int	count_lines(int fd);
//char	*strdup_without_newline(const char *line);
//void	fill_lines_array(int fd, char **lines);

// PARSE IDENTIFIERS
void	parse_divide_cub_lines(t_scene *scene, char *line, int *start, int *end);
//int	is_empty_line(const char *line);
//int	is_map_line(char *line);
//void	parse_identify_line(t_scene *scene, char **lines, char *line);
//void	are_all_elements_present(t_scene *scene, char **lines, int *map_start);

// PARSE TEXTURES
//char		**select_texture_memory(t_scene *scene, char *identifier);
//int		ensure_texture_file_exists(const char *path);
void	parse_texture_line(t_scene *scene, char *line, char **path);

// PARSE COLORS
//char	*skip_spaces(char *line);
//int	search_line_for_colours(char **line, t_scene *scene, char **lines);
//void	load_colour(t_rgb *colour, int red, int green, int blue);
int	parse_colour_line(t_scene *scene,char *line, int *path);
void append_node(t_scene *scene, char *line, t_node **head);

// PARSER UTILS
size_t	strlen(const char* str);
size_t	c3d_strlen(const char *str);
int		strncmp(const char *s1, const char *s2, size_t n);
int		safe_strncmp(const char *s1, const char *s2, size_t n);
int		c3d_isspace(char c);
char	*c3d_trim_spaces(const char *s);
void check_map_lines(t_scene *scene, t_node *head);
int	is_empty_line(const char *line);
void build_matrix(t_scene *scene);
void check_surroundings(t_scene *scene);
void load_imgs(t_scene *scene);
void get_directions(t_scene *scene, char dir);
int	limit_n(int n, int min, int max);
int txtr_x(t_ray *r, t_img *wall, t_player *player);
int	txtr_y(int y, int height, int txtr_h);
void draw_pixel(t_img *image, int x, int y, int rgb);
void render(t_scene *scene);
void walk_forwards(t_scene *s);
void walk_left(t_scene *s);
void walk_backwards(t_scene *s);
void walk_right(t_scene *s);
int	exit_event(t_scene *scene);
void events(t_scene *scene);

#endif