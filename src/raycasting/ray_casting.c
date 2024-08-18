/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:16:46 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/18 15:43:29 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "data.h"
#include "ray_casting.h"
#include "dda.h"
#include <stdio.h>
#include "defines.h"
#include <MLX42.h>
#include "utils.h"
#include <stdlib.h>
#include <math.h>

static void defineTexture(t_data *data, t_dda *dda, t_ray *ray);
static void	init(t_ray *ray, t_data *data);
// static int defineColor(t_data *data, t_dda *dda, t_ray *ray);
// static void draw(t_data *data, t_dda *dda, t_ray ray);


void	ray_casting(t_data *data)
{
	t_ray	ray;
	t_dda	dda;

	ray.index = 0;
	while (ray.index < WIDTH -1)
	{
		init(&ray, data);
		ft_dda(data, &ray, &dda);
		ray.line_height = (int) (HEIGHT / ray.distance_wall);
		ray.draw_start = -ray.line_height / 2 + HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = 	ray.line_height / 2 + HEIGHT / 2;
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT -1;
		defineTexture(data, &dda, &ray);
		// draw(data, &dda, ray);
		ray.index++;
	}
}

static void	init(t_ray *ray, t_data *data)
{
	ray->camX = 2 * ray->index / (double) WIDTH -1;
	ray->ray_dir[Y] = data->coord->dir[Y] + data->coord->plane[Y] * ray->camX;
	ray->ray_dir[X] = data->coord->dir[X] + data->coord->plane[X] * ray->camX;
	ray->distance_wall = 0;
}

// static int		defineColor(t_data *data, t_dda *dda, t_ray *ray)
// {
// 	int allcolor[5];
// 	int color;
// 	int value;

// 	allcolor[0] = ft_color(255, 0, 0, 255);
// 	allcolor[1] = ft_color(0, 255, 0, 255);
// 	allcolor[2] = ft_color(0, 0, 255, 255);
// 	allcolor[3] = ft_color(0, 0, 0, 255);
// 	allcolor[4] = ft_color(255, 255, 224, 255);
// 	value = data->worldmap[dda->map[Y]][dda->map[Y]] - '0';
// 	if (value == 1)
// 	{
// 		if (ray->ray_dir[Y] < 0)
// 			color = allcolor[0];
// 		else if (ray->ray_dir[Y] > 0)
// 			color = allcolor[1];
// 		else if (ray->ray_dir[X] < 0)
// 			color = allcolor[2];
// 		else if (ray->ray_dir[X] > 0)
// 			color = allcolor[3];
// 	}
// 	if (dda->side == 1)
// 		color = color / 2;
// 	return (color);
// }

// static void draw(t_data *data, t_dda *dda, t_ray ray)
// {
// 	int red = defineColor(data, dda, &ray);

// 	while (ray.draw_start < ray.draw_end)
// 	{
// 		mlx_put_pixel(data->window.image, ray.index, ray.draw_start, red);
// 		ray.draw_start++;
// 	}
// }

uint32_t buffer[HEIGHT];

void	draw_v_line(t_data *data, int col, int start, int end)
{
	int	row;

	row = start;
	while (row < end)
	{
		mlx_put_pixel(data->window.image, col, row,
			buffer[row]);
		row++;
	}
	ft_bzero(buffer, HEIGHT);
}

static unsigned int	rearrange_color(unsigned int argb)
{
	unsigned int	blue;
	unsigned int	green;
	unsigned int	red;
	unsigned int	alpha;

	blue = (argb & 0xFF) << 24;
	green = (argb & 0xFF00) << 8;
	red = (argb & 0xFF0000) >> 8;
	alpha = (argb & 0xFF000000) >> 24;
	return (blue | green | red | alpha);
}

