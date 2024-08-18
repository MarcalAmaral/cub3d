/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:48:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/18 16:14:17 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include "data.h"
#include <stdio.h>
#include "draw_image.h"
#include <libft.h>
#include "defines.h"
#include "ray_casting.h"
#include <math.h>

static void ctrl(int c, t_data *data);

void ft_hook(void* param)
{
	t_data *data;

	data = (t_data*) param;
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->window.mlx);
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_UP))
		ctrl(MLX_KEY_UP, data);
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_DOWN))
		ctrl(MLX_KEY_DOWN, data);
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_LEFT))
		ctrl(MLX_KEY_LEFT, data);
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_RIGHT))
		ctrl(MLX_KEY_RIGHT, data);
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_A))
		ctrl(MLX_KEY_A, data);
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_D))
		ctrl(MLX_KEY_D, data);
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_S))
		ctrl(MLX_KEY_S, data);
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_W))
		ctrl(MLX_KEY_W, data);
	draw_plaine(data);
	ray_casting(data);
}

static void ctrl(int c, t_data *data)
{
	double dir;
	double plane;

	if (c == MLX_KEY_W)
	{
		if (data->worldmap[(int)(data->coord->pos[Y] + data->coord->dir[Y] * MOVE_SPPED)][(int) (data->coord->pos[X])] == '0')
			data->coord->pos[Y] +=  data->coord->dir[Y] * MOVE_SPPED;
		if (data->worldmap[(int)data->coord->pos[Y]][(int)(data->coord->pos[X] + data->coord->dir[X] * MOVE_SPPED)] == '0')
			data->coord->pos[X] += data->coord->dir[X] * MOVE_SPPED;
	}
	else if (c == MLX_KEY_A)
	{
		if (data->worldmap[(int) data->coord->pos[Y]][(int)(data->coord->pos[X] - data->coord->plane[X] * MOVE_SPPED)] == '0')
		{
			data->coord->pos[X] -= data->coord->plane[X] * MOVE_SPPED;
		}
		if (data->worldmap[(int) (data->coord->pos[Y] - data->coord->plane[Y] * MOVE_SPPED)][(int) data->coord->pos[X]] == '0')
			data->coord->pos[Y] -= data->coord->plane[Y] * MOVE_SPPED;

	}
	else if (c == MLX_KEY_D)
	{
		if (data->worldmap[(int) data->coord->pos[Y]][(int)(data->coord->pos[X] + data->coord->plane[X] * MOVE_SPPED)] == '0')
		{
			data->coord->pos[X] += data->coord->plane[X] * MOVE_SPPED;
		}
		if (data->worldmap[(int) (data->coord->pos[Y] + data->coord->plane[Y] * MOVE_SPPED)][(int) data->coord->pos[X]] == '0')
			data->coord->pos[Y] += data->coord->plane[Y] * MOVE_SPPED;

	}
	else if (c == MLX_KEY_S)
	{
		if (data->worldmap[(int)(data->coord->pos[Y] - data->coord->dir[Y] * MOVE_SPPED)][(int) (data->coord->pos[X])] == '0')
			data->coord->pos[Y] -=  data->coord->dir[Y] * MOVE_SPPED;
		if (data->worldmap[(int)data->coord->pos[Y]][(int)(data->coord->pos[X] - data->coord->dir[X] * MOVE_SPPED)] == '0')
			data->coord->pos[X] -= data->coord->dir[X] * MOVE_SPPED;
	}
	else if (c == MLX_KEY_LEFT)
	{
		dir = data->coord->dir[Y];
		plane = data->coord->plane[Y];
		data->coord->dir[Y] = data->coord->dir[Y] * cos(ROT_SPEED) - data->coord->dir[X] * sin (ROT_SPEED);
		data->coord->dir[X] = dir * sin (ROT_SPEED) + data->coord->dir[X] * cos(ROT_SPEED);
		data->coord->plane[Y] = data->coord->plane[Y] * cos(ROT_SPEED) - data->coord->plane[X] * sin (ROT_SPEED);
		data->coord->plane[X] = plane * sin (ROT_SPEED) + data->coord->plane[X] * cos(ROT_SPEED);
	}
	else if (c == MLX_KEY_RIGHT)
	{

		dir = data->coord->dir[Y];
		plane = data->coord->plane[Y];
		data->coord->dir[Y] = data->coord->dir[Y] * cos(-ROT_SPEED) - data->coord->dir[X] * sin (-ROT_SPEED);
		data->coord->dir[X] = dir * sin (-ROT_SPEED) + data->coord->dir[X] * cos(-ROT_SPEED);
		data->coord->plane[Y] = data->coord->plane[Y] * cos(-ROT_SPEED) - data->coord->plane[X] * sin (-ROT_SPEED);
		data->coord->plane[X] = plane * sin (-ROT_SPEED) + data->coord->plane[X] * cos(-ROT_SPEED);
	}
}