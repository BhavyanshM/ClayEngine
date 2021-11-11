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

in vec3 v_Position[3];

out vec3 v_Normal;
out vec3 f_Position;

void main()
{
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

uniform vec4 u_ObjectColor;
uniform vec4 u_LightColor;
uniform float u_AmbientStrength;

void main(){
    vec3 lightPos = vec3(-2.1, 3.2, 5.3);
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(lightPos - f_Position);

    vec4 ambient = u_AmbientStrength * u_LightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * u_ObjectColor;

    vec4 result = (ambient + diffuse) * u_ObjectColor;
    color = vec4(result.xyz, 1.0);
}