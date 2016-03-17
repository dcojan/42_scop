/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_shortcuts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:10:07 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 15:00:15 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

GLuint		new_buffer(GLuint type, GLuint size, GLfloat *data, GLuint draw)
{
	GLuint	buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(type, buffer);
	glBufferData(type, size * sizeof(data[0]), &(data[0]), draw);
	return (buffer);
}

GLuint		new_texture_buffer(uint w, uint h, uint8_t *data, GLuint color)
{
	GLuint	texture_id;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0,
		color, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (texture_id);
}

void		set_uniform_mat4x4(GLuint prog, const char *name, t_mat4x4 *mat)
{
	GLuint	rot_unif_id;

	rot_unif_id = glGetUniformLocation(prog, name);
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((mat->data)[0][0]));
}

void		set_attrib_array(GLuint num, GLuint size)
{
	glEnableVertexAttribArray(num);
	glVertexAttribPointer(num, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
