#include <scop.h>

// static const GLfloat g_vertex_buffer_data[] = {
//    -1.0f, -1.0f, 0.0f,
//    1.0f, -1.0f, 0.0f,
//    0.0f,  1.0f, 0.0f,
// };

GLuint  init_normal_buffer(t_obj *obj)
{
    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER,
        obj->vertex_data.vn.size * sizeof(GLfloat),
        &(obj->vertex_data.vn.vertices[0]),
        GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    return normalbuffer;
}

GLuint  init_vertex_buffer(t_obj *obj)
{
  	GLuint vertexBuffer;
  	glGenBuffers(1, &vertexBuffer);
  	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  	glBufferData(GL_ARRAY_BUFFER,
        sizeof(GLfloat) * obj->vertex_data.v.size,
        &(obj->vertex_data.v.vertices[0]),
        GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
  	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    return vertexBuffer;
}

GLuint  init_element_array_buffer(t_obj *obj)
{
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLushort) * obj->elements.f.size,
        &(obj->elements.f.element[0]),
        GL_STATIC_DRAW);
    return elementbuffer;
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
