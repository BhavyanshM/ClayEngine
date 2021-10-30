#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transforms[32];

void main(){
    v_Position = a_Position;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type geometry
#version 450 core
layout (triangles) in;
layout(triangle_strip, max_vertices = 3) out;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec3 v_Position;

uniform vec4 u_Color;

void main(){
    color = u_Color;
}