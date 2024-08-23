#pragma vertex
#version 460 core
#include "DefaultVertex.glsl"

#pragma fragment
#version 460 core
#include "Shapes.glsl" 

in vec3 oPosition;
in vec2 oTexCoord;
in vec3 oNormal;
in vec4 oColor;

uniform float uThickness;
uniform float uSmoothness;

out vec4 fragColor;

void main()
{
    float circle = Circle(oTexCoord, vec2(0.0), uThickness, uSmoothness);
    vec4 coloredCirlcle = oColor * circle;
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}