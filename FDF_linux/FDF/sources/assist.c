/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atote <atote@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 15:41:29 by atote             #+#    #+#             */
/*   Updated: 2021/01/28 17:16:03 by atote            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		draw_gor(t_param *p)
{
	if (p->i > 0)
	{
		p->pnts_amount = 0;
		p->count = 0;
		p->dx = p->crd[p->j][p->i].xcrd - p->crd[p->j][p->i - 1].xcrd;
		p->dy = p->crd[p->j][p->i].ycrd - p->crd[p->j][p->i - 1].ycrd;
		while (p->pnts_amount < 100)
		{
			calculate_gor(p);
			if (p->xdraw > 10 && p->ydraw > 10 && p->xdraw < p->hei
			&& p->ydraw < p->wid)
				fill_pix_gor(p, p->xdraw, p->ydraw);
		}
	}
}

void		draw_ver(t_param *p)
{
	if (p->j > 0)
	{
		p->pnts_amount = 0;
		p->dx = p->crd[p->j][p->i].xcrd - p->crd[p->j - 1][p->i].xcrd;
		p->dy = p->crd[p->j][p->i].ycrd - p->crd[p->j - 1][p->i].ycrd;
		p->count = 0;
		while (p->pnts_amount < 100)
		{
			calculate_ver(p);
			if (p->xdraw > 10 && p->ydraw > 10 && p->xdraw < p->hei
			&& p->ydraw < p->wid)
				fill_pix_ver(p, p->xdraw, p->ydraw);
		}
	}
}

int			sixteen_to_ten(char *str, int p)
{
	int		i;
	int		res;
	int		tmp;

	res = 0;
	i = 1;
	while (i >= 0)
	{
		if (str[p] >= 65)
			tmp = str[p] - 55;
		else
			tmp = str[p] - 48;
		res = res + tmp * pow(16, i);
		i--;
	}
	return (res);
}

void		rotate_help(t_param *p, double tmp)
{
	p->crd[p->j][p->i].xcrd = (p->i - p->endi / 2) * cos(p->ang_r)
	- (p->j - p->endj / 2) * sin(p->ang_r);
	p->crd[p->j][p->i].ycrd = (p->i - p->endi / 2) * sin(p->ang_r)
	+ (p->j - p->endj / 2) * cos(p->ang_r);
	p->crd[p->j][p->i].zcrd = (p->crd[p->j][p->i].ycrd) * sin(p->ang_w)
	+ (p->nbrs[p->j][p->i] * cos(p->ang_w));
	p->crd[p->j][p->i].ycrd = (p->crd[p->j][p->i].ycrd) * cos(p->ang_w)
	+ (p->nbrs[p->j][p->i] * -1 * sin(p->ang_w));
	tmp = (p->crd[p->j][p->i].xcrd) * cos(p->ang_z)
	- (p->crd[p->j][p->i].zcrd) * sin(p->ang_z);
	p->crd[p->j][p->i].zcrd = (p->crd[p->j][p->i].xcrd)
	* sin(p->ang_z) + (p->crd[p->j][p->i].zcrd) * cos(p->ang_z);
	p->crd[p->j][p->i].xcrd = tmp;
}
