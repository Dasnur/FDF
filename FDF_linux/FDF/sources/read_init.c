/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atote <atote@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:46:44 by atote             #+#    #+#             */
/*   Updated: 2021/01/28 18:14:30 by atote            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		find_size(int *fd, char *line, t_param *p)
{
	char	**map;
	
	p->j = 0;
	p->i = 0;
	while ((p->flag = get_next_line(*fd, &line)) > 0)
	{
		if (p->j == 0)
			map = ft_strsplit(line, ' ');
		while (map[p->i] && (p->j == 0))
		{
			//printf("%s\n", map[p->i]);
			p->i++;
		}
		p->j++;
	}
	if (map != NULL)
		free_map(map);
	p->endi = p->i;
	p->endj = p->j;
	if (p->endj > p->endi)
		p->endmax = p->endj;
	else
		p->endmax = p->endi;
	//printf("%d \n%d", p->endi, p->endj);
	close(*fd);
}

void		reading_map(int fd, char *line, double **nbrs, t_param *p)
{
	char	**map;
	char	*tmp;

//printf("%d \n%d", p->endi, p->endj);
	p->cvet = (char ***)malloc(sizeof(char ***) * (p->endj + 1));
	p->j = 0;
	while ((p->flag = get_next_line(fd, &line)) > 0)
	{
		p->cvet[p->j] = (char **)malloc(sizeof(char **) * (p->endi + 1));
		p->i = 0;
		map = ft_strsplit(line, ' ');
		nbrs[p->j] = (double *)malloc(sizeof(double) * (p->endi + 1));
		while (map[p->i])
		{
			tmp = ft_strchr(map[p->i], ',');
			p->cvet[p->j][p->i] = tmp != NULL ? strdup(tmp + 3) : NULL;
			nbrs[p->j][p->i] = ft_atoi(map[p->i]);
			p->i++;
		}
		p->j++;
		if (map != NULL)
			free_map(map);
	}
	if (p->flag == -1)
		exit(1);
}

void		init_p(t_param *p)
{
	t_img	p_i;

	p->hei = HEIGHT;
	p->wid = WIDTH;
	p->conn = mlx_init();
	p->win = mlx_new_window(p->conn, p->hei, p->wid, "FDF");
	p_i.p_img = mlx_new_image(p->conn, p->hei, p->wid);
	p_i.im_d = mlx_get_data_addr(p_i.p_img, &p_i.bpp,
	&p_i.size_line, &p_i.endian);
	p->im = p_i;
}

void		init_p_const(t_param *p)
{
	p->j = 0;
	p->def_size = 40;
	p->def_x = HEIGHT / 2;
	p->def_y = WIDTH / 2;
	p->ang_r = 0;
	p->ang_w = 0;
	p->ang_z = 0;
	p->maxh = 0;
	p->pre_y = 0;
	p->pre_x = 0;
	p->press_1 = 0;
	p->press_2 = 0;
	p->minh = 20000000;
	p->s = p->hei / 4 / p->endj;
	p->projection = "ISO";
	p->clr.r = 255;
	p->clr.g = 0;
	p->clr.b = 255;
}

void		init_def_p(t_param *p)
{
	t_coord	**crd;

	init_p_const(p);
	crd = (t_coord **)malloc(sizeof(t_coord *) * (p->endj + 1));
	while (p->j < p->endj)
	{
		crd[p->j] = (t_coord *)malloc(sizeof(t_coord) * (p->endi + 1));
		p->i = 0;
		while (p->i < p->endi)
		{
			crd[p->j][p->i].ycrd = p->j - p->endj / 2;
			crd[p->j][p->i].xcrd = p->i - p->endi / 2;
			crd[p->j][p->i].zcrd = p->nbrs[p->j][p->i];
			if (p->nbrs[p->j][p->i] > p->maxh)
				p->maxh = p->nbrs[p->j][p->i];
			if (p->nbrs[p->j][p->i] < p->minh)
				p->minh = p->nbrs[p->j][p->i];
			p->i++;
		}
		p->j++;
	}
	p->crd = crd;
	take_pix_map(p);
}
