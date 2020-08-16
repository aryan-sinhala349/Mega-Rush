#type vertex
#version 330 core

in vec3 a_Position;

out vec3 g_Position;

void main()
{
	g_Position = a_Position;
}

#type geometry
#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in vec3 g_Position[];

void main()
{
	vec3 position = g_Position[0];
	vec2 scale = vec2(1.0, 1.0);

	gl_Position = (vec4(position, 1.0) + vec4(-scale.x / 2.0, -scale.y / 2.0, 0.0, 0.0));
	EmitVertex();
	
	gl_Position = (vec4(position, 1.0) + vec4( scale.x / 2.0, -scale.y / 2.0, 0.0, 0.0));
	EmitVertex();					   
			
	gl_Position = (vec4(position, 1.0) + vec4( scale.x / 2.0,  scale.y / 2.0, 0.0, 0.0));
	EmitVertex();					   
			
	gl_Position = (vec4(position, 1.0) + vec4( scale.x / 2.0,  scale.y / 2.0, 0.0, 0.0));
	EmitVertex();					   
				
	gl_Position = (vec4(position, 1.0) + vec4(-scale.x / 2.0,  scale.y / 2.0, 0.0, 0.0));
	EmitVertex();					   
				
	gl_Position = (vec4(position, 1.0) + vec4(-scale.x / 2.0, -scale.y / 2.0, 0.0, 0.0));
	EmitVertex();

	EndPrimitive();
}

#type fragment
#version 330 core

out vec4 color;

void main()
{
	color = vec4(0.2, 0.3, 0.8, 1.0);
}