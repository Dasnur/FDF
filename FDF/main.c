#include "fdf.h"

double		new_x_rot(double oldx, double oldy)
{
	double	xnew;

	xnew = oldx * 0.9848 - oldy * 0.1736;
	//xnew = oldx * 0.866 - oldy * 0.5;
	//xnew = oldx * 0 - oldy * 1;
	return (xnew);
}

double		new_y_rot(double oldx, double oldy)
{
	double ynew;

	ynew = oldx * 0.1736 + oldy * 0.9848;
	//ynew = oldx * 0.5 + oldy * 0.866;
	//ynew = oldx * 1 - oldy * 0;
	return (ynew);
}

int		turn_left_30(int key, void *param)
{
	int		j;
	int		i;
	int		x;
	int		y;
	double		xnew;
	double		ynew;
	double		znew;
	double		count;
	double		oy;
	double		ox;
	int			flag;

	t_param	*p;
	x =500;
	y = 300;
	j = 0;
	flag = 1;
	count = 0;
	double	k = 0;
	double	b = 0;
	double	k1 = 0;
	double	b1 = 0;
	i = 0;
	p = (t_param*)param;
	if (key == 65307)
		exit;
	if (key == 105)
	{
		mlx_clear_window(p->conn, p->win);
		while (j < p->endj)
		{
			i = 0;
			while (i < p->endi)
			{
				xnew = p->coord[j][i].xcoord * get_cos(0.785398) - p->coord[j][i].ycoord * get_sin(0.785398);
				ynew = p->coord[j][i].xcoord * get_sin(0.785398) + p->coord[j][i].ycoord * get_cos(0.785398);
				ynew = ynew * get_cos(0.959931) + (p->coord[j][i].zcoord * -1 * get_sin(0.959931));
				znew = ynew * get_sin(0.959931) + (p->coord[j][i].zcoord * get_cos(0.959931));
				if (i > 0)
				{
					k = (ynew - p->coord[j][i - 1].ycoord) / (xnew - p->coord[j][i - 1].xcoord);
					b = ynew - k * xnew;
				}
				if (j > 0)
				{
					k1 = (ynew - p->coord[j - 1][i].ycoord) / (xnew - p->coord[j - 1][i].xcoord);
					b1 = ynew - k1 * xnew;
				}
				while (i >= 0 && i < p->endi && j >= 0 && j < p->endj && count < 5)
				{
					if (i > 0  && (p->coord[j][i - 1].xcoord + count) *p->size + x < (xnew *p->size + x) && (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y < ynew *p->size + y)
					{
						if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count > 0.5 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] == p->nbrs[j][i - 1] && p->nbrs[j][i] > 1 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count < 0.5 && p->nbrs[j][i - 1] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count > 0.7 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count < 0.3 && p->nbrs[j][i - 1] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] < 0 && p->nbrs[j][i] == p->nbrs[j][i - 1])
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > 0 && p->nbrs[j][i] == p->nbrs[j][i - 1])
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFFDD00);
					}
					if (j > 0 && (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y < ynew *p->size + y && (p->coord[j - 1][i].xcoord - count) *p->size + x > xnew *p->size + x)
					{
						if (p->nbrs[j][i] == p->nbrs[j - 1][i] && p->nbrs[j][i] > 1 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count < 0.5 && p->nbrs[j - 1][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] > p->nbrs[j - 1][i] && count > 0.5 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win,  (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 *(p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count > 0.9 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win,  (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > p->nbrs[j - 1][i] && count < 0.2 && p->nbrs[j - 1][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] < 0 && (p->nbrs[j][i] == p->nbrs[j - 1][i]))
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > 0 && (p->nbrs[j][i] == p->nbrs[j - 1][i]))
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else
					 		mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 *(p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFFDD00);
						//  printf("x->%f\n", (p->coord[j - 1][i].xcoord - count) *p->size + x);
						//  printf("y-->%f\n",(k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y );
						//  printf("oldx%f\n", p->coord[j - 1][i].xcoord *p->size + x);
						//  printf("oldy%f\n", p->coord[j - 1][i].ycoord *p->size + y);
						//  printf("reallyy-->%f\n",  ynew *p->size + y);
						//  printf("realyx->%f\n", xnew *p->size + x);
					}
					count += 0.01;
				}
				p->coord[j][i].xcoord = xnew;
				p->coord[j][i].ycoord = ynew;
				p->coord[j][i].zcoord = znew;
				i++;
				count = 0;
			}
			j++;
		}
	}
	if (key == 97)
	{
		// if (p->flag2 == 1)
		// {
		// 	while (j < p->endj)
		// 	{
		// 		i = 0;
		// 		while (i < p->endi)
		// 		{
		// 			//printf("-->%d\n", p->flag2);
		// 			p->coord[j][i].xcoord = p->coord[j][i].xcoord;
		// 			p->coord[j][i].ycoord = p->coord[j][i].ycoord;
		// 			p->coord[j][i].zcoord = p->coord[j][i].zcoord;
		// 			//printf("-->%f\n", p->coord[j][i].xcoord);
		// 			//printf("-->%d\n", j);
		// 			i++;
		// 		}
		// 		j++;
		// 	}
		// 	p->flag2 = 0;
		// 	i = 0;
		// 	j = 0;
		// }
		mlx_clear_window(p->conn, p->win);
		while (j < p->endj)
		{
			i = 0;
			while (i < p->endi)
			{
				xnew = p->coord[j][i].xcoord * get_cos(p->angle_rad_r) - p->coord[j][i].ycoord * get_sin(p->angle_rad_r);
				ynew = p->coord[j][i].xcoord * get_sin(p->angle_rad_r) + p->coord[j][i].ycoord * get_cos(p->angle_rad_r);
				mlx_pixel_put(p->conn, p->win, (xnew *p->size + x), (ynew *p->size + y), 0xFFDD00);
				//printf("realx-->%f\n", (xnew *p->size + x));
				//printf("realy-->%f\n", (ynew *p->size + y));
				if (i > 0)
				{
					k = (ynew - p->coord[j][i - 1].ycoord) / (xnew - p->coord[j][i - 1].xcoord);
					b = ynew - k * xnew;
				}
				if (j > 0)
				{
					k1 = (ynew - p->coord[j - 1][i].ycoord) / (xnew - p->coord[j - 1][i].xcoord);
					b1 = ynew - k1 * xnew;
				}
				while (i >= 0 && i < p->endi && j >= 0 && j < p->endj && count < 5)
				{
					if (i > 0 && (p->coord[j][i - 1].xcoord + count) *p->size + x < xnew *p->size + x)
					{
						if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count > 0.7 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] == p->nbrs[j][i - 1] && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count < 0.7 && p->nbrs[j][i - 1] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count > 0.7 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count < 0.7 && p->nbrs[j][i - 1] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] == p->nbrs[j][i - 1] && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFFDD00);
					}
					if (j > 0 && ((k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y < ynew *p->size + y) && ((k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y > p->coord[j - 1][i].ycoord *p->size + y))
					{
						if (p->nbrs[j][i] > p->nbrs[j - 1][i] && count > 0.5)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] == p->nbrs[j - 1][i] && p->nbrs[j][i] > 1)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count < 0.1)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count < 0.1 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0x1100FC);
						else
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFFDD00);
						// printf("-->%f\n", (p->coord[j - 1][i].ycoord - count) *p->size + x);
						// printf("-->%f\n", (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y);
						// printf("b1-->%f\n", b1);
						// printf("k1-->%f\n", k1);
						// printf("ynew%f\n", ynew);
						// printf("yold%f\n", p->coord[j - 1][i].ycoord + count);
					}
					count += 0.01;
				}
				p->coord[j][i].xcoord = xnew;
				p->coord[j][i].ycoord = ynew;
				count = 0;
				i++;
			}
			j++;
		}
		p->flag2 = 0;
		//p->angle_rad_r = p->angle_rad_r + 0.174533;
	}
	if (key == 119)
	{
		// if (p->flag2 == 0)
		// {
		// 	while (j < p->endj)
		// 	{
		// 		i = 0;
		// 		while (i < p->endi)
		// 		{
		// 			//printf("-->%d\n", p->flag2);
		// 			p->coord[j][i].xcoord = p->coord[j][i].xcoord;
		// 			p->coord[j][i].ycoord = p->coord[j][i].ycoord;
		// 			p->coord[j][i].zcoord = p->coord[j][i].zcoord;
		// 			//printf("-->%f\n", p->coord[j][i].xcoord);
		// 			//printf("-->%d\n", j);
		// 			i++;
		// 		}
		// 		j++;
		// 	}
		// 	p->flag2 = 1;
		// 	i = 0;
		// 	j = 0;
		// }
		//p->coord = p->coord;
		mlx_clear_window(p->conn, p->win);
		while (j < p->endj)
		{
			i = 0;
			while (i < p->endi)
			{
				//xnew = (p->coord[j][i].xcoord) * 0.866 - (p->coord[j][i].ycoord) * 0.5;
				xnew = p->coord[j][i].xcoord;
				printf("realyx->%f\n", xnew *p->size + x);
				//ynew = new_x_rot(p->coord[j][i].ycoord, p->coord[j][i].zcoord);
				//znew = new_y_rot(p->coord[j][i].ycoord, p->coord[j][i].zcoord);
				// ynew = p->coord[j][i].zcoord * get_sin(p->angle_rad) + p->coord[j][i].ycoord * get_cos(p->angle_rad);
				// znew = p->coord[j][i].zcoord * get_cos(p->angle_rad);
				if (p->flag1 == 1)
				{			
					// ynew = -1 * p->coord[j][i].ycoord * get_cos(p->angle_rad_w) + (p->coord[j][i].zcoord *  get_sin(p->angle_rad_w));
					// znew = -1 * p->coord[j][i].ycoord * get_sin(p->angle_rad_w) + (-1 * p->coord[j][i].zcoord * get_cos(p->angle_rad_w));
					ynew = p->coord[j][i].ycoord * get_cos(p->angle_rad_w) + (p->coord[j][i].zcoord * -1 * get_sin(p->angle_rad_w));
					znew = p->coord[j][i].ycoord * get_sin(p->angle_rad_w) + (p->coord[j][i].zcoord * get_cos(p->angle_rad_w));
				}
				else
				{
					ynew = p->coord[j][i].ycoord * get_cos(p->angle_rad_w) + (p->coord[j][i].zcoord * -1 * get_sin(p->angle_rad_w));
					znew = p->coord[j][i].ycoord * get_sin(p->angle_rad_w) + (p->coord[j][i].zcoord * get_cos(p->angle_rad_w));
				}
				printf("reallyy-->%f\n",  ynew *p->size + y);
				//znew = p->coord[j][i].zcoord * get_cos(p->angle_rad_w);
				mlx_pixel_put(p->conn, p->win, (p->coord[j][i].xcoord *p->size + x), (ynew *p->size + y), 0xFFDD00);
				if (i > 0)
				{
					if (xnew - p->coord[j][i - 1].xcoord == 0.0)
					{
						k = 0;
					}
					else
						k = (ynew - p->coord[j][i - 1].ycoord) / (xnew - p->coord[j][i - 1].xcoord);
					b = ynew - k * xnew;
				}
				if (j > 0)
				{
					if (xnew - p->coord[j - 1][i].xcoord == 0.0)
					{
						k1 = (xnew - p->coord[j - 1][i].xcoord) / (ynew - p->coord[j - 1][i].ycoord);
						b1 = xnew - k1 * ynew;
					}
					else
					{
						k1 = (ynew - p->coord[j - 1][i].ycoord) / (xnew - p->coord[j - 1][i].xcoord);
						b1 = ynew - k1 * xnew;
					}
				}
				while (i >= 0 && i < p->endi && j >= 0 && j < p->endj && count < 5)
				{
					if (i > 0  && (p->coord[j][i - 1].xcoord + count) * p->size + x < (p->coord[j][i].xcoord *p->size + x))
					{
						if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count > 0.5 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] == p->nbrs[j][i - 1] && p->nbrs[j][i] > 1 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count < 0.5 && p->nbrs[j][i - 1] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count > 0.7 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count < 0.3 && p->nbrs[j][i - 1] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] < 0 && p->nbrs[j][i] == p->nbrs[j][i - 1])
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > 0 && p->nbrs[j][i] == p->nbrs[j][i - 1])
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFC0000);
						else
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) *p->size + x, (k * (p->coord[j][i - 1].xcoord + count) + b) *p->size + y, 0xFFDD00);
					}
					if (j > 0 && ((p->coord[j - 1][i].xcoord - count) *p->size + x > p->coord[j][i].xcoord *p->size + x))
					{
						if (p->nbrs[j][i] == p->nbrs[j - 1][i] && p->nbrs[j][i] > 1 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count < 0.5 && p->nbrs[j - 1][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] > p->nbrs[j - 1][i] && count > 0.5 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win,  (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 *(p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count > 0.9 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win,  (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > p->nbrs[j - 1][i] && count < 0.2 && p->nbrs[j - 1][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] < 0 && (p->nbrs[j][i] == p->nbrs[j - 1][i]))
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0x1100FC);
						else if (p->nbrs[j][i] > 0 && (p->nbrs[j][i] == p->nbrs[j - 1][i]))
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFC0000);
						else
					 		mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) *p->size + x, (k1 *(p->coord[j - 1][i].xcoord - count) + b1) *p->size + y, 0xFFDD00);
						// printf("x->%f\n", (p->coord[j - 1][i].xcoord - count) *p->size + x);
						// printf("y-->%f\n",(k1 * (p->coord[j - 1][i].xcoord - count) + b1) *p->size + y );
						// printf("oldx%f\n", p->coord[j - 1][i].xcoord *p->size + x);
						// printf("oldy%f\n", p->coord[j - 1][i].ycoord *p->size + y);
						// printf("reallyy-->%f\n",  ynew *p->size + y);
						// printf("realyx->%f\n", xnew *p->size + x);
					}
					count += 0.01;
				}
				p->coord[j][i].xcoord = xnew;
				p->coord[j][i].ycoord = ynew;
				p->coord[j][i].zcoord = znew;
				count = 0;
				i++;
			}
			j++;
		}
		//p->angle_rad_w = p->angle_rad_w + 0.174533;
	}
	double	lengthi;
	double	lengthj;
	double	dxi;
	double	dyi;;
	double	dxj;
	double	dyj;
	if (key == 61)
	{
		count = 0;
		p->size = p->size + 5;
		mlx_clear_window(p->conn, p->win);
		ft_bzero((void *)p->im.img_data, p->height * p->weight * 4);
		//mlx_destroy_image(p->conn, p->im.p_img);
		while (j < p->endj)
		{
			i = 0;
			while (i < p->endi)
			{
				if (i > 0)
				{
					dxi = p->coord[j][i].xcoord - p->coord[j][i -  1].xcoord;
					dyi = p->coord[j][i].ycoord - p->coord[j][i -  1].ycoord;
					//lengthj = sqrt(stepen(p->coord[j][i].ycoord - p->coord[j - 1][i].ycoord, 2) + stepen(p->coord[j][i].xcoord - p->coord[j - 1][i].xcoord, 2));
					lengthi = sqrt(stepen(p->coord[j][i].xcoord - p->coord[j][i - 1].xcoord, 2) + stepen(p->coord[j][i].ycoord - p->coord[j][i - 1].ycoord, 2));
					while ((p->coord[j][i - 1].xcoord + count) <= p->coord[j][i].xcoord)
					{
						if (p->nbrs[j][i] > p->nbrs[j][i - 1] && p->clr.red > 0)
							p->clr.green -= 2;
						if (p->nbrs[j][i] < p->nbrs[j][i - 1])
							p->clr.green += 2;
						fill_pix(p, (p->coord[j][i - 1].xcoord + count) * p->size + x, (p->coord[j][i - 1].ycoord + dyi * (p->coord[j][i - 1].xcoord + count - p->coord[j][i - 1].xcoord) / dxi) * p->size + y);
						count += 0.01;
					}
				}
				if (j > 1)
				{
					dxj = p->coord[j][i].xcoord - p->coord[j - 1][i].xcoord;
					dyj = p->coord[j][i].ycoord - p->coord[j - 1][i].ycoord;
					count = 0;
					while  (p->coord[j - 1][i].xcoord - count > p->coord[j][i].xcoord) 
					{
						if (p->nbrs[j][i] > p->nbrs[j - 1][i] && p->clr.red > 0)
							p->clr.green -= 2;
						if (p->nbrs[j][i] < p->nbrs[j - 1][i])
							p->clr.green += 2;
						fill_pix(p, (p->coord[j - 1][i].xcoord + count) * p->size + x, (p->coord[j - 1][i].ycoord + dyj * (p->coord[j - 1][i].xcoord + count - p->coord[j - 1][i].xcoord) / dxj) * p->size + y);
						count += 0.01;
					}
				}
				count = 0;
				i++;
			}
			p->clr.green = 221;
			j++;
		}
		mlx_put_image_to_window(p->conn, p->win, p->im.p_img, 0, 0);
	}
	if (key == 45)
	{
		count = 0;
		p->size = p->size - 5;
		mlx_clear_window(p->conn, p->win);
		ft_bzero((void *)p->im.img_data, p->height * p->weight * 4);
		//mlx_destroy_image(p->conn, p->im.p_img);
		while (j < p->endj)
		{
			i = 0;
			while (i < p->endi)
			{
				if (i > 0)
				{
					dxi = p->coord[j][i].xcoord - p->coord[j][i -  1].xcoord;
					dyi = p->coord[j][i].ycoord - p->coord[j][i -  1].ycoord;
					//lengthj = sqrt(stepen(p->coord[j][i].ycoord - p->coord[j - 1][i].ycoord, 2) + stepen(p->coord[j][i].xcoord - p->coord[j - 1][i].xcoord, 2));
					lengthi = sqrt(stepen(p->coord[j][i].xcoord - p->coord[j][i - 1].xcoord, 2) + stepen(p->coord[j][i].ycoord - p->coord[j][i - 1].ycoord, 2));
					while ((p->coord[j][i - 1].xcoord + count) < p->coord[j][i].xcoord)
					{
						if (p->nbrs[j][i] > p->nbrs[j][i - 1] && p->clr.red > 0)
							p->clr.green -= 2;
						if (p->nbrs[j][i] < p->nbrs[j][i - 1])
							p->clr.green += 2;
						fill_pix(p, (p->coord[j][i - 1].xcoord + count) * p->size + x, (p->coord[j][i - 1].ycoord + dyi * (p->coord[j][i - 1].xcoord + count - p->coord[j][i - 1].xcoord)) * p->size + y);
						count += 0.01;
					}
				}
				count = 0;
				i++;
			}
			j++;
		}
		mlx_put_image_to_window(p->conn, p->win, p->im.p_img, 0, 0);
	}
	ft_putnbr(key);
	if (p->angle_rad_w > 3.2)
	{
		p->angle_rad_w = 0.174533;
	}
	if (p->angle_rad_r > 1.57)
	{
		p->angle_rad_r = 0.174533;
	}
	//printf("%f\n", p->angle_rad_w);
	printf("%s\n\n\n", "------------------------");
	return (0);
}

