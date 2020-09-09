#include "mlx_int.h"
#include <X11/Xlib.h>

int	mlx_get_screen_size(t_xvar *xvar, int *sizex, int *sizey)
{
	Display	*d;
	Screen	*s;

	(void)xvar;
	d = XOpenDisplay(NULL);
	s = DefaultScreenOfDisplay(d);
	*sizex = s->width;
	*sizey = s->height;
	XCloseDisplay(d);
	return (0);
}