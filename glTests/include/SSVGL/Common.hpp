// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVGL_COMMON
#define SSVGL_COMMON

#include <string>
#include <iostream>
#include <SSVUtils/SSVUtils.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ssvgl
{
	class ShaderSource;
	class Shader;
	class Program;

	using Attribute = GLint;
	using Uniform = GLint;

	constexpr std::size_t shaderLogBufferSize{512};

	enum class DataType
	{
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		Float = GL_FLOAT,
		Double = GL_DOUBLE
	};

	enum class PrimitiveType
	{
		Triangles = GL_TRIANGLES,
		Lines = GL_LINES,
		Points = GL_POINTS,
	};

	enum class BufferType
	{
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY,
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY
	};

	enum class ShaderType
	{
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER
	};

	namespace Internal
	{
		inline void errorCallback(int mError, const char* mDescription)
		{
			ssvu::lo("GLFW error #" + ssvu::toStr(mError)) << mDescription << std::endl;
		}

		inline bool& getInitialized() noexcept	{ static bool initialized{false}; return initialized; }
		inline bool isInitialized() noexcept	{ return getInitialized(); }

		inline void deInitialize() noexcept
		{
			SSVU_ASSERT(isInitialized());

			glfwTerminate();
			getInitialized() = false;
		}
		inline void initialize() noexcept
		{
			SSVU_ASSERT(!isInitialized());

			glfwSetErrorCallback(&errorCallback);
			if(!glfwInit()) std::terminate();

			glewExperimental = GL_TRUE;

			getInitialized() = true;

			std::atexit(&deInitialize);
		}
	}
}

#endif
