/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:08:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/15 08:42:36 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
 #define DATA_H

#include <MLX42.h>

typedef	struct s_components_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*player;
	mlx_texture_t	*wall[4];
}		t_comp_mlx;

typedef struct s_player
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	time[2];

}	t_plr;

typedef struct s_data
{
	t_comp_mlx	window;
	t_plr		*coord;
	char 		**worldmap;
	int			rgb_floor[4];
	int			rgb_cel[4];
	int			player_rgb[4];
}	t_data;


#endif