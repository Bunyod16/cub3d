/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:43:04 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/11/02 15:10:41 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159265359

void	render_background(t_map *map, int ray_num)
{
	int	color_top;
	int	color_bottom;
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < ray_num)
	{
		j = -1;
		while (j++ < 810 / 2)
		{
			color_top = map->c_color;
			color_top = darken_rgb(color_top, j * 0.9);
			put_p(map->img, i, j, color_top);
		}
		j = 810;
		k = 810 / 2;
		while (j-- > 810 / 2)
		{
			color_bottom = map->f_color;
			color_bottom = darken_rgb(color_bottom, (j - 810 / 2) * 0.9);
			put_p(map->img, i, k++, color_bottom);
		}
	}
}

void	render_rays(t_map *map, int ray_num)
{
	int		i;
	float	wall_height;

	i = -1;
	while (++i < ray_num)
	{
		wall_height = (40 * 500) / map->rays[i]->len + 0.01;
		connect_dots_colors(map, i, wall_height, map->rays[i]);
	}
}

void	render_doors(t_map *map, int ray_num)
{
	int		i;
	float	wall_height;

	i = -1;
	while (++i < ray_num)
	{
		if (map->rays[i]->isdoor == 'y')
		{
			wall_height = (40 * 500) / map->rays[i]->doorlen + 0.01;
			connect_dots_doors(map, i, wall_height, map->rays[i]);
		}
	}
}

void	calculate_intersection(t_ray *ray, float fDistance)
{
	float	dist_t;
	float	ca;

	ca = ray->playerangle - ray->angle;
	ray->x = (ray->start.x + ray->dir.x * fDistance);
	ray->y = (ray->start.y + ray->dir.y * fDistance);
	if (ray->xmin == 0 && ray->angle > 0 && ray->angle < PI)
		ray->side = 'n';
	else if (ray->xmin == 0 && ray->angle > PI && ray->angle < 2 * PI)
		ray->side = 's';
	if (ray->xmin == 1 && ray->angle < 3 * PI / 2 && ray->angle > (PI / 2))
		ray->side = 'w';
	else if (ray->xmin == 1 && (ray->angle < (PI / 2)
			|| ray->angle > 3 * PI / 2))
		ray->side = 'e';
	dist_t = fDistance * 32;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	if (dist_t != -1)
		dist_t = dist_t * cos(ca);
	ray->len = dist_t;
}

t_ray	*init_ray(float angle, t_map *map)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->angle = angle;
	ray->playerangle = map->player->angle;
	ray->firstdoor = 0;
	ray->isdoor = ';';
	ray->side = 'r';
	ray->start.x = map->player->x;
	ray->start.y = map->player->y;
	ray->max.x = ((map->player->x) + ((cos(angle) / 10) * 2000));
	ray->max.y = ((map->player->y) + ((sin(angle) / 10) * 2000));
	ray->dir.x = ray->max.x - map->player->x;
	ray->dir.y = ray->max.y - map->player->y;
	ray->magnitude = dist(ray->max.x, ray->max.y,
			map->player->x, map->player->y);
	ray->dir.x = ray->dir.x / ray->magnitude;
	ray->dir.y = ray->dir.y / ray->magnitude;
	ray->step_size.x = sqrt(1 + (ray->dir.y / ray->dir.x)
			* (ray->dir.y / ray->dir.x));
	ray->step_size.y = sqrt(1 + (ray->dir.x / ray->dir.y)
			* (ray->dir.x / ray->dir.y));
	return (ray);
}
