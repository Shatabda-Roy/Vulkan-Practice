#version 400
layout(std140, set = 0, binding = 0) uniformbuffer{
    mat4 projection_matrix;
    mat4 view_matrix;
    mat4 model_matrix;
}UBO;
layout(location = 0 ) in vec4 pos;
layout(location = 1) in vec3 color;
layout(location = 0) out struct vertex_out {
    vec4 vColor;
}OUT;
void main() {
    // combine the matrices.
    mat4 modelView = UBO.model_matrix * UBO.view_matrix;
    // transform position by matrices.
    gl_Position = pos * (modelView * UBO.projection_matrix);
    // pass input color to the next stage.
    OUT.vColor = vec4(color, 1.0);
}