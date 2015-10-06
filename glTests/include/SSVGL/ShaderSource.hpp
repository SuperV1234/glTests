// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVGL_SHADERSOURCE
#define SSVGL_SHADERSOURCE

#include "SSVGL/Common.hpp"

namespace ssvgl
{
    class ShaderSource
    {
    private:
        std::string sourceStr;
        const char* sourceData;

    public:
        inline ShaderSource(std::string mStr)
            : sourceStr{std::move(mStr)}, sourceData{sourceStr.c_str()}
        {
        }
        inline const char** getSourceData() noexcept { return &sourceData; }
    };
}

#endif
