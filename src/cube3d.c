/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:57 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/31 13:50:04 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"
#include <stdio.h>
#include <math.h>
#include "../includes/mlx.h"
#include <float.h>
#include <stdlib.h>
#include <sys/time.h>

void	shoot_rays(t_map *map)
{
	int			i;
	float		angle;
	t_coord		map_check;
	t_fcoord	step;
	t_ray		*ray;

	map->rays = malloc(sizeof(t_ray *) * WIN_W);
	angle = (map->player->angle) - (DR / 16 * (WIN_W / 2));
	if (angle < 0)
		angle += 2 * PI;
	else if (angle > 2 * PI)
		angle -= 2 * PI;
	i = -1;
	while (++i < WIN_W)
	{
		map->rays[i] = init_ray(angle, map);
		ray = map->rays[i];
		init_map_check_ray_dir(ray, &map_check, map, &step);
		calculate_intersection(ray,
			walk_shortest_path(ray, &map_check, &step, map));
		angle = rotate_angle(angle);
	}
}

void	set_player_posix(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->ylen)
	{
		x = -1;
		while (++x < map->xlen)
		{
			if (map->coord[y][x] == 'N' || map->coord[y][x] == 'S'
				|| map->coord[y][x] == 'E' || map->coord[y][x] == 'W')
			{
				map->player->x = x + 0.5;
				map->player->y = y + 0.5;
				map->coord[y][x] = '0';
			}
		}
	}
}

void	create_screen(t_map *map)
{
	int	x;
	
	set_player_posix(map);
	shoot_rays(map);
	render_background(map, WIN_W);
	render_rays(map, WIN_W);
	render_doors(map, WIN_W);
	draw_minimap(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
	x = -1;
	while (++x < WIN_W)
		free(map->rays[x]);
	free(map->rays);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_data	img;

	map = malloc(sizeof(t_map));
	if (argc == 2 && check_cub(map, argv[1]))
	{
		map->mlx = mlx_init();
		map->win = mlx_new_window(map->mlx, WIN_W, WIN_H, "MLX CUBE3D");
		img.img = mlx_new_image(map->mlx, WIN_W, WIN_H);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		map->img = &img;
		get_textures(map);
		create_screen(map);
		map->last_frame = 0;
		mlx_hook(map->win, 2, 0, deal_key, map);
		mlx_hook(map->win, 6, 0, read_mouse, map);
		mlx_loop_hook(map->mlx, render_screen, map);
		mlx_mouse_move(map->win, 100, 100);
		mlx_mouse_hide(map->mlx, map->win);
		mlx_loop(map->mlx);
	}
	return (0);
}
