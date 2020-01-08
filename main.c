/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                   +#+                      */
/*   Created: 2020/01/04 11:15:43 by prmerku        #+#    #+#                */
/*   Updated: 2020/01/08 14:29:42 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <cub3d.h>

static void	init_win(t_win *win)
{
	win->mlx = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx, win->win_x, win->win_y, "cub3D");
	win->img.img = mlx_new_image(win->mlx, win->win_x, win->win_y);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bpp,
			&win->img.llen, &win->img.endian);
}

int			main(int argc, char **argv)
{
	t_win	win;

	if (argc != 2){
		if (argc == 3){
			write(1, "Saved\n", 6);
			return (0);
		}
		perror("Error");
		exit (1);
	}
	parse_file(argv[1], &win);
	init_win(&win);
	mlx_loop_hook(win.mlx, render_next_frame, &win);
	mlx_key_hook(win.mlx_win, close_key, &win);
	//mlx_hook(win.mlx_win, 17, 0L, close, &win);
	mlx_loop(win.mlx);
	return (0);
}