int		draw_image(t_param *p)
{
	int		i;
	int		j;
	t_coord	**coord;
	int x = 500;
	int y = 300;
	int	count = 0;
	t_param *ptr_p;

	coord = (t_coord **)malloc(sizeof(t_coord *) *11600);
	j = 0;
	i = 0;
	while (j < p->endj)
	{
		coord[j] = (t_coord *)malloc(sizeof(t_coord) * 11600);
		i = 0;
		while (i < p->endi)
		{
			coord[j][i].ycoord = j; 
			coord[j][i].xcoord = i;
			coord[j][i].zcoord = p->nbrs[j][i];
			fill_pix(p, x + i * p->size, y + j * p->size);
			while (i >= 0 && i < p->endi && j >= 0 && j < p->endj && count < p->size)
			{
				if (i < p->endi - 1)
					fill_pix(p, x + i * p->size + count, y + j * p->size);
				if (j < p->endj - 1)
					fill_pix(p, x + i * p->size, y + j * p->size + count);
				count += 1;
			}
			count = 0;
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(p->conn, p->win, p->im.p_img, 0, 0);
	p->coord = coord;
	ptr_p = (void *)p;
	mlx_hook(p->win, 2, 1L << 0, turn_left_30, ptr_p);
	//mlx_pixel_put(conn_ptr, win_ptr_main, 250, 250, 0xFFFFFF);
	//mlx_destroy_image(p->conn, p->im.p_img);;
	mlx_loop(p->conn);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	**line;
	int		**nbrs;
	t_param	p;

	nbrs = (int **)malloc(sizeof(int *) * 11600);
	line = (char**)malloc(sizeof(char *));
	fd = open(argv[1], O_RDONLY);
	reading_map(fd, line, nbrs, &p);
	init_p(&p);
	draw_image(&p);
}