/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:48:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/17 19:25:09 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"
#include "data.h"
#include "parse.h"
#include "draw_image.h"
#include "libft.h"
#include "MLX42.h"
#include <stdlib.h>
#include "ray_casting.h"
#include "defines.h"
#include <stdio.h>
#include "utils.h"

int main(int argc, char **argv)
{
	t_data	*data;

	data = parse(argc, argv);
	if (!data)
		return (error_handler("ERROR\n", NULL, NULL, NULL));
	draw_plaine(data);
	ray_casting(data);


	uint32_t h, w;
	uint32_t color;
	w = data->window.wall[NORTH]->width;
	h = data->window.wall[NORTH]->height;
	for (uint32_t i = 0; i < h * w; i++)
	{
		color = ((uint32_t*)data->window.wall[NORTH]->pixels)[i];
		mlx_put_pixel(data->window.player, i % w, i / h, color);
	}
	mlx_image_to_window(data->window.mlx, data->window.image, 0, 0);
	// mlx_image_to_window(data->window.mlx, data->window.player, 0, 0);
	mlx_loop_hook(data->window.mlx, ft_hook, (void*)data);
	mlx_loop(data->window.mlx);
	mlx_terminate(data->window.mlx);
	ft_delcmtrx(data->worldmap);
	return (EXIT_SUCCESS);
}
