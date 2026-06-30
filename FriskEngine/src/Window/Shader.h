#pragma once

namespace Frisk {
	class Shader {
	public:
	    virtual ~Shader() = default;

	    virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Reload() = 0;

		virtual void SetFloat(const STRING& a_Name, float a_Value) const = 0;
		virtual void SetFloat2(const STRING& a_Name, const VEC2& a_Value) const = 0;
		virtual void SetFloat3(const STRING& a_Name, const VEC3& a_Value) const = 0;
		virtual void SetFloat4(const STRING& a_Name, const VEC4& a_Value) const = 0;

		virtual void SetMat3(const STRING& a_Name, const MAT3& a_Value) const = 0;
		virtual void SetMat4(const STRING& a_Name, const MAT4& a_Value) const = 0;

		virtual void SetBool(const STRING& a_Name, bool a_Value) const = 0;

		static std::unique_ptr<Shader> Create(const std::filesystem::path& a_VertexShaderPath, const std::filesystem::path& a_FragmentShaderPath);
	};
}
