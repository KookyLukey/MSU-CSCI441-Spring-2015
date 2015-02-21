#version 330

in vec2 position;
uniform mat4 projMatrix;

void main() {
  gl_Position = projMatrix *  vec4(position.x, position.y, 0, 1);

}
