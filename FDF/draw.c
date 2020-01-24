#include "fdf.h"

void		fill_pix(t_param *p, int x, int y)
{
	p->im.img_data[(x) * 4 + (y) * 4 * p->height] = p->clr.blue;
	p->im.img_data[(x) * 4 + (y) * 4 * p->height + 1] = p->clr.green;
	p->im.img_data[(x) * 4 + (y) * 4 * p->height + 2] = p->clr.red;
}