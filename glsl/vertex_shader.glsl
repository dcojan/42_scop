#version 330 core

layout(location = 0) in vec3 in_vertex;
layout(location = 2) in vec3 in_normal;
// "layout(location = 1) in vec3 vertexColor;"
// "vec3 vertexColor = vec3(1.0f,0.0f,0.0f);"
// "layout(location = 1) in vec2 vertexUV;"

// "out vec3 fragmentColor;"
// "out vec2 UV;"
out vec3 position_world_space;
out vec3 normal_camera_space;
out vec3 light_direction_camera_space;
out vec3 eye_direction_camera_space;

// uniform mat4 MVP;
uniform mat4 Rotation;
uniform mat4 Projection;
uniform mat4 View;
// uniform mat4 V;
// "uniform mat4 M;"
uniform vec3 light_position_worldspace;

smooth out vec3 vNormal;

void main() {
	gl_Position = Projection * View * Rotation * (vec4(in_vertex, 1.0));
// " position_world_space = (M * vec4(in_vertex, 1.0)).xyz;"
	position_world_space = (Rotation * vec4(in_vertex, 1.0)).xyz;

// " vec3 vertex_position_cameraspace = (V * M * vec4(in_vertex, 1.0)).xyz;"
	vec3 vertex_position_cameraspace = (View * Rotation * vec4(in_vertex, 1.0)).xyz;
	eye_direction_camera_space = vec3(0,0,0) - vertex_position_cameraspace;
//
	vec3 light_position_cameraspace = (View * vec4(light_position_worldspace, 1.0)).xyz;
	light_direction_camera_space = light_position_cameraspace + eye_direction_camera_space;
	normal_camera_space = (View * Rotation * vec4(in_normal, 0)).xyz;
// "normal_camera_space = (V * M * vec4(in_normal, 0)).xyz;"
// "	fragmentColor = vertexColor;"
// "UV = vertexUV;"
}
