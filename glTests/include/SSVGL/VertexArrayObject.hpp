// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVGL_VERTEXARRAYOBJECT
#define SSVGL_VERTEXARRAYOBJECT

#include "SSVGL/Common.hpp"

namespace ssvgl
{
	class VertexArrayObject
	{
		private:
			GLuint glId;

			inline void bind() const noexcept { glBindVertexArray(glId); }

		public:
			inline VertexArrayObject() noexcept { glGenVertexArrays(1, &glId); }
			inline ~VertexArrayObject() noexcept { glDeleteVertexArrays(1, &glId); }

			inline void bindAttribute(const Attribute& mAttribute, const VertexBufferObject& mVBO, DataType mType,
				std::size_t mSize, std::size_t mStride = 0, std::size_t mOffset = 0, bool mNormalized = GL_FALSE) const noexcept
			{
				bind(); mVBO.bind();
				glEnableVertexAttribArray(mAttribute);
				glVertexAttribPointer(mAttribute, mSize, GLenum(mType), mNormalized, mStride, reinterpret_cast<GLvoid*>(mOffset));
			}
	};
}

#endif
