/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 11:15:43 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/07 10:25:36 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <cub3d.h>

int     close(int keycode, t_env *env)
{
    if (keycode == 53)
    {
        mlx_destroy_window(env->mlx, env->mlx_win);
        exit(0);
    }
    printf("%d\n", keycode);
    return (0);
}

void    my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char    *dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int		render_next_frame(t_env *env)
{
	for (int i = 0; i < 500; i++)
		my_mlx_pixel_put(&env->data, i, 5, 0x00FF0000);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->data.img, 0, 0);
	return (0);
}

int		main(void)
{

	t_env  env;

	env.mlx = mlx_init();
	env.mlx_win = mlx_new_window(env.mlx, 600, 500, "Hello world!");
	env.data.img = mlx_new_image(env.mlx, 600, 500);
	env.data.addr = mlx_get_data_addr(env.data.img, &env.data.bpp, &env.data.llen, &env.data.endian);
	mlx_loop_hook(env.mlx, render_next_frame, &env);
    mlx_hook(env.mlx_win, 2, 1L<<0, close, &env);
	mlx_loop(env.mlx);
}
