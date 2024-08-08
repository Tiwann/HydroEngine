float Disc(vec2 uv, vec2 offset, float radius, float smoothness)
{
    vec2 st = uv - 0.5 + offset;
    float radial = length(st);
    float result = smoothstep(radius, radius - radius * max(smoothness, 0.001), radial * 2.0);
    return result;
}

float Circle(vec2 uv, vec2 offset, float thickness, float smoothness)
{
    float disc0 = Disc(uv, offset, 1.0, smoothness);
    float disc1 = Disc(uv, offset, 1.0 - thickness, smoothness);
    return disc0 - disc1;
}
