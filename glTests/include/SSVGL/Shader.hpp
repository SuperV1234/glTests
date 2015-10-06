// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVGL_SHADER
#define SSVGL_SHADER

#include "SSVGL/Common.hpp"

namespace ssvgl
{
    class Shader
    {
        friend class Program;

    private:
        const ShaderType type;
        const GLuint glId;

    public:
        inline Shader(const Shader&) noexcept = default;
        inline Shader(ShaderType mType)
            : type{mType}, glId{glCreateShader(GLenum(type))}
        {
        }
        inline Shader(ShaderType mType, ShaderSource& mSource) : Shader{mType}
        {
            compile(mSource);
        }
        inline ~Shader() noexcept { glDeleteShader(glId); }

        inline void compile(ShaderSource& mSource)
        {
            glShaderSource(glId, 1, mSource.getSourceData(), nullptr);
            glCompileShader(glId);

            GLint status;
            glGetShaderiv(glId, GL_COMPILE_STATUS, &status);

            char logBuffer[shaderLogBufferSize];
            glGetShaderInfoLog(glId, shaderLogBufferSize, nullptr, logBuffer);

            std::string compilationLog = std::string{logBuffer};
            if(!compilationLog.empty())
                ssvu::lo("Shader compilation log") << compilationLog
                                                   << std::endl;
        }
    };
}

#endif
