/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glsl_loader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 15:21:57 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/13 15:33:02 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLSL_LOADER_H
# define GLSL_LOADER_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int		glsl_loader(char **text, const char *path);

#endif
