/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:34:39 by snicolet          #+#    #+#             */
/*   Updated: 2018/04/26 17:34:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tga.h"
#include <fcntl.h>
#include <stdlib.h>

/*
** export pixels to a tga filepath, if the file already exists it will be
** replaced
** returns:
** 0 = everything was ok, no error
** 1 = wrong header type or memdup failed
** 2 = failed to open destination file, check permissions
*/

int					tga_save(const char *filepath, const t_tga *specs,
	const unsigned int *pixels)
{
	const size_t	size = specs->height * specs->width;
	int				fd;
	unsigned int	*px;
	size_t			p;

	if ((specs->type != TGA_TYPE_TC_RAW) ||
			(!(px = ft_memdup(pixels, size << 2))))
		return (1);
	if (!(fd = open(filepath, O_RDWR | O_TRUNC | O_CREAT, 0644)))
	{
		free(px);
		return (2);
	}
	p = size;
	while (p--)
		px[p] = TGA_S(px[p]);
	write(fd, specs, TGA_SIZE);
	write(fd, px, size << 2);
	close(fd);
	free(px);
	return (0);
}
