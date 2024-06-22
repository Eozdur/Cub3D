/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:00:46 by eozdur            #+#    #+#             */
/*   Updated: 2024/03/04 13:11:12 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "cub3d.h"
#include <stddef.h>

void	map_init(t_game *game)
{
	game->map.map_name = NULL;
	game->map.playercount = 0;
	game->map.c_color = 0;
	game->map.f_color = 0;
	game->map.fd = 0;
	game->map.playercount = 0;
	game->map.real_height = 0;
	game->map.posx = 0;
	game->map.posy = 0;
	game->map.tmp_map = NULL;
	game->map.map = NULL;
	game->map.map_h = 0;
	game->map.floor = NULL;
	game->map.ceiling = NULL;
	game->map.real_map = NULL;
	game->map.infocount = 0;
	game->map.endofinfo = 0;
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->img = NULL;
	game->win = NULL;
	init_array(game);
}

void	init_array(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->map.directions[i] = NULL;
		game->map.textures[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 2)
	{
		game->map.color_path[i] = NULL;
		game->map.rgb_color[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 6)
	{
		game->map.flags[i] = 0;
		i++;
	}
}

void	raycast_init(t_game *game)
{
	if (!check_player(game))
		return (free_all(game, "Error player pov\n"));
	game->posx = game->map.posx + 0.5;
	game->posy = game->map.posy + 0.5;
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->img = NULL;
	game->win = NULL;
	game->a = false;
	game->d = false;
	game->s = false;
	game->w = false;
	game->left = false;
	game->right = false;
	game->shift = false;
	game->speed = 0.07;
	game->rotspeed = 0.05;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free_all(game, "Error mlx init"));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		return (free_all(game, "Error mlx window"));
}
