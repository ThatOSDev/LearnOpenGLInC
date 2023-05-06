// In your C file:
// ======================
float offset = 0.5f;
setFloat(programID, "xOffset", offset); // The programID you need to get before you call this. Examine learnopengl/shader_s.h

// In your vertex shader:
// ======================
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float xOffset;

void main()
{
    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
    ourColor = aColor;
}
