#include "fdf.h"

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