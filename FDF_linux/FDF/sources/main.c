/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atote <atote@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:46:29 by atote             #+#    #+#             */
/*   Updated: 2021/01/28 18:12:01 by atote            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	turn_wrg_arrows(t_param *p, int key)
{
	if (key == BUTTON_A)
		p->ang_r += 0.07;
	if (key == BUTTON_D)
		p->ang_r -= 0.07;
	if (key == BUTTON_S)
		p->ang_w -= 0.07;
	if (key == BUTTON_W)
		p->ang_w += 0.07;
	if (key == BUTTON_Q)
		p->ang_z += 0.07;
	if (key == BUTTON_E)
		p->ang_z -= 0.07;
	if (key == BUTTON_UP)
		p->def_y -= 10;
	if (key == BUTTON_DOWN)
		p->def_y += 10;
	if (key == BUTTON_LEFT)
		p->def_x -= 10;
	if (key == BUTTON_RIGHT)
		p->def_x += 10;
	if (key == BUTTON_P)
		p->projection = "perspective";
	if (key == BUTTON_I)
		p->projection = "ISO";
}

void	decrease_z(int key, t_param *p)
{
	if (key == BUTTON_Z)
	{
		while (p->j < p->endj)
		{
			p->i = 0;
			while (p->i < p->endi)
			{
				p->nbrs[p->j][p->i] /= 1.1;
				p->i++;
			}
			p->j++;
		}
		p->maxh /= 1.1;
		p->minh /= 1.1;
	}
	if (key == BUTTON_PLUS)
		p->s = p->s + 2;
}

void	increase_z(int key, t_param *p)
{
	if (key == BUTTON_X)
	{
		while (p->j < p->endj)
		{
			p->i = 0;
			while (p->i < p->endi)
			{
				p->nbrs[p->j][p->i] *= 1.1;
				p->i++;
			}
			p->j++;
		}
		p->maxh *= 1.1;
		p->minh *= 1.1;
	}
	if (key == ENTER)
		init_def_p(p);
	if (key == SPACE)
		p->clr.b += 123;
}

int		turn(int key, void *param)
{
	t_param	*p;

	p = (t_param *)param;
	p->j = 0;
	if (key == ESC)
		exit(0);
	turn_wrg_arrows(p, key);
	if (key == BUTTON_MINUS)
	{
		if (p->s > 2)
			p->s = p->s - 2;
	}
	decrease_z(key, p);
	increase_z(key, p);
	if (key == BUTTON_1)
	{
		init_def_p(p);
		p->ang_r = 0.785398;
		p->ang_w = 0.610865238;
	}
	take_pix_map(p);
	rotate(p);
	draw_all(p);
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	double	**nbrs;
	t_param	p;

	if (argc == 1)
		ft_putstr_fd("No maps input, try ../maps/*.fdf\n", 1);
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	find_size(&fd, line, &p);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	nbrs = (double **)malloc(sizeof(double *) * (p.endj + 1));
	reading_map(fd, line, nbrs, &p);
	p.nbrs = nbrs;
	init_p(&p);
	init_def_p(&p);
	take_pix_map(&p);
	draw_all(&p);
	mlx_hook(p.win, 2, (1L << 0), turn, (void *)&p);
	mlx_hook(p.win, 4, (1L << 2), mouse_press, (void *)&p);
	mlx_hook(p.win, 5, (1L << 3), mouse_release, (void *)&p);
	mlx_hook(p.win, 6, (1L << 6), mouse_motion, (void *)&p);
	mlx_loop(p.conn);
}
