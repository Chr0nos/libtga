/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 15:23:31 by snicolet          #+#    #+#             */
/*   Updated: 2017/07/15 17:13:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"
#include "libft.h"

int			main(int ac, char **av)
{
	const char			*dest;
	const char			*src;
	t_tga				specs;
	unsigned int		*pixels;

	if (ac < 3)
		return (1);
	src = av[1];
	dest = av[2];
	ft_putstr("loading picture\n");
	if (!(pixels = tga_load(src, &specs)))
	{
		ft_dprintf(2, "failed to open file\n");
		return (1);
	}
	specs.type |= TGA_BIT_RLE;
	specs.depth = 32;
	ft_putstr("exporting\n");
	ft_printf("state: %d\n", tga_save(dest, &specs, pixels));
	ft_putstr("done\n");
	return (0);
}
