/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:15 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/12 17:13:16 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	clean_object(t_obj *obj)
{
	glDeleteProgram(obj->shaderProgram);
	glDeleteBuffers(1, &(obj->vertexBuffer));
	glDeleteBuffers(1, &(obj->normalBuffer));
	if (obj->vertex_data.v.vertices != NULL)
		free(obj->vertex_data.v.vertices);
	if (obj->vertex_data.vn.vertices != NULL)
		free(obj->vertex_data.vn.vertices);
	if (obj->elements.f.element != NULL)
		free(obj->elements.f.element);
	free(obj);
}

int		main(int ac, char **av)
{
	t_obj		*obj;
	t_sdl		sdl_var;

	if (ac == 2)
	{
		obj = load_obj(av[1]);
		if (obj != NULL)
		{
			init_sdl(&sdl_var);
			scop(obj, &sdl_var);
			clean_object(obj);
			clean_sdl(&sdl_var);
		}
		else
			printf("Error : unable to load object\n");
	}
	else
		printf("Usage :\n$> ./scop file.obj\n");
	return (0);
}
