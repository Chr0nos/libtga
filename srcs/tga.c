/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 21:41:43 by snicolet          #+#    #+#             */
/*   Updated: 2018/04/26 17:34:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tga.h"
#include <fcntl.h>
#include <stdlib.h>

static void			*load_tga_error(const char *error, void *file_content)
{
	if (file_content)
		free(file_content);
	ft_dprintf(2, "error: %s\n", error);
	return (NULL);
}

static unsigned int	*pixels_to_rgba(unsigned int *pixels, size_t n)
{
	while (n--)
		pixels[n] = TGA_L(pixels[n]);
	return (pixels);
}

static unsigned int	*tga_px3(unsigned char *pixels, const t_tga *specs)
{
	const size_t		pixels_total = specs->width * specs->height;
	const size_t		size = pixels_total * 3;
	size_t				p;
	unsigned int		*buffer;
	unsigned int		*px;

	if (!(buffer = malloc(pixels_total * 4)))
		return (load_tga_error("failed to alloc the second stage", pixels));
	px = buffer;
	p = 0;
	while (p < size)
	{
		*(px++) = ((unsigned int)0xff << 24) |
			((unsigned int)pixels[p + 2]) |
			((unsigned int)pixels[p + 1] << 8) |
			((unsigned int)pixels[p] << 16);
		p += 3;
	}
	free(pixels);
	return (buffer);
}

/*
** load a tga file into a unsigned int * to retrive pixels,
** *specs will be filled by the function, in case of error each value will be
** set to 0 and NULL will be returned
*/

unsigned int		*tga_load(const char *filepath, t_tga *specs)
{
	size_t			file_size;
	size_t			pixels_size;
	unsigned int	*pixels;
	char			*file_content;
	t_tga			*header;

	ft_bzero(specs, TGA_SIZE);
	if (!(file_content = ft_readfile(filepath, &file_size)))
		return (load_tga_error("unable to read file\n", NULL));
	if (file_size <= TGA_SIZE)
		return (load_tga_error("invalid file or no content\n", file_content));
	header = (t_tga*)(size_t)file_content;
	if ((header->type != TGA_TYPE_TC_RAW) || (header->depth < 24))
		return (load_tga_error("unsupported file format\n", file_content));
	pixels_size = header->width * header->height * (header->depth >> 3) + 1;
	if ((pixels = malloc(pixels_size)))
	{
		ft_memcpy(pixels, &file_content[TGA_SIZE], pixels_size);
		*specs = *header;
		free(file_content);
		if (specs->depth == 24)
			return (tga_px3((void*)(size_t)pixels, specs));
		return (pixels_to_rgba(pixels, specs->height * specs->width));
	}
	return (load_tga_error("failed to get pixels\n", file_content));
}
