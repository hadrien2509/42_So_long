/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:45:35 by hgeissle          #+#    #+#             */
/*   Updated: 2023/02/21 16:31:11 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_put_objects(t_mapcoord *mapc, t_rendering *ren, char copy)
{
	int	a;
	int	x;
	int	y;

	x = (mapc->x + 0.4) * 128;
	y = (mapc->y + 0.4) * 160;
	if (copy == 'P')
		mlx_put_image_to_window(ren->mlx, ren->win, ren->imgd, x, y);
	if (copy == 'C')
		mlx_put_image_to_window(ren->mlx, ren->win, ren->imgc, x, y);
	if (copy == 'E')
	{
		x = (mapc->x + 0.1) * 128;
		mlx_put_image_to_window(ren->mlx, ren->win, ren->imge, x, y);
	}
}

void	ft_fixed_tiles(char **map_array, t_mapcoord *mapc, t_rendering *ren)
{
	char	copy;
	int		x;
	int		y;

	ft_create_img(ren, mapc, map_array);
	mapc->y = 0;
	while (mapc->y < mapc->linem)
	{
		mapc->x = 0;
		while (mapc->x < mapc->colm)
		{
			x = mapc->x * 128;
			y = mapc->y * 160;
			copy = map_array[mapc->y][mapc->x];
			if (copy == '1')
				mlx_put_image_to_window(ren->mlx, ren->win, ren->img1, x, y);
			if (copy == '0' || copy == 'E' || copy == 'C' || copy == 'P')
				mlx_put_image_to_window(ren->mlx, ren->win, ren->img0, x, y);
			ft_put_objects(mapc, ren, copy);
			mapc->x++;
		}
		mapc->y++;
	}
}

void	ft_move_tiles(t_mapcoord *mapc, t_rendering ren, t_vars *v, char **ar)
{
	v->mapc = *mapc;
	v->ren = ren;
	v->map_array = ar;
	v->lines = v->mapc.linem;
	v->cols = v->mapc.colm;
	v->moves = 0;
	v->end = 0;
	ft_create_player_img(&v->ren, &v->mapc, v->map_array);
	ft_text_box(v, "Collect all the bags !", 0);
	mlx_hook(v->ren.win, 17, 0, ft_exit, v);
	mlx_key_hook(v->ren.win, key_hook, v);
	mlx_loop(v->ren.mlx);
}

void	show_map(char **map_array, t_mapcoord mapc)
{
	t_rendering		ren;
	t_vars			vars;
	int				width;
	int				height;

	width = mapc.colm * 128;
	height = mapc.linem * 160;
	ren.mlx = mlx_init();
	ren.win = mlx_new_window(ren.mlx, width, height, "So long!");
	ft_fixed_tiles(map_array, &mapc, &ren);
	ft_move_tiles(&mapc, ren, &vars, map_array);
}
