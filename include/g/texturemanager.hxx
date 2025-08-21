#pragma once

#include<memory>
#include <unordered_map>
#include<g3d/texture.hxx>

namespace TextureManager {
        inline std::unordered_map<std::string, std::shared_ptr<Texture>> cache;

        std::shared_ptr<Texture> load(const std::string& path);
        std::shared_ptr<Texture> reload(const std::string& path);

        void unload(const std::string& path);
        void clear();
};
