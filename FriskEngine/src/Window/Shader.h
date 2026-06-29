#pragma once

namespace Frisk {
	class Shader {
	public:
	    virtual ~Shader() = default;

	    virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::unique_ptr<Shader> Create(std::filesystem::path& a_VertexShaderPath, std::filesystem::path& a_FragmentShaderPath);
	};
}
