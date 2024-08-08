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


void main()
{
    mat4 mvp = uProjection * uView * uModel;
    vec4 newPosition = mvp * vec4(vPosition, 1.0);
    oPosition = newPosition.xyz;
    oTexCoord = vTexCoord;
    oNormal = vNormal;
    oColor = vColor;
    gl_Position = newPosition;
}