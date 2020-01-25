/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:15:05 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/25 09:51:30 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils.h>
#include <parser.h>
#include <engine.h>
#include <cub3d.h>

/*
** Initialized game struct
*/

static t_win g_win = {
	.key = {
		.up = 0,
		.left = 0,
		.down = 0,
		.right = 0,
		.rot_l = 0,
		.rot_r = 0
	},
	.mov = {
		.m_speed = 0.05,
		.r_speed = 0.03
	},
	.color = {
		.a = 0,
		.r = 0,
		.g = 0,
		.b = 0,
		.c_color = 0x0000FF00,
		.f_color = 0x000000FF
	}
};

/*
** Initialize window and image
**
** @param  t_win *win allocated global window structure
** @return void
*/

static void	init_win(t_win *win)
{
	win->mlx_win = mlx_new_window(win->mlx, win->x, win->y, "cub3D");
	if (!win->mlx_win)
		close_error("Couldn't open window\n");
	win->img.img = mlx_new_image(win->mlx, win->x, win->y);
	if (!win->img.img)
		close_error("Couldn't create image\n");
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->img.addr)
		close_error("Couldn't get image data\n");
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
	if (keycode == KEY_ESC)
		close_key(keycode, win);
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
	if (argc != 2)
	{
		if (argc == 3 && (ft_strncmp(argv[3], "--save", 6) == 0))
		{
			write(1, "Saved\n", 6);
			exit (EXIT_SUCCESS);
		}
		write(1, "Error\n", 6);
		exit (EXIT_FAILURE);
	}
	g_win.mlx = mlx_init();
	if (!g_win.mlx)
		close_error("Couldn't initialize window\n");
	parse_file(argv[1], &g_win);
	init_win(&g_win);
	init_pos(&g_win);
	mlx_hook(g_win.mlx_win, 2, (1L<<0), key_press, &g_win);
	mlx_hook(g_win.mlx_win, 3, (1L<<1), key_release, &g_win);
	mlx_hook(g_win.mlx_win, 17, 0L, close_win, &g_win);
	mlx_loop_hook(g_win.mlx, &render_next_frame, &g_win);
	mlx_loop(g_win.mlx);
	return (0);
}
