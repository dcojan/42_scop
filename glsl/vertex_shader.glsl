#version 330 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 in_normal;
layout(location = 4) in vec3 in_color;

out vec2 UV;
out vec3 position_world_space;
out vec3 normal_camera_space;
out vec3 light_direction_camera_space;
out vec3 eye_direction_camera_space;
out vec3 fragment_color;

uniform mat4 Rotation;
uniform mat4 Projection;
uniform mat4 Translation;
uniform mat4 PostTranslation;
uniform mat4 View;
uniform vec3 light_position_worldspace;

smooth out vec3 vNormal;

void main() {
	gl_Position = Projection * View * PostTranslation * Rotation * Translation * (vec4(in_vertex, 1.0));
	position_world_space = (Rotation * vec4(in_vertex, 1.0)).xyz;

	vec3 vertex_position_cameraspace = (View * Rotation * vec4(in_vertex, 1.0)).xyz;
	eye_direction_camera_space = vec3(0,0,0) - vertex_position_cameraspace;

	vec3 light_position_cameraspace = (View * vec4(light_position_worldspace, 1.0)).xyz;
	light_direction_camera_space = light_position_cameraspace + eye_direction_camera_space;
	normal_camera_space = (View * Rotation * vec4(in_normal, 0)).xyz;

	fragment_color = in_color;
	UV = vertex_uv;
}
