/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:10:07 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 16:27:07 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

GLuint		new_buffer(GLuint type, GLuint size, GLfloat *data, GLuint draw)
{
	GLuint	buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(type, buffer);
	glBufferData(type,
		size * sizeof(data[0]),
		&(data[0]),
		draw);
	return (buffer);
}

//
// GLuint  init_texture_buffer()
// {
//   	GLuint vertexBuffer;
//   	glGenBuffers(1, &vertexBuffer);
//   	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//   	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
//   	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
//   	glEnableVertexAttribArray(1);
//     return vertexBuffer;
// }
