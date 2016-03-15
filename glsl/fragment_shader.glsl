#version 330 core

in vec3 position_world_space;
in vec3 normal_camera_space;
in vec3 eye_direction_camera_space;
in vec3 light_direction_camera_space;
in vec2 UV;
in vec3 fragment_color;

uniform sampler2D texture_sampler;
uniform float texture_transition;
uniform vec3 light_position_worldspace;
uniform float LightPower;

out vec3 outColor;

void main() {
	// "	outColor = vec4(fragmentColor, 1.0f);" // R G B Alpha
	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1,1,1);
//	float LightPower = 50.0f;

	// Material properties
	vec3 fragment_color2 = fragment_color * texture_transition;
	vec3 tex = (texture(texture_sampler, UV).rgb * (1 - texture_transition));

	vec3 MaterialDiffuseColor = fragment_color2 + tex;
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

	// Distance to the light
	float distance = length( light_position_worldspace - position_world_space );

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( normal_camera_space );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( light_direction_camera_space );

	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );

	// Eye vector (towards the camera)
	vec3 E = normalize(eye_direction_camera_space);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );

	outColor =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);

		// "	outColor = vec3(1,0,0);" // R G B Alpha
}
