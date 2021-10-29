#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in int a_Id;

out vec4 v_Color;
out vec3 v_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transforms[32];

void main(){
    v_Position = a_Position;
    v_Color = a_Color;
    gl_Position = u_ViewProjection * u_Transforms[a_Id] * vec4(a_Position, 1.0);
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