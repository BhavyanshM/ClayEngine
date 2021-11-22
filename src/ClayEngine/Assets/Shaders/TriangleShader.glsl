#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in float a_Id;

out vec3 v_Position;
out vec4 v_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transforms[32];

void main(){
    v_Color = a_Color;
    v_Position = a_Position;
    gl_Position = u_ViewProjection * u_Transforms[int(a_Id)] * vec4(a_Position, 1.0);
}

#type geometry
#version 450 core
layout (triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 v_Position[3];
in vec4 v_Color[3];

out vec3 v_Normal;
out vec3 f_Position;
out vec4 f_Color;

void main()
{
    f_Color = v_Color[0];

    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 normal = normalize(cross(a, b));
    f_Position = v_Position[0];
    v_Normal = normal;

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

in vec3 f_Position;
in vec3 v_Normal;
in vec4 f_Color;

uniform vec4 u_ObjectColor;
uniform vec4 u_LightColor;
uniform float u_AmbientStrength;
uniform vec4 u_Colors[32];

void main(){
    vec3 lightPos = vec3(-2.1, 3.2, 5.3);
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(lightPos - f_Position);

    vec4 ambient = u_AmbientStrength * u_LightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec4 objectColor = f_Color;
    vec4 diffuse = diff * objectColor;

    vec4 result = (ambient + diffuse) * objectColor;
    color = vec4(result.xyz, 1.0);
}