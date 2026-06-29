#pragma once

namespace Frisk {
	class Shader {
	public:
	    virtual ~Shader();

	    virtual void Bind() const;
		virtual void Unbind() const;

		static std::unique_ptr<Shader> Create(std::filesystem::path& a_VertexShaderPath, std::filesystem::path& a_FragmentShaderPath);
	};
}
