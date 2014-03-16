// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVGL_PROGRAM
#define SSVGL_PROGRAM

#include "SSVGL/Common.hpp"

namespace ssvgl
{
	class Program
	{
		private:
			const GLuint glId{glCreateProgram()};
			std::vector<Shader> attached;

		public:
			inline Program() = default;
			inline Program(const Shader& mVertex)
			{
				SSVU_ASSERT(mVertex.type == ShaderType::Vertex);
				attach(mVertex);
				link(); use();
			}
			inline Program(const Shader& mVertex, const Shader& mFragment)
			{
				SSVU_ASSERT(mVertex.type == ShaderType::Vertex);
				SSVU_ASSERT(mFragment.type == ShaderType::Fragment);
				attach(mVertex); attach(mFragment);
				link(); use();
			}
			inline Program(const Shader& mVertex, const Shader& mFragment, const Shader& mGeometry)
			{
				SSVU_ASSERT(mVertex.type == ShaderType::Vertex);
				SSVU_ASSERT(mFragment.type == ShaderType::Fragment);
				SSVU_ASSERT(mGeometry.type == ShaderType::Geometry);
				attach(mVertex); attach(mFragment); attach(mGeometry);
				link(); use();
			}
			inline ~Program() noexcept { glDeleteProgram(glId); }

			inline void attach(const Shader& mShader) noexcept
			{
				glAttachShader(glId, mShader.glId);
				attached.emplace_back(mShader);
			}
			inline void link() noexcept
			{
				glLinkProgram(glId);
				for(const auto& s : attached) glDetachShader(glId, s.glId);
			}
			inline void use() noexcept { glUseProgram(glId); }

			inline Attribute getAttribute(const std::string& mName) const noexcept
			{
				return glGetAttribLocation(glId, mName.c_str());
			}
	};
}

#endif
