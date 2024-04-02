#pragma vertex 
#version 460 core

in vec3 vPosition;
in vec2 vTexCoord;
in vec3 vNormal;
in vec4 vColor;

out vec3 oPosition;
out vec2 oTexCoord;
out vec3 oNormal;
out vec4 oColor;

uniform mat4 uModelMatrix;

void main()
{
    oPosition = (uModelMatrix * vec4(vPosition, 1.0)).xyz;
    oTexCoord = vTexCoord;
    oNormal = vNormal;
    oColor = vColor;
    gl_Position = vec4(oPosition, 1.0);
};

#pragma fragment
#version 460 core

in vec3 oPosition;
in vec2 oTexCoord;
in vec3 oNormal;
in vec4 oColor;

uniform sampler2D uTexture;

void main()
{
    vec4 colorTexture = texture(uTexture, oTexCoord);
    gl_FragColor = colorTexture;
}