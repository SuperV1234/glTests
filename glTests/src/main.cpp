#include <thread>
#include <string>
#include <iostream>
#include <SSVUtils/SSVUtils.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SSVGL/SSVGL.hpp>

ssvgl::ShaderSource vertexShaderSource{R"(
	#version 330

	in vec2 inVSPosition;
	in vec3 inVSColor;
	out vec3 inFSColor;

	void main()
	{
		inFSColor = inVSColor;
		gl_Position = vec4(inVSPosition, 0.0, 1.0);
	}
)"};

ssvgl::ShaderSource fragmentShaderSource{R"(
	#version 330

	in vec3 inFSColor;
	out vec4 outFSColor;

	void main()
	{
		float lerpValue = gl_FragCoord.y / 500.f;
		outFSColor = mix(vec4(inFSColor, 1.f), vec4(0.2f, 0.2f, 0.2f, 1.f), lerpValue * sin(gl_FragCoord.x / 15.f));
	}
)"};

int main()
{
	ssvgl::Window window{800, 600, "ssvgl tests", false};

	ssvgl::Shader vertexShader{ssvgl::ShaderType::Vertex, vertexShaderSource};
	ssvgl::Shader fragmentShader{ssvgl::ShaderType::Fragment, fragmentShaderSource};
	ssvgl::Program program{vertexShader, fragmentShader};

	GLfloat vertices[]
	{
		0.f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f,

		0.1f, 0.5f, 1.f,
		0.8f, 1.f, 0.3f,
		0.5f, 0.5f, 0.1f
	};
	ssvgl::VertexBufferObject vbo{vertices};



	/*GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[]{
		0, 1, 2,
		2, 3, 0
	};
!glfwWindowShouldClose(window)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);*/




	ssvgl::VertexArrayObject vao;
	vao.bindAttribute(program.getAttribute("inVSPosition"), vbo, ssvgl::DataType::Float, 2, 0, 0);
	vao.bindAttribute(program.getAttribute("inVSColor"), vbo, ssvgl::DataType::Float, 3, 0, 3 * sizeof(GLfloat));

	while(!window.shouldClose())
	{
		glfwPollEvents();
		if(glfwGetKey(window.getGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) window.close();

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.display();
	}
}
