/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:48:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/03 13:28:09 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_minimap(t_app *app)
{
	t_minimap	mm;

	mm.pixX = -1;
	mm.pixY = -1;
	mm.startX = -1;
	mm.startY = -1;
	mm.intX = -1;
	mm.intY = -1;
	mm.mapSizeX = -1;
	mm.mapSizeY = -1;
	set_frame_dimensions(app, &mm);
	get_minimap_pos(app, &mm);
	put_minimap_on_screen(app, &mm);
	put_minimap_frame(app, &mm);
}
