# include "../include/cub3d.h"

// PARSE
// ** Flujo general:
// ** 1. parse_cub_file() valida argumentos, lee el archivo completo y coordina el proceso
// ** 2. parse_identifiers() procesa IDs (NO, SO, WE, EA, F, C) y detecta el inicio del mapa
// ** 3. extract_map() extrae el mapa desde la primera línea válida, calcula dimensiones y valida estructura básica
// ** 4. validate_map() comprueba integridad del mapa:
// **    - caracteres válidos
// **    - existencia de un único jugador
// **    - mapa cerrado (sin huecos)

/*
** main:
** Punto de entrada del programa. Verifica los argumentos y lanza el parseo
** del fichero .cub recibido.
*/

//he reformulado parte del parseo aqui para ahorrar la linea de ac != 2 en main y asi tener mas espacio en caso de que lo necesitemos

static void parse_args(int argc, char **argv)
{
	int fd;
	char *str;
	char *name;

	if(argc != 2)
		ft_error("Invalid number of arguments.\n");
	name = ft_strrchr(argv[1], '/');
	if (name)
		name++;
	else
		name = argv[1];
	if (name[0] == '.')
		ft_error("Hidden files are not allowed\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		if(fd >= 0)
			close(fd);
		ft_error("File cannot be opened or readed\n");
	}
	close(fd);
	str = ft_strrchr(argv[1], '.');
	if (!str || ft_strcmp(str, ".cub") || ft_strlen(str) != 4)
		ft_error("Invalid format.\n");
}

static void	init_scene(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(t_scene));
	scene->map_scale = SCALE; //minimap scale
	scene->controls = 1;
	scene->map.f_color = -42; //-42 arbitrario solo se usa en caso de error
	scene->map.c_color = -42;
}

static void init_mlx(t_scene *scene, char *s)
{
	scene->mlx = mlx_init();
	if(!scene->mlx)
		parser_error(scene, NULL, "Minilibx error.");
	load_imgs(scene);
	scene->wdw = mlx_new_window(scene->mlx, WDW_WIDTH, WDW_HEIGHT, s);
	if(!scene->wdw)
		parser_error(scene, NULL, "Image failed.");
	scene->image.img = mlx_new_image(scene->mlx, WDW_WIDTH, WDW_HEIGHT);
	if(!scene->image.img)
		parser_error(scene, NULL, "Image failed.");
	scene->image.addr = mlx_get_data_addr(scene->image.img, &scene->image.bpp,
			&scene->image.len, &scene->image.endian);
	if (!scene->image.addr)
		parser_error(scene, NULL, "Adress error");
}

static void get_start_pos(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->map.height)
	{
		j = 0;
		while (j < scene->map.width)
		{
			if (ft_strchr("NSEW", scene->map.matrix[i][j]))
			{
				scene->player.player_x = j + 0.5;
				scene->player.player_y= i + 0.5;
				get_directions(scene, scene->map.matrix[i][j]);
				scene->map.matrix[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	t_scene scene;
	printf("1\n");
	parse_args(argc, argv);
	printf("2\n");
	init_scene(&scene);
	printf("3\n");
	parse_cub_file(&scene, argv[1]);
	printf("4\n");
	init_mlx(&scene, TITLE);
	printf("5\n");
	get_start_pos(&scene);
	printf("6\n");
	render(&scene);
	printf("7\n");
	events(&scene);
	printf("8\n");
	mlx_loop(scene.mlx);
	printf("9\n");
	return (0);
}
