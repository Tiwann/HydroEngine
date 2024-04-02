float Circle(vec2 uv, vec2 offset, float radius, float smoothness)
{
    vec2 st = uv - 0.5 + offset;
    float radial = length(st);
    float result = smoothstep(radius, radius - radius * smoothness, radial * 2.0);
    return result;
}
