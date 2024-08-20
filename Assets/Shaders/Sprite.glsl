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

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat3 uSpriteScale;
uniform vec2 uTiling;


void main()
{
    vec4 newPosition = uProjection * uView * uModel * vec4(uSpriteScale * vPosition, 1.0);
    oPosition = newPosition.xyz;
    oTexCoord = vTexCoord * uTiling;
    oNormal = vNormal;
    oColor = vColor;
    gl_Position = newPosition;
}

#pragma fragment
#version 460 core

in vec3 oPosition;
in vec2 oTexCoord;
in vec3 oNormal;
in vec4 oColor;

uniform sampler2D uTexture;
uniform vec4 uColorTint;

void main()
{
    vec4 colorTexture = texture(uTexture, oTexCoord);
    if(colorTexture.a <= 0.0001)
        discard;
    gl_FragColor = colorTexture * uColorTint;
}