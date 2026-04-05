
//shader vertex
#version 430 core
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * aPos;
}


//shader fragment
#version 430 core
out vec4 FragColor;
uniform vec4 color;

void main()
{
	FragColor = color;
}
