/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:33:01 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/20 13:31:43 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_file_format(char *arg)
{
	int	len;
	int	error;

	error = 0;
	len = ft_strlen(arg);
	if (len < 5)
	{
		ft_printf("Argument must be a .ber file\n");
		return (-1);
	}
	if (arg[len - 1] != 'r')
		error = 1;
	if (arg[len - 2] != 'e')
		error = 1;
	if (arg[len - 3] != 'b')
		error = 1;
	if (arg[len - 4] != '.')
		error = 1;
	if (error == 1)
	{	
		ft_printf("Argument must be a .ber file\n");
		return (-1);
	}
	return (0);
}

int	ft_check_file(char *arg)
{
	int	fd;

	if (ft_check_file_format(arg) == -1)
		return (-1);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		ft_printf("File not found\n");
	return (fd);
}

int	main(int ac, char **av)
{
	int			fd;
	char		**map_array;
	t_map		*map;
	t_mapcoord	mapc;

	map = 0;
	if (ac != 2)
		return (0);
	fd = ft_check_file(av[1]);
	if (fd == -1 || ft_file_to_lst(fd, &mapc, &map) == -1)
		return (-1);
	close(fd);
	map_array = ft_map_array(map, mapc.linem);
	if (!map_array)
		return (-1);
	fd = ft_check_map(map_array, &mapc);
	if (fd != 3)
	{
		ft_error_type(fd);
		return (-1);
	}
	if (ft_pathfinding_utils(&mapc, map_array) == -1)
		return (-1);
	show_map(map_array, mapc);
	return (0);
}