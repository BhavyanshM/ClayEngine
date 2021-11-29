#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in float a_Id;

out vec3 v_Position;
out vec4 v_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transforms[250];

void main(){
    v_Color = a_Color;
    v_Position = a_Position;
    gl_Position = u_ViewProjection * u_Transforms[int(a_Id)] * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec3 v_Position;

uniform vec4 u_Color;

void main(){
    //color = vec4(v_Color.x - v_Position.y * 0.1, v_Color.y - v_Position.y * 0.12, v_Color.z - v_Position.y * 0.13, 1.0);
    color = v_Color;
}