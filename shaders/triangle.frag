#version 400
layout(location = 0) in struct vertex_in{
    vec4 vColor;
}IN;
layout (location = 0) out vec4 uFragColor;
void main() {
    // pass input color along without any modifications
    // (e.g, Phong lighting calculations could be done here)
    uFragColor = IN.vColor;
}