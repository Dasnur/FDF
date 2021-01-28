/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atote <atote@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:47:10 by atote             #+#    #+#             */
/*   Updated: 2021/01/28 18:11:55 by atote            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		mouse_press(int key, int x, int y, void *ptr)
{
	t_param *p;

	p = (t_param *)ptr;
	if (x <= 0 || x >= p->hei || y <= 0 || y >= p->wid)
		return (0);
	if (key == 1)
		p->press_1 = 1;
	if (key == 2)
		p->press_2 = 1;
	if (key == 4)
	{
		p->s = p->s + 2;
		draw_all(p);
	}
	if (key == 5)
	{
		if (p->s > 2)
			p->s -= 2;
		draw_all(p);
	}
	return (0);
}

int		mouse_release(int key, int x, int y, void *ptr)
{
	t_param *p;

	p = (t_param *)ptr;
	if (x <= 0 || x >= p->hei || y <= 0 || y >= p->wid)
		return (0);
	if (key == 1)
		p->press_1 = 0;
	if (key == 2)
		p->press_2 = 0;
	return (0);
}

void	motion_but_1(t_param *p, int x, int y)
{
	if (abs(y - p->pre_y) > 5)
		p->ang_w += (y - p->pre_y) * -0.005;
	if (abs(x - p->pre_x) > 5)
		p->ang_z += (x - p->pre_x) * -0.005;
	if (abs(y - p->pre_y) > 5 || abs(x - p->pre_x) > 5)
	{
		p->pre_x = x;
		p->pre_y = y;
		rotate(p);
		draw_all(p);
	}
}

int		mouse_motion(int x, int y, void *ptr)
{
	t_param	*p;

	p = (t_param *)ptr;
	if (abs(y - p->pre_y) > 25 || abs(x - p->pre_x) > 25)
	{
		p->pre_x = x;
		p->pre_y = y;
	}
	if (p->press_1 == 1)
		motion_but_1(p, x, y);
	if (p->press_2 == 1)
	{
		p->def_y += (y - p->pre_y) * 0.8;
		p->def_x += (x - p->pre_x) * 0.8;
		p->pre_x = x;
		p->pre_y = y;
		draw_all(p);
	}
	return (0);
}
