/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:16:13 by eozdur            #+#    #+#             */
/*   Updated: 2024/03/04 12:56:42 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include "cub3d.h"
#include <math.h>
#include <stdlib.h>

int	close_game(t_game *game)
{
	free_all(game, "Game closed");
	return (0);
}

void	get_image_data_addr(t_game *game)
{
	game->north->addr = (int *)mlx_get_data_addr(game->north->img,
			&game->north->bits_per_pixel, &game->north->line_length,
			&game->north->endian);
	game->east->addr = (int *)mlx_get_data_addr(game->east->img,
			&game->east->bits_per_pixel, &game->east->line_length,
			&game->east->endian);
	game->south->addr = (int *)mlx_get_data_addr(game->south->img,
			&game->south->bits_per_pixel, &game->south->line_length,
			&game->south->endian);
	game->west->addr = (int *)mlx_get_data_addr(game->west->img,
			&game->west->bits_per_pixel, &game->west->line_length,
			&game->west->endian);
	if (!game->north->addr || !game->east->addr || !game->south->addr
		|| !game->west->addr)
		free_all(game, "mlx fail");
}

void	init_game_img(t_game *game)
{
	init_direction(game);
	game->img->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img->img)
		free_all(game, "mlx fail");
	game->img->addr = (int *)mlx_get_data_addr(game->img->img,
			&game->img->bits_per_pixel, &game->img->line_length,
			&game->img->endian);
	if (!game->img->addr)
		free_all(game, "mlx fail");
	game->north->img = mlx_xpm_file_to_image(game->mlx, game->map.textures[0],
			&game->north->width, &game->north->height);
	game->east->img = mlx_xpm_file_to_image(game->mlx, game->map.textures[1],
			&game->east->width, &game->east->height);
	game->south->img = mlx_xpm_file_to_image(game->mlx, game->map.textures[2],
			&game->south->width, &game->south->height);
	game->west->img = mlx_xpm_file_to_image(game->mlx, game->map.textures[3],
			&game->west->width, &game->west->height);
	if (!game->north->img || !game->east->img || !game->south->img
		|| !game->west->img)
		free_all(game, "mlx fail");
	check_texture_size(game);
	get_image_data_addr(game);
}

void	check_texture_size(t_game *game)
{
	if (game->north->width > 400 || game->north->height > 400)
		free_all(game, "Texture size is too big");
	if (game->east->width > 400 || game->east->height > 400)
		free_all(game, "Texture size is too big");
	if (game->south->width > 400 || game->south->height > 400)
		free_all(game, "Texture size is too big");
	if (game->west->width > 400 || game->west->height > 400)
		free_all(game, "Texture size is too big");
	return ;
}

void	init_direction(t_game *game)
{
	char	*tmp[4];
	int		i;

	i = 0;
	game->img = malloc(sizeof(t_image));
	game->north = malloc(sizeof(t_image));
	game->south = malloc(sizeof(t_image));
	game->east = malloc(sizeof(t_image));
	game->west = malloc(sizeof(t_image));
	if (!game->img || !game->north || !game->south || !game->east
		|| !game->west)
		free_all(game, "alloc fail");
	while (i < 4)
	{
		tmp[i] = ft_strtrim(game->map.textures[i], "\n");
		if (!tmp[i])
			free_all(game, "alloc fail");
		free(game->map.textures[i]);
		game->map.textures[i] = tmp[i];
		i++;
	}
}
