/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:15:05 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 15:35:13 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <engine.h>
#include <parser.h>
#include <utils.h>
#include <cub3d.h>

/*
** Initialized game struct
*/

static t_win g_win = {
	.x = 0,
	.y = 0,
	.i = 0,
	.score = 0,
	.health = 1,
	.key = {
		.up = 0,
		.left = 0,
		.down = 0,
		.right = 0,
		.rot_l = 0,
		.rot_r = 0,
		.open = 0,
		.crouch = 0,
		.shoot = 0
	},
	.color = {
		.a = 0,
		.r = 0,
		.g = 0,
		.b = 0,
		.c_color = 0xFF000000,
		.f_color = 0xFF000000,
		.spr_i = 0
	},
	.pos = {
		.x = 0,
		.y = 0,
		.dir_x = 0,
		.dir_y = 0,
		.plane_x = 0,
		.plane_y = 0
	},
	.mov = {
		.m_speed = MOV_SPEED,
		.r_speed = ROT_SPEED
	}
};

/*
** Initialize window and image
**
** @param  t_win *win allocated global window structure
** @return void
*/

static void	init_win(t_img *img, t_win *win)
{
	img->img = mlx_new_image(win->mlx, win->x, win->y);
	img->img = mlx_new_image(win->mlx, win->x, win->y);
	if (!img->img)
		close_error("Couldn't create image\n");
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		close_error("Couldn't get image data\n");
}

/*
** Set key variable to 0 if released
**
** @param  int   keycode accordingly keycode for the key pressed
** @param  t_win *win    allocated global window structure
** @return int           status code
*/

int			key_release(int keycode, t_win *win)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		win->key.up = 0;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		win->key.down = 0;
	if (keycode == KEY_A)
		win->key.left = 0;
	if (keycode == KEY_D)
		win->key.right = 0;
	if (keycode == KEY_LEFT)
		win->key.rot_l = 0;
	if (keycode == KEY_RIGHT)
		win->key.rot_r = 0;
	if (keycode == KEY_SHIFT)
		win->key.crouch = 0;
	return (0);
}

/*
** Set key variable to 1 if pressed
**
** @param  int   keycode accordingly keycode for the key pressed
** @param  t_win *win    allocated global window structure
** @return int           status code
*/

int			key_press(int keycode, t_win *win)
{
	if (keycode == KEY_ESC)
		close_win(win);
	if (keycode == KEY_W || keycode == KEY_UP)
		win->key.up = 1;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		win->key.down = 1;
	if (keycode == KEY_A)
		win->key.left = 1;
	if (keycode == KEY_D)
		win->key.right = 1;
	if (keycode == KEY_LEFT)
		win->key.rot_l = 1;
	if (keycode == KEY_RIGHT)
		win->key.rot_r = 1;
	if (keycode == KEY_E)
		win->key.open = !win->key.open;
	if (keycode == KEY_SHIFT)
		win->key.crouch = 1;
	if (keycode == KEY_SPACE)
		win->key.shoot = !win->key.shoot;
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
		if (argc == 3 && (ft_strncmp(argv[2], "--save", 6) == 0))
			g_win.save = 1;
		else
			close_error("Missing parameters\n");
	}
	g_win.mlx = mlx_init();
	if (!g_win.mlx)
		close_error("Couldn't initialize window\n");
	parse_file(argv[1], &g_win);
	g_win.mlx_win = mlx_new_window(g_win.mlx, g_win.x, g_win.y, "cub3D");
	if (!g_win.mlx_win)
		close_error("Couldn't open window\n");
	init_win(&g_win.img[0], &g_win);
	init_win(&g_win.img[1], &g_win);
	mlx_hook(g_win.mlx_win, 2, (1L << 0), key_press, &g_win);
	mlx_hook(g_win.mlx_win, 3, (1L << 1), key_release, &g_win);
	mlx_hook(g_win.mlx_win, 17, 0L, close_win, &g_win);
	mlx_loop_hook(g_win.mlx, render_next_frame, &g_win);
	mlx_loop(g_win.mlx);
	return (0);
}