static void catch_texture(t_data *data, t_dda *dda, t_ray *ray, t_texture_index tex)
{
	double wallX; //where exactly the wall was hit
    if(dda->side == NORTH || dda->side == SOUTH)
		wallX = data->coord->pos[X] + ray->distance_wall * ray->ray_dir[X];
	else
		wallX = data->coord->pos[Y] + ray->distance_wall * ray->ray_dir[Y];
	wallX -= floor(wallX);
	
	int	texX = (int) (wallX * (double)data->window.wall[tex]->width);
	// if (dda->side == NORTH || dda->side == SOUTH)
	// 	texX = data->window.wall[tex]->width - texX - 1;
	// if (dda->side == EAST || dda->side == WEST)
	// 	texX = data->window.wall[tex]->width - texX - 1;
	// printf("WallX value: %f texX value: %d\n", wallX, texX);
	double step = (double) data->window.wall[tex]->height / ray->line_height;
	
	double texPos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	for (int y = ray->draw_start; y < ray->draw_end; y++)
	{
		int texY = (int) texPos & (data->window.wall[tex]->height - 1);
		texPos += step;
		unsigned int color = *((unsigned int *)data->window.wall[tex]->pixels
				+ (unsigned int)(texY * data->window.wall[tex]->width
					+ texX));
		unsigned int color_hex = rearrange_color(color);
		// uint32_t color = ((uint32_t *)data->window.wall[NORTH]->pixels)[data->window.wall[NORTH]->height * texY + texX];
		buffer[y] = color_hex;
	}
}

static void defineTexture(t_data *data, t_dda *dda, t_ray *ray)
{
	// int value;

	// value = data->worldmap[dda->map[Y]][dda->map[Y]] - '0';
// if (value == 1)
	// {
		
		// double wallX; //where exactly the wall was hit
    	// if(dda->side == 0)
		// 	wallX = data->coord->pos[X] + ray->distance_wall * ray->ray_dir[X];
		// else
		// 	wallX = data->coord->pos[Y] + ray->distance_wall * ray->ray_dir[Y];
		// wallX -= floor(wallX);
		
		// int	texX = (int) (wallX * (double)data->window.wall[NORTH]->width);
		// printf("WallX value: %f texX value: %d\n", wallX, texX);
		// // if (dda->side == 0 && ray->ray_dir[X] > 0)
		// // 	texX = data->window.wall[NORTH]->width - texX - 1;
		// // if (dda->side == 1 && ray->ray_dir[Y] < 0)
		// // 	texX = data->window.wall[NORTH]->width - texX - 1;
		// // texX = data->window.wall[NORTH]->width - texX - 1;
		// double step = (double) data->window.wall[NORTH]->height / ray->line_height;
		
		// double texPos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
		// for (int y = ray->draw_start; y < ray->draw_end; y++)
		// {
		// 	int texY = (int) texPos & (data->window.wall[NORTH]->height - 1);
		// 	texPos += step;
		// 	unsigned int color = *((unsigned int *)data->window.wall[NORTH]->pixels
		// 			+ (unsigned int)(texY * data->window.wall[NORTH]->width
		// 				+ texX));
		// 	unsigned int color_hex = rearrange_color(color);
		// 	// uint32_t color = ((uint32_t *)data->window.wall[NORTH]->pixels)[data->window.wall[NORTH]->height * texY + texX];
		// 	buffer[y] = color_hex;
		// }
		// printf("current side: %d\n", dda->side);
		if (dda->side == EAST)
			catch_texture(data, dda, ray, EAST);
		else if (dda->side == NORTH)
			catch_texture(data, dda, ray, NORTH);
		else if (dda->side == SOUTH)
			catch_texture(data, dda, ray, SOUTH);
		else if (dda->side == WEST)
			catch_texture(data, dda, ray, WEST);
		draw_v_line(data, ray->index, ray->draw_start, ray->draw_end);
		// if (ray->ray_dir[Y] < 0)
		// else if (ray->ray_dir[Y] > 0)
			
		// else if (ray->ray_dir[X] < 0)
			
		// else if (ray->ray_dir[X] > 0)
			
	// }
	return ;
}