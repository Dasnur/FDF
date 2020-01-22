#include "../../minilibx/mlx.h"
#include <fcntl.h>
#include "libft/libft.h"
#include <stdio.h>

typedef struct		s_coord
{
	double		xcoord;
	double		ycoord;
	double		zcoord;
}					t_coord;

typedef struct		s_param
{
	void		*win;
	void		*conn;
	int			endi;
	int			endj;
	int			**nbrs;
	double		angle_rad_w;
	double		angle_rad_r;
	int			flag1;
	int			flag2;
	t_coord			**coord;
	t_coord			**bazis;
}					t_param;

double		stepen(double in, int st)
{
	double	res;

	if (st == 0)
		return ((double)1);
	res = in;
	while (st > 1)
	{
		res = res * in;
		st--;
	}
	return (res);
}

int			fact(int st)
{
	if (st == 1)
		return (1);
	return (st * fact(st - 1));
}

double		get_sin(double rad)
{
	int		i;
	double	res;

	res = 0;
	i = 5;
	while (i > 0)
	{
		res = res + stepen(-1, i - 1) * (stepen(rad, 2 * i - 1) / fact(2 * i - 1));
		i--;
	}
	return (res);
}

double		get_cos(double rad)
{
	int		i;
	double	res;

	res = 0;
	i = 5;
	while (i > 0)
	{
		res = res + stepen(-1, i) * (stepen(rad, 2 * i) / fact(2 * i));
		i--;
	}
	return (1 + res);
}

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
	x = 500;
	y = 300;
	j = 0;
	flag = 1;
	count = 0;
	double	k = 0;
	double	b = 0;
	double	k1 = 0;
	double	b1 = 0;
	p = (t_param*)param;
	if (key == 97)
	{
		mlx_clear_window(p->conn, p->win);
		while (j < p->endj)
		{
			i = 0;
			while (i < p->endi)
			{
				xnew = p->bazis[j][i].xcoord * get_cos(p->angle_rad_r) - p->bazis[j][i].ycoord * get_sin(p->angle_rad_r);
				ynew = p->bazis[j][i].xcoord * get_sin(p->angle_rad_r) + p->bazis[j][i].ycoord * get_cos(p->angle_rad_r);
				mlx_pixel_put(p->conn, p->win, (xnew * 40 + x), (ynew * 40 + y), 0xFFDD00);
				//printf("realx-->%f\n", (xnew * 40 + x));
				//printf("realy-->%f\n", (ynew * 40 + y));
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
					if (i > 0 && (p->coord[j][i - 1].xcoord + count) * 40 + x < xnew * 40 + x)
					{
						if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count > 0.7 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) * 40 + x, (k * (p->coord[j][i - 1].xcoord + count) + b) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] == p->nbrs[j][i - 1] && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) * 40 + x, (k * (p->coord[j][i - 1].xcoord + count) + b) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count < 0.7 && p->nbrs[j][i - 1] > 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) * 40 + x, (k * (p->coord[j][i - 1].xcoord + count) + b) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count > 0.7 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) * 40 + x, (k * (p->coord[j][i - 1].xcoord + count) + b) * 40 + y, 0x1100FC);
						else if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count < 0.7 && p->nbrs[j][i - 1] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) * 40 + x, (k * (p->coord[j][i - 1].xcoord + count) + b) * 40 + y, 0x1100FC);
						else if (p->nbrs[j][i] == p->nbrs[j][i - 1] && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) * 40 + x, (k * (p->coord[j][i - 1].xcoord + count) + b) * 40 + y, 0x1100FC);
						else
							mlx_pixel_put(p->conn, p->win, (p->coord[j][i - 1].xcoord + count) * 40 + x, (k * (p->coord[j][i - 1].xcoord + count) + b) * 40 + y, 0xFFDD00);
					}
					if (j > 0 && ((k1 * (p->coord[j - 1][i].xcoord - count) + b1) * 40 + y < ynew * 40 + y))
					{
						if (p->nbrs[j][i] > p->nbrs[j - 1][i] && count > 0.5)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) * 40 + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] == p->nbrs[j - 1][i] && p->nbrs[j][i] > 1)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) * 40 + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count < 0.1)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) * 40 + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count < 0.1 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) * 40 + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) * 40 + y, 0x1100FC);
						else
							mlx_pixel_put(p->conn, p->win, (p->coord[j - 1][i].xcoord - count) * 40 + x, (k1 * (p->coord[j - 1][i].xcoord - count) + b1) * 40 + y, 0xFFDD00);
						// printf("-->%f\n", (p->coord[j - 1][i].ycoord - count) * 40 + x);
						// printf("-->%f\n", (k1 * (p->coord[j - 1][i].xcoord - count) + b1) * 40 + y);
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
		flag = 0;
		p->angle_rad_r = p->angle_rad_r + 0.174533;
	}
	if (key == 119)
	{
		if (flag == 0)
		{
			while (j < p->endj)
			{
				while (i < p->endi)
				{
					p->bazis[j][i].xcoord = p->coord[j][i].xcoord;
					p->bazis[j][i].ycoord = p->coord[j][i].ycoord;
					p->bazis[j][i].zcoord = p->coord[j][i].zcoord;
					i++;
				}
				j++;
			}
			flag = 1;
			i = 0;
			j = 0;
		}
		//p->bazis = p->coord;
		mlx_clear_window(p->conn, p->win);
		while (j < p->endj)
		{
			i = 0;
			while (i < p->endi)
			{
				//xnew = (p->coord[j][i].xcoord) * 0.866 - (p->coord[j][i].ycoord) * 0.5;
				xnew = p->bazis[j][i].xcoord;
				//ynew = new_x_rot(p->coord[j][i].ycoord, p->coord[j][i].zcoord);
				//znew = new_y_rot(p->coord[j][i].ycoord, p->coord[j][i].zcoord);
				// ynew = p->coord[j][i].zcoord * get_sin(p->angle_rad) + p->coord[j][i].ycoord * get_cos(p->angle_rad);
				// znew = p->coord[j][i].zcoord * get_cos(p->angle_rad);
				if (p->flag1 == 1)
				{			
					// ynew = -1 * p->bazis[j][i].ycoord * get_cos(p->angle_rad_w) + (p->bazis[j][i].zcoord *  get_sin(p->angle_rad_w));
					// znew = -1 * p->bazis[j][i].ycoord * get_sin(p->angle_rad_w) + (-1 * p->bazis[j][i].zcoord * get_cos(p->angle_rad_w));
					ynew = p->bazis[j][i].ycoord * get_cos(p->angle_rad_w) + (p->bazis[j][i].zcoord * -1 * get_sin(p->angle_rad_w));
					znew = p->bazis[j][i].ycoord * get_sin(p->angle_rad_w) + (p->bazis[j][i].zcoord * get_cos(p->angle_rad_w));
				}
				else
				{
					ynew = p->bazis[j][i].ycoord * get_cos(p->angle_rad_w) + (p->bazis[j][i].zcoord * -1 * get_sin(p->angle_rad_w));
					znew = p->bazis[j][i].ycoord * get_sin(p->angle_rad_w) + (p->bazis[j][i].zcoord * get_cos(p->angle_rad_w));
				}
				//printf("-->%f\n",  get_cos(p->angle_rad_w));
				//znew = p->bazis[j][i].zcoord * get_cos(p->angle_rad_w);
				mlx_pixel_put(p->conn, p->win, (p->bazis[j][i].xcoord * 40 + x), (ynew * 40 + y), 0xFFDD00);
				if (i > 0)
				{
					if (xnew - p->bazis[j][i - 1].xcoord == 0.0)
					{
						k = 0;
					}
					else
						k = (ynew - p->bazis[j][i - 1].ycoord) / (xnew - p->bazis[j][i - 1].xcoord);
					b = ynew - k * xnew;
				}
				if (j > 0)
				{
					k1 = (xnew - p->bazis[j - 1][i].xcoord) / (ynew - p->bazis[j - 1][i].ycoord);
					b1 = xnew - k1 * ynew;
				}
				while (i >= 0 && i < p->endi && j >= 0 && j < p->endj && count < 5)
				{
					if (i > 0  && (p->bazis[j][i - 1].xcoord + count) * 40 + x < (p->bazis[j][i].xcoord * 40 + x))
					{
						if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count > 0.5 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->bazis[j][i - 1].xcoord + count) * 40 + x, (k * (p->bazis[j][i - 1].xcoord + count) + b) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] == p->nbrs[j][i - 1] && p->nbrs[j][i] > 1 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (p->bazis[j][i - 1].xcoord + count) * 40 + x, (k * (p->bazis[j][i - 1].xcoord + count) + b) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count < 0.5 && p->nbrs[j][i - 1] > 0)
							mlx_pixel_put(p->conn, p->win, (p->bazis[j][i - 1].xcoord + count) * 40 + x, (k * (p->bazis[j][i - 1].xcoord + count) + b) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j][i - 1] && count > 0.7 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (p->bazis[j][i - 1].xcoord + count) * 40 + x, (k * (p->bazis[j][i - 1].xcoord + count) + b) * 40 + y, 0x1100FC);
						else if (p->nbrs[j][i] > p->nbrs[j][i - 1] && count < 0.3 && p->nbrs[j][i - 1] < 0)
							mlx_pixel_put(p->conn, p->win, (p->bazis[j][i - 1].xcoord + count) * 40 + x, (k * (p->bazis[j][i - 1].xcoord + count) + b) * 40 + y, 0x1100FC);
						else if (p->nbrs[j][i] < 0 && p->nbrs[j][i] == p->nbrs[j][i - 1])
							mlx_pixel_put(p->conn, p->win, (p->bazis[j][i - 1].xcoord + count) * 40 + x, (k * (p->bazis[j][i - 1].xcoord + count) + b) * 40 + y, 0x1100FC);
						else if (p->nbrs[j][i] > 0 && p->nbrs[j][i] == p->nbrs[j][i - 1])
							mlx_pixel_put(p->conn, p->win, (p->bazis[j][i - 1].xcoord + count) * 40 + x, (k * (p->bazis[j][i - 1].xcoord + count) + b) * 40 + y, 0xFC0000);
						else
							mlx_pixel_put(p->conn, p->win, (p->bazis[j][i - 1].xcoord + count) * 40 + x, (k * (p->bazis[j][i - 1].xcoord + count) + b) * 40 + y, 0xFFDD00);
					}
					if (j > 0 && ((p->bazis[j - 1][i].ycoord + count) * 40 + y < ynew * 40 + y))
					{
						if (p->nbrs[j][i] == p->nbrs[j - 1][i] && p->nbrs[j][i] > 1 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (k1 * (p->bazis[j - 1][i].xcoord + count) + b1) * 40 + x, (p->bazis[j - 1][i].ycoord + count) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count < 0.5 && p->nbrs[j - 1][i] > 0)
							mlx_pixel_put(p->conn, p->win, (k1 * (p->bazis[j - 1][i].xcoord + count) + b1) * 40 + x, (p->bazis[j - 1][i].ycoord + count) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] > p->nbrs[j - 1][i] && count > 0.5 && p->nbrs[j][i] > 0)
							mlx_pixel_put(p->conn, p->win, (k1 * (p->bazis[j - 1][i].xcoord + count) + b1) * 40 + x, (p->bazis[j - 1][i].ycoord + count) * 40 + y, 0xFC0000);
						else if (p->nbrs[j][i] < p->nbrs[j - 1][i] && count > 0.9 && p->nbrs[j][i] < 0)
							mlx_pixel_put(p->conn, p->win, (k1 * (p->bazis[j - 1][i].xcoord + count) + b1) * 40 + x, (p->bazis[j - 1][i].ycoord + count) * 40 + y, 0x1100FC);
						else if (p->nbrs[j][i] > p->nbrs[j - 1][i] && count < 0.2 && p->nbrs[j - 1][i] < 0)
							mlx_pixel_put(p->conn, p->win, (k1 * (p->bazis[j - 1][i].xcoord + count) + b1) * 40 + x, (p->bazis[j - 1][i].ycoord + count) * 40 + y, 0x1100FC);
						else if (p->nbrs[j][i] < 0 && (p->nbrs[j][i] == p->nbrs[j - 1][i]))
							mlx_pixel_put(p->conn, p->win, (k1 * (p->bazis[j - 1][i].xcoord + count) + b1) * 40 + x, (p->bazis[j - 1][i].ycoord + count) * 40 + y, 0x1100FC);
						else if (p->nbrs[j][i] > 0 && (p->nbrs[j][i] == p->nbrs[j - 1][i]))
							mlx_pixel_put(p->conn, p->win, (k1 * (p->bazis[j - 1][i].xcoord + count) + b1) * 40 + x, (p->bazis[j - 1][i].ycoord + count) * 40 + y, 0xFC0000);
						else
					 		mlx_pixel_put(p->conn, p->win, (k1 * (p->bazis[j - 1][i].xcoord + count) + b1) * 40 + x, (p->bazis[j - 1][i].ycoord + count) * 40 + y, 0xFFDD00);
					}
					count += 0.01;
				}
				p->bazis[j][i].xcoord = xnew;
				p->bazis[j][i].ycoord = ynew;
				p->bazis[j][i].zcoord = znew;
				count = 0;
				i++;
			}
			x = 500;
			j++;
		}
		//p->angle_rad_w = p->angle_rad_w + 0.174533;
	}
	ft_putnbr(key);
	if (p->angle_rad_w > 3.2)
	{
		p->angle_rad_w = 0.174533;
		p->flag1 = p->flag1 * -1;
	}
	if (p->angle_rad_r > 1.57)
	{
		p->angle_rad_r = 0.174533;
	}
	printf("%f\n", p->angle_rad_w);
	printf("%s\n\n\n", "------------------------");
	return (0);
}

int		draw_image(int **nbrs, int endj, int endi)
{
	t_param	p;
	void	*conn_ptr;
	void	*win_ptr_main;
	int		i;
	int		j;
	t_coord	**coord;
	t_coord	**bazis;
	int		**test;
	int x = 500;
	int y = 300;
	int xnew;
	int ynew;
	int	count = 0;
	t_param *ptr_p = &p;
	//void *ptr_p = (void *)p;

	test = (int **)malloc(sizeof(int *) * 10);
	coord = (t_coord **)malloc(sizeof(t_coord *) * 35);
	bazis = (t_coord **)malloc(sizeof(t_coord *) * 35);
	ptr_p->endi = endi;
	ptr_p->endj = endj;
	ptr_p->nbrs = nbrs;
	ptr_p->angle_rad_w = 0.01;
	ptr_p->angle_rad_r = 0.01;
	ptr_p->flag1 = 1;
	ptr_p->flag2 = -1;
	j = 0;
	conn_ptr = mlx_init();
	win_ptr_main = mlx_new_window(conn_ptr, 1600, 1600, "Shit");
	ptr_p->win = win_ptr_main;
	ptr_p->conn = conn_ptr;
	while (j < endj)
	{
		while (i < endi)
		{
			printf("%d ", nbrs[j][i]);
			i++;
		}
		i = 0;
		j++;
		printf("\n");
	}
	j = 0;
	//coord[j] = (t_coord *)malloc(sizeof(t_coord) * 100);
	while (j < endj)
	{
		coord[j] = (t_coord *)malloc(sizeof(t_coord) * 30);
		bazis[j] = (t_coord *)malloc(sizeof(t_coord) * 30);
		i = 0;
		while (i < endi)
		{
			coord[j][i].ycoord = j; 
			coord[j][i].xcoord = i;
			coord[j][i].zcoord = nbrs[j][i];
			bazis[j][i].ycoord = j; 
			bazis[j][i].xcoord = i;
			bazis[j][i].zcoord = nbrs[j][i];
			// xnew = (x + i) * 0.866 - (y + j) * 0.5;
			// ynew = (x + i) * 0.5 + (y + j) * 0.866;
			mlx_pixel_put(conn_ptr, win_ptr_main, x + i * 40, y + j * 40, 0xFFDD00);
			while (i >= 0 && i < endi && j >= 0 && j < endj && count < 40)
			{
				if (i < endi - 1)
					mlx_pixel_put(conn_ptr, win_ptr_main, (x + i * 40 + count), (y + j * 40), 0xFFFFFF);
				if (j < endj - 1)
					mlx_pixel_put(conn_ptr, win_ptr_main, x + i * 40, y + j * 40 + count, 0xFFFFFF);
				count += 1;
			}
			count = 0;
			i++;
		}
		x = 500;
		j++;
	}
	ptr_p->coord = coord;
	ptr_p->bazis = bazis;
	mlx_key_hook(win_ptr_main, turn_left_30, ptr_p);
	//mlx_pixel_put(conn_ptr, win_ptr_main, 250, 250, 0xFFFFFF);
	mlx_loop(conn_ptr);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	**line;
	int		ret;
	char	**map;
	int		i;
	int		j;
	int		**nbrs;

	// printf("%d", fact(5));
	// printf("%f", stepen(3, 3));
	 printf("%f", get_sin(0.174533 * 3));
	j = 0;
	nbrs = (int **)malloc(sizeof(int *) * 20);
	line = (char**)malloc(sizeof(char *));
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, line))
	{
		i = 0;
		map = ft_strsplit(*line, ' ');
		nbrs[j] = (int *)malloc(sizeof(int) * 100);
		while (map[i])
		{
			nbrs[j][i] = ft_getnbr(map[i]) / 2;
			i++;
		}
		j++;
		free(map);
	}
	int endj = j;
	int endi = i;
	i = 0;
	j = 0;
	while (j < endj)
	{
		while (i < endi)
		{
			printf("%d ", nbrs[j][i]) * 3;
			i++;
		}
		i = 0;
		j++;
		printf("\n");
	}
	draw_image(nbrs, endj, endi);
}