/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_load_ogl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 00:59:23 by snicolet          #+#    #+#             */
/*   Updated: 2017/07/04 01:00:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include <stdlib.h>
#include "tga.h"

/*
** load fhe filepath tga file into the graphic card (must have a valid opengl
** context)
** return the id of the opengl texture, 0 in case of error
*/

GLuint				tga_load_ogl(const char *filepath)
{
	t_tga				header;
	GLuint				id;
	unsigned int		*pixels;

	if (!(pixels = tga_load(filepath, &header)))
		return (0);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, header.width, header.height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	free(pixels);
	return (id);
}
