/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:15:05 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/20 17:14:20 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <cub3d.h>

static void	init_win(t_win *win)
{
	win->mlx = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx, win->x, win->y, "cub3D");
	win->img.img = mlx_new_image(win->mlx, win->x, win->y);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bpp,
									  &win->img.line_len, &win->img.endian);
}

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
	printf("%d\n", keycode);
	return (0);
}

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
	move_pos(win);
	return (0);
}

int			main(int argc, char **argv)
{
	t_win	win;

	if (argc != 2){
		if (argc == 3 && (ft_strncmp(argv[3], "--save", 6) == 0))
		{
			write(1, "Saved\n", 6);
			exit (EXIT_SUCCESS);
		}
		perror("Error");
		exit (EXIT_FAILURE);
	}
	parse_file(argv[1], &win);
	init_win(&win);
	mlx_hook(win.mlx_win, 2, (1L<<0), key_press, &win);
	mlx_hook(win.mlx_win, 3, (1L<<1), key_release, &win);
	mlx_hook(win.mlx_win, 17, 0L, close_win, &win);
	init_pos(&win);
	mlx_loop_hook(win.mlx, &render_next_frame, &win);
	mlx_loop(win.mlx);
	return (0);
}
