#pragma once

namespace Frisk {
	class Texture {
	public:
		virtual ~Texture() = default;

    	virtual void Bind() const = 0;
    	virtual void Unbind() const = 0;

    	static std::unique_ptr<Texture> Create(const std::filesystem::path& a_TexturePath);
    	static std::unique_ptr<Texture> Create(); // empty texture, with solid color

	};
}
