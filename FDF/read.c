#include "fdf.h"

void		reading_map(int fd, char **line, int **nbrs, t_param* p)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	while (get_next_line(fd, line))
	{
		i = 0;
		map = ft_strsplit(*line, ' ');
		nbrs[j] = (int *)malloc(sizeof(int) * 250);
		while (map[i])
		{
			nbrs[j][i] = (ft_getnbr(map[i]) / 10);
			i++;
		}
		j++;
		free(map);
	}
	p->endi = i;
	p->endj = j;
	p->nbrs = nbrs;
}

void		init_p(t_param *p)
{
	t_img	p_i;
	t_color	p_c;

	p->height = 1600;
	p->weight = 1600;
	p_c.red = 255;
	p_c.blue = 0;
	p_c.green = 221;
	p->conn = mlx_init();
	p->win = mlx_new_window(p->conn, p->height, p->weight, "Shit");
	p_i.p_img = mlx_new_image(p->conn, p->height, p->weight);
	p_i.img_data = mlx_get_data_addr(p_i.p_img, &p_i.bpp, &p_i.size_line, &p_i.endian);
	p->im = p_i;
	p->def_size = 40;
	p->def_x = 500;
	p->def_y = 300;
	p->angle_rad_r = 0.1;
	p->angle_rad_w = 0.1;
	p->size = 20;
	p->clr = p_c;
}