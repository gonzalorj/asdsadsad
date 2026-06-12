/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 09:56:42 by gorodrig          #+#    #+#             */
/*   Updated: 2026/06/11 09:56:42 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	parse_args(int argc, char **argv)
{
	int		fd;
	char	*str;
	char	*name;

	if (argc != 2)
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
		if (fd >= 0)
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
	scene->controls = 1;
	scene->map.f_color = -42;
	scene->map.c_color = -42;
}

static void	init_mlx(t_scene *scene, char *s)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		parser_error(scene, NULL, "Minilibx error.");
	load_imgs(scene);
	scene->wdw = mlx_new_window(scene->mlx, WDW_WIDTH, WDW_HEIGHT, s);
	if (!scene->wdw)
		parser_error(scene, NULL, "Image failed.");
	scene->image.img = mlx_new_image(scene->mlx, WDW_WIDTH, WDW_HEIGHT);
	if (!scene->image.img)
		parser_error(scene, NULL, "Image failed.");
	scene->image.addr = mlx_get_data_addr(scene->image.img, &scene->image.bpp,
			&scene->image.len, &scene->image.endian);
	if (!scene->image.addr)
		parser_error(scene, NULL, "Adress error");
}

/*
** Busca la posición inicial del jugador dentro del mapa.
** Recorre toda la matriz hasta encontrar uno de los caracteres
** de orientación ('N', 'S', 'E' o 'W'). Cuando lo encuentra:
**   - Guarda la posición centrada en la celda (+0.5).
**   - Inicializa la dirección y el plano de la cámara.
**   - Sustituye el carácter de orientación por '0' para que
**     la celda pase a considerarse suelo transitable.
*/
static void	get_start_pos(t_scene *scene)
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
				scene->player.player_y = i + 0.5;
				get_directions(scene, scene->map.matrix[i][j]);
				scene->map.matrix[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	parse_args(argc, argv);
	init_scene(&scene);
	parse_cub_file(&scene, argv[1]);
	init_mlx(&scene, TITLE);
	get_start_pos(&scene);
	render(&scene);
	events(&scene);
	mlx_loop(scene.mlx);
	return (0);
}
