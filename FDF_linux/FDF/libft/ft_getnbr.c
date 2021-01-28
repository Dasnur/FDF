/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atote <atote@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:05:02 by atote             #+#    #+#             */
/*   Updated: 2020/02/01 14:05:11 by atote            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getnbr(char *str)
{
	int		i;
	int		nbr;
	int		flag;

	flag = 0;
	i = 0;
	nbr = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			flag = 1;
			i++;
		}
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	if (flag == 1)
		nbr = nbr * -1;
	return (nbr);
}
