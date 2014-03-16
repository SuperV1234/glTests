// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVGL_VERTEXBUFFEROBJECT
#define SSVGL_VERTEXBUFFEROBJECT

#include "SSVGL/Common.hpp"

namespace ssvgl
{
	class VertexBufferObject
	{
		friend class VertexArrayObject;

		private:
			GLuint glId;

			inline void bind() const noexcept { glBindBuffer(GL_ARRAY_BUFFER, glId); }
			inline void buffer() const noexcept { }

		public:
			template<typename... TArgs> inline VertexBufferObject(TArgs&&... mArgs) noexcept
			{
				glGenBuffers(1, &glId);
				buffer(std::forward<TArgs>(mArgs)...);
			}
			inline ~VertexBufferObject() noexcept { glDeleteBuffers(1, &glId); }

			template<typename T, std::size_t TS> inline void buffer(const T(&mArray)[TS]) const noexcept
			{
				bind();
				glBufferData(GL_ARRAY_BUFFER, sizeof(mArray), mArray, GL_STATIC_DRAW);
			}
	};
}

#endif
