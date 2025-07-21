#include<g3d/texturemanager.hxx>
#include<utils/files.hxx>

namespace TextureManager {
        std::shared_ptr<Texture> load(const std::string& path) {
		auto it = cache.find(path);
		if(it != cache.end())
			return it->second;

		auto tex = std::make_shared<Texture>();
		

		std::istream *in = Files::openi(path.c_str());
		if(!tex->load(*in)) {
			return nullptr;
		}

		return cache[path] = tex;
	}

        std::shared_ptr<Texture> reload(const std::string& path) {
		auto tex = std::make_shared<Texture>();

                std::istream *in = Files::openi(path.c_str());
                if(!tex->load(*in)) {
                        return nullptr;
                }

                return cache[path] = tex;
	}

        void unload(const std::string& path) {
		cache.erase(path);
	};
        void clear() {
		cache.clear();
	};
};
