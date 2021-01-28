/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atote <atote@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:47:01 by atote             #+#    #+#             */
/*   Updated: 2021/01/28 17:16:09 by atote            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		get_pix_clr(t_param *p, int j, int i)
{
	t_color *clr;

	clr = (t_color *)malloc(sizeof(t_color *));
	p->crd[j][i].clr = clr;
	p->crd[j][i].clr->r = sixteen_to_ten(p->cvet[j][i], 0);
	p->crd[j][i].clr->g = sixteen_to_ten(p->cvet[j][i], 2);
	p->crd[j][i].clr->b = sixteen_to_ten(p->cvet[j][i], 4);
}

void		take_pix_clr(t_param *p, int j, int i)
{
	t_color	*clr;
	double	grad_pix;

	if (p->crd[j][i].clr)
		free(p->crd[j][i].clr);
	grad_pix = 200 / (p->maxh - p->minh);
	p->d_grad = grad_pix / 100;
	clr = (t_color *)malloc(sizeof(t_color *));
	p->crd[j][i].clr = clr;
	p->crd[j][i].clr->r = 35 + (grad_pix * ((p->nbrs[j][i]) - p->minh));
	p->crd[j][i].clr->g = p->clr.g;
	p->crd[j][i].clr->b = p->clr.b;
}

void		take_pix_map(t_param *p)
{
	int		j;
	int		i;

	j = 0;
	while (j < p->endj)
	{
		i = 0;
		while (i < p->endi)
		{
			if (p->cvet[j][i] == NULL)
				take_pix_clr(p, j, i);
			else
				get_pix_clr(p, j, i);
			i++;
		}
		j++;
	}
}

void		menu(t_param *p)
{
	mlx_put_image_to_window(p->conn, p->win, p->im.p_img, 0, 0);
	mlx_string_put(p->conn, p->win, 10, 10, 0xFF9100, "w/s   X rot |");
	mlx_string_put(p->conn, p->win, 10, 25, 0xFF9100, "q/e   Y rot |");
	mlx_string_put(p->conn, p->win, 10, 40, 0xFF9100, "a/d   Z rot |");
	mlx_string_put(p->conn, p->win, 150, 10, 0xFF9100, "i  ISO           |");
	mlx_string_put(p->conn, p->win, 150, 25, 0xFF9100, "p  perspective   |");
	mlx_string_put(p->conn, p->win, 150, 40, 0xFF9100, "ENTER  default   |");
	mlx_string_put(p->conn, p->win, 340, 10, 0xFF9100, "arrows  move proj  |");
	mlx_string_put(p->conn, p->win, 340, 25, 0xFF9100,
	"+/-  zoom          |");
	mlx_string_put(p->conn, p->win, 510, 10, 0xFF9100,
	"z  icrease points hei   |");
	mlx_string_put(p->conn, p->win, 510, 25, 0xFF9100,
	"x  decrease points hei  |");
}

void		draw_all(t_param *p)
{
	p->j = 0;
	mlx_clear_window(p->conn, p->win);
	ft_bzero((void *)p->im.im_d, p->hei * p->wid * 4);
	while (p->j < p->endj)
	{
		p->i = 0;
		while (p->i < p->endi)
		{
			draw_gor(p);
			draw_ver(p);
			p->i++;
		}
		p->j++;
	}
	menu(p);
}
