/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:15:05 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/22 10:11:45 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils.h>
#include <parser.h>
#include <engine.h>
#include <cub3d.h>

/*
** Initialize window and image
**
** @param  t_win *win allocated global window structure
** @return void
*/

static void	init_win(t_win *win)
{
	win->mlx = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx, win->x, win->y, "cub3D");
	win->img.img = mlx_new_image(win->mlx, win->x, win->y);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
}

/*
** Set key variable to 0 if released
**
** @param  int   keycode accordingly keycode for the key pressed
** @param  t_win *win    allocated global window structure
** @return int           status code
*/

int 		key_release(int keycode, t_win *win)
{
	if (keycode == KEY_ESC)
		close_key(keycode, win);
	if (keycode == KEY_W || keycode == KEY_UP)
		win->key.up = 0;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		win->key.down = 0;
	if (keycode == KEY_A || keycode == KEY_LEFT)
		win->key.left = 0;
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		win->key.right = 0;
	if (keycode == KEY_Q)
		win->key.rot_l = 0;
	if (keycode == KEY_E)
		win->key.rot_r = 0;
	return (0);
}

/*
** Set key variable to 1 if pressed
**
** @param  int   keycode accordingly keycode for the key pressed
** @param  t_win *win    allocated global window structure
** @return int           status code
*/

int 		key_press(int keycode, t_win *win)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		win->key.up = 1;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		win->key.down = 1;
	if (keycode == KEY_A || keycode == KEY_LEFT)
		win->key.left = 1;
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		win->key.right = 1;
	if (keycode == KEY_Q)
		win->key.rot_l = 1;
	if (keycode == KEY_E)
		win->key.rot_r = 1;
	return (0);
}

/*
** Main
**
** @param  int  argc   number of params
** @param  char **argv 2D array string of params
** @return int         status code
*/

int			main(int argc, char **argv)
{
	t_win	win;

	if (argc != 2){
		if (argc == 3 && (ft_strncmp(argv[3], "--save", 6) == 0))
		{
			write(1, "Saved\n", 6);
			exit (EXIT_SUCCESS);
		}
		write(1, "Error\n", 6);
		exit (EXIT_FAILURE);
	}
	parse_file(argv[1], &win);
	init_win(&win);
	init_pos(&win);
	mlx_hook(win.mlx_win, 2, (1L<<0), key_press, &win);
	mlx_hook(win.mlx_win, 3, (1L<<1), key_release, &win);
	mlx_hook(win.mlx_win, 17, 0L, close_win, &win);
	mlx_loop_hook(win.mlx, &render_next_frame, &win);
	mlx_loop(win.mlx);
	return (0);
}
