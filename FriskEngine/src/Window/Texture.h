#pragma once

namespace Frisk {
	class Texture {
	public:
	    virtual ~Texture();

    	virtual void Bind() const;
    	virtual void Unbind() const;

    	static std::unique_ptr<Texture> Create(std::filesystem::path& a_TexturePath);
    	static std::unique_ptr<Texture> Create(); // empty texture, with solid color

	};
}
