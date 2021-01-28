/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atote <atote@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:46:53 by atote             #+#    #+#             */
/*   Updated: 2021/01/28 17:16:20 by atote            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		fill_pix_gor(t_param *p, int x, int y)
{
	int	pc;

	pc = (x) * 4 + (y) * 4 * p->hei;
	if (p->cvet[p->j][p->i] != NULL)
	{
		p->im.im_d[pc] = p->crd[p->j][p->i - 1].clr->b;
		p->im.im_d[pc + 1] = p->crd[p->j][p->i - 1].clr->g;
	}
	else
	{
		p->im.im_d[pc] = p->crd[p->j][p->i].clr->b;
		p->im.im_d[pc + 1] = p->crd[p->j][p->i].clr->g;
	}
	if ((p->nbrs[p->j][p->i] > p->nbrs[p->j][p->i - 1])
	&& p->cvet[p->j][p->i - 1] == NULL)
		p->im.im_d[pc + 2] = p->crd[p->j][p->i - 1].clr->r + (p->d_grad * (p->
		nbrs[p->j][p->i] - p->nbrs[p->j][p->i - 1]) * (double)p->pnts_amount);
	else if ((p->nbrs[p->j][p->i] < p->nbrs[p->j][p->i - 1])
	&& p->cvet[p->j][p->i] == NULL)
		p->im.im_d[pc + 2] = p->crd[p->j][p->i - 1].clr->r - (p->d_grad * (p->
		nbrs[p->j][p->i - 1] - p->nbrs[p->j][p->i]) * (double)p->pnts_amount);
	else
		p->im.im_d[pc + 2] = p->crd[p->j][p->i].clr->r;
}

void		fill_pix_ver(t_param *p, int x, int y)
{
	int		pc;

	pc = (x) * 4 + (y) * 4 * p->hei;
	if (p->cvet[p->j][p->i] != NULL)
	{
		p->im.im_d[pc] = p->crd[p->j - 1][p->i].clr->b;
		p->im.im_d[pc + 1] = p->crd[p->j - 1][p->i].clr->g;
	}
	else
	{
		p->im.im_d[pc] = p->crd[p->j][p->i].clr->b;
		p->im.im_d[pc + 1] = p->crd[p->j][p->i].clr->g;
	}
	if (p->nbrs[p->j][p->i] > p->nbrs[p->j - 1][p->i]
	&& p->cvet[p->j - 1][p->i] == NULL)
		p->im.im_d[pc + 2] = p->crd[p->j - 1][p->i].clr->r + (p->d_grad * (p->
		nbrs[p->j][p->i] - p->nbrs[p->j - 1][p->i]) * p->pnts_amount);
	else if (p->nbrs[p->j][p->i] < p->nbrs[p->j - 1][p->i]
	&& p->cvet[p->j][p->i] == NULL)
		p->im.im_d[pc + 2] = p->crd[p->j - 1][p->i].clr->r - (p->d_grad * (p->
		nbrs[p->j - 1][p->i] - p->nbrs[p->j][p->i]) * p->pnts_amount);
	else
		p->im.im_d[pc + 2] = p->crd[p->j][p->i].clr->r;
}

void		calculate_ver(t_param *p)
{
	if (p->dx == 0)
	{
		p->xdraw = p->crd[p->j][p->i].xcrd * p->s + p->def_x;
		p->ydraw = (p->crd[p->j - 1][p->i].ycrd + p->count) * p->s + p->def_y;
	}
	else
	{
		p->xdraw = (p->crd[p->j - 1][p->i].xcrd + p->count) * p->s + p->def_x;
		p->ydraw = (p->crd[p->j - 1][p->i].ycrd + p->dy *
		(p->crd[p->j - 1][p->i].xcrd + p->count -
		p->crd[p->j - 1][p->i].xcrd) / p->dx) * p->s + p->def_y;
	}
	if (p->dx == 0)
		p->count += p->dy / 100;
	else
		p->count += p->dx / 100;
	p->pnts_amount++;
}

void		calculate_gor(t_param *p)
{
	if (p->dx == 0)
	{
		p->xdraw = p->crd[p->j][p->i].xcrd * p->s + p->def_x;
		p->ydraw = (p->crd[p->j][p->i].ycrd + p->count) * p->s + p->def_y;
	}
	else
	{
		p->xdraw = (p->crd[p->j][p->i - 1].xcrd + p->count) * p->s + p->def_x;
		p->ydraw = (p->crd[p->j][p->i - 1].ycrd + p->dy *
		(p->crd[p->j][p->i - 1].xcrd + p->count -
		p->crd[p->j][p->i - 1].xcrd) / p->dx) * p->s + p->def_y;
	}
	if (p->dx == 0)
		p->count += p->dy / 100;
	else
		p->count += p->dx / 100;
	p->pnts_amount++;
}

void		rotate(t_param *p)
{
	double	tmp;

	tmp = 0.0;
	p->j = 0;
	while (p->j < p->endj)
	{
		p->i = 0;
		while (p->i < p->endi)
		{
			rotate_help(p, tmp);
			if (ft_strcmp(p->projection, "perspective") == 0)
			{
				p->crd[p->j][p->i].ycrd = p->crd[p->j][p->i].ycrd
				/ (-0.01 * p->crd[p->j][p->i].zcrd + 1);
				p->crd[p->j][p->i].xcrd = p->crd[p->j][p->i].xcrd
				/ (-0.01 * p->crd[p->j][p->i].zcrd + 1);
				p->crd[p->j][p->i].zcrd = p->crd[p->j][p->i].zcrd
				/ (-0.01 * p->crd[p->j][p->i].zcrd + 1);
			}
			p->i++;
		}
		p->j++;
	}
}
