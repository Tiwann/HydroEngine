#pragma vertex 
#version 460 core
in vec3 vPosition;
in vec2 vTexCoord;
in vec3 vNormal;
in vec4 vColor;

uniform mat4 uModelMatrix;

out vec3 position;
out vec2 texCoord;
out vec3 normal;
out vec4 color;

void main()
{
    gl_Position = uModelMatrix * vec4(vPosition, 1.0);
    position = gl_Position.xyz;
    texCoord = vTexCoord;
    normal = vNormal;
    color = vColor;
};

#pragma fragment
#version 460 core

in vec2 texCoord;
out vec4 fragColor;


float Circle(vec2 uv, vec2 offset, float radius, float smoothness)
{
    vec2 st = uv - 0.5 + offset;
    float radial = length(st);
    float result = smoothstep(radius, radius - radius * smoothness, radial * 2.0);
    return result;
}

void main()
{
    float circle = Circle(texCoord, vec2(0.0), 1.0, 0.1);
    fragColor = vec4(circle);
}