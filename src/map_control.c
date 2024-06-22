/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:11:59 by eozdur            #+#    #+#             */
/*   Updated: 2024/03/05 10:21:24 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	map_read(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	game->map.fd = open(game->map.map_name, O_RDONLY);
	if (game->map.fd == -1)
		free_all(game, "Error open file");
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.map_h + 1));
	if (!game->map.map)
		free_all(game, "Error malloc");
	while (1)
	{
		line = get_next_line(game->map.fd);
		if (!line)
			break ;
		game->map.map[i] = ft_strdup(line);
		i++;
		free(line);
	}
	game->map.map[i] = NULL;
	if (i == 0)
		free_all(game, "Error map is empty");
	close(game->map.fd);
}

void	find_size_map(t_game *game)
{
	int		y;
	char	*line;

	y = 0;
	game->map.fd = open(game->map.map_name, O_RDONLY);
	if (game->map.fd == -1)
		free_all(game, "Error open file\n");
	while (1)
	{
		line = get_next_line(game->map.fd);
		if (!line)
			break ;
		y++;
		free(line);
	}
	game->map.map_h = y;
	close(game->map.fd);
}

void	map_control(t_game *game)
{
	find_size_map(game);
	map_read(game);
	map_parse(game);
	check_info(game);
	take_info(game);
	skip_spaces(game, game->map.endofinfo);
	map_check(game);
	path_finder(game, game->map.posy, game->map.posx);
}

void	path_finder(t_game *game, int y, int x)
{
	if (x < 0 || y < 0 || y >= (game->map.real_height)
		|| game->map.tmp_map[y][x] == ' ' || game->map.tmp_map[y][x] == '\0')
	{
		free_all(game, "Invalid path\n");
	}
	if (game->map.tmp_map[y][x] == '1')
	{
		return ;
	}
	game->map.tmp_map[y][x] = '1';
	path_finder(game, y, x - 1);
	path_finder(game, y - 1, x);
	path_finder(game, y, x + 1);
	path_finder(game, y + 1, x);
}

int	check_line_dir(char *map, int i)
{
	char	c;

	while (map[i] != '\0')
	{
		c = map[i];
		if (ft_strncmp(map, "SO ", 3) == 0)
			return (1);
		else if (ft_strncmp(map, "NO ", 3) == 0)
			return (1);
		else if (ft_strncmp(map, "EA ", 3) == 0)
			return (1);
		else if (ft_strncmp(map, "WE ", 3) == 0)
			return (1);
		else if (ft_strncmp(map, "F ", 2) == 0)
			return (1);
		else if (ft_strncmp(map, "C ", 2) == 0)
			return (1);
		else if (c == '\n' || c == ' ')
			i++;
		else if (c == '\0')
			return (1);
		else
			return (0);
	}
	return (1);
}
