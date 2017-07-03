/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 21:41:43 by snicolet          #+#    #+#             */
/*   Updated: 2017/06/11 18:38:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tga.h"

void		tga_display(const t_tga *specs)
{
	ft_printf("id: %hhd\ncolor_map: %hhd\ntype: %hhd\nfirst_entry_index: %hu\n"
			"color_map_len: %hu\nbpp: %hhu\nx_offset: %hu\ny_offset: %hu\n"
			"width: %hu\nheight: %hu\ndepth: %hhu\ndescriptor: %hhu\n",
			specs->id, specs->color_map, specs->type, specs->first_entry_index,
			specs->color_map_len, specs->bpp, specs->x_offset, specs->y_offset,
			specs->width, specs->height, specs->depth, specs->descriptor);
}
