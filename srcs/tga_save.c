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

	if (specs->type & TGA_BIT_RLE)
		return (tga_save_rle(filepath, specs, pixels));
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
/*
static void			tga_save_rle_loop(const int fd, const unsigned int *pixels,
	const size_t size, size_t p)
{
	unsigned char			len;
	unsigned int			color;

	while (p < size)
	{
		color = pixels[p];
		len = 1;
		while (((size_t)len + p < size) && (pixels[p + len] == color) && (len != 0x7f))
			len++;
		color = TGA_S(color);
		write(fd, &len, 1);
		write(fd, &color, sizeof(unsigned int));
		p += (size_t)len;
	}
}
*/
static unsigned char	*tga_rle_alloc(const unsigned int *pixels,
		const size_t size)
{
	size_t			p;
	unsigned char	*px;
	unsigned char	*pxo;

	if (!(px = malloc((size << 2) + size)))
		return (NULL);
	pxo = px;
	p = 0;
	while (p < size)
	{
		*(px++) = 0;
		*(unsigned int *)(size_t)px = TGA_S(pixels[p]);
		p++;
		px += 4;
	}
	return (pxo);
}

/*
** example of use:
** t_tga specs;
** specs.height = 1280;
** specs.width = 720;
** specs.type = TGA_TYPE_TC_RAW | TGA_BIT_RLE;
** tga_save_rle('/tmp/picture.tga', &specs, pixels);
*/

int					tga_save_rle(const char *filepath, const t_tga *specs,
		const unsigned int *pixels)
{
	const size_t			size = specs->height * specs->width;
	int						fd;
	unsigned char			*rle_pixels;

	if (!(fd = open(filepath, O_RDWR | O_TRUNC | O_CREAT, 0644)))
		return (1);
	if( (!(specs->type & TGA_BIT_RLE)) ||
			((specs->type & 0x07) != TGA_TYPE_TC_RAW))
		return (1);
	if (!(rle_pixels = tga_rle_alloc(pixels, size)))
		return (2);
	write(fd, specs, TGA_SIZE);
	write(fd, rle_pixels, (size << 2) + size);
	//	tga_save_rle_loop(fd, pixels, size, 0);
	close(fd);
	free(rle_pixels);
	return (0);
}
