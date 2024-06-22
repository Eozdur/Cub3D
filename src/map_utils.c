/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:15:12 by eozdur            #+#    #+#             */
/*   Updated: 2024/03/05 10:51:12 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	free_all(t_game *game, char *str)
{
	if (game->map.map != NULL)
		free_array(game->map.map, 0);
	if (game->map.ceiling != NULL)
		free(game->map.ceiling);
	if (game->map.floor != NULL)
		free(game->map.floor);
	if (game->map.real_map != NULL)
		free_array(game->map.real_map, 0);
	if (game->map.tmp_map != NULL)
		free_array(game->map.tmp_map, 0);
	free_array(game->map.directions, 4);
	free_array(game->map.textures, 4);
	free_array(game->map.color_path, 2);
	free_array(game->map.rgb_color, 2);
	ft_destroy_mlx(game);
	free_ray(game);
	printf("%s\n", str);
	exit(1);
}

void	ft_destroy_mlx(t_game *game)
{
	if (game->north != NULL && game->north->img != NULL)
		mlx_destroy_image(game->mlx, game->north->img);
	if (game->south != NULL && game->south->img != NULL)
		mlx_destroy_image(game->mlx, game->south->img);
	if (game->west != NULL && game->west->img != NULL)
		mlx_destroy_image(game->mlx, game->west->img);
	if (game->east != NULL && game->east->img != NULL)
		mlx_destroy_image(game->mlx, game->east->img);
	if (game->img != NULL && game->img->img != NULL)
		mlx_destroy_image(game->mlx, game->img->img);
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
}

void	free_ray(t_game *game)
{
	if (game->north != NULL)
		free(game->north);
	if (game->south != NULL)
		free(game->south);
	if (game->west != NULL)
		free(game->west);
	if (game->east != NULL)
		free(game->east);
	if (game->img != NULL)
		free(game->img);
}

void	free_array(char **str, int size)
{
	int	i;

	i = 0;
	if (size == 0)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			if (str[i] != NULL)
				free(str[i]);
			i++;
		}
	}
	if (size == 0)
		free(str);
}

int	count_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
