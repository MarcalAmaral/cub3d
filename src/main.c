/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:48:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/15 16:55:37 by rbutzke          ###   ########.fr       */
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
	draw_plaine(data);
	ray_casting(data);
	mlx_image_to_window(data->window.mlx, data->window.image, 0, 0);
	//mlx_image_to_window(data->window.mlx, data->window.player, 0, 0);
	mlx_loop_hook(data->window.mlx, ft_hook, (void*)data);
	mlx_loop(data->window.mlx);
	mlx_terminate(data->window.mlx);
	ft_delcmtrx(data->worldmap);
	return (EXIT_SUCCESS);
}

