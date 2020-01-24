#ifndef FDF_H
# define FDF_H

# include "../../minilibx/mlx.h"
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>

typedef struct		s_coord
{
	double		xcoord;
	double		ycoord;
	double		zcoord;
}					t_coord;

typedef struct 		s_img
{
	void		*p_img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
}					t_img;

typedef struct		s_color
{
	int			red;
	int			blue;
	int			green;
}					t_color;

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
	int			height;
	int			weight;
	int			def_x;
	int			def_y;
	int			def_size;
	int			size;
	t_coord		**coord;
	t_img		im;
	t_color		clr;
}					t_param;

double		stepen(double in, int st);
int			fact(int st);
double		get_sin(double rad);
double		get_cos(double rad);
void		reading_map(int fd, char **line, int **nbrs, t_param *p);
void		init_p(t_param *p);
void		fill_pix(t_param *p, int x, int y);

#endif