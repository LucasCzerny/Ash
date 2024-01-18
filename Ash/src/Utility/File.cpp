#include "pch.h"
#include "File.h"

#include "Core/Assert.h"

namespace Ash::Utility
{
    std::string ReadFile(const fs::path& filePath)
    {
        std::ifstream file(filePath, std::ios::ate | std::ios::binary);
        ASSERT(file.is_open(), "Failed to open file ", filePath);

        size_t size = (size_t)file.tellg();

        std::string content(size, ' ');
        file.seekg(0);
        file.read(content.data(), size);

        return content;
    }
}