#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "camera2D.h"

std::string get_file_contents(const char *filename);

class Shader
{
private:
	GLuint ID;

public:
	static void initDefaultShader(const char *v, const char *f) { default_shader.load(v, f); }
	static Shader default_shader;

	Shader() {}
	Shader(const char *vertexFile, const char *fragmentFile);

	~Shader() {destroy();}

	void load(const char *vertexFile, const char *fragmentFile);
	void use() const;
	void destroy() const;
	operator GLuint() const { return ID; }

	template <typename T>
	void setScalar(const char *name, T value) const;

	void setVec2(const char *name, float value1, float value2) const;
	void setVec2(const char *name, float *values) const;
	void setVec2(const char *name, const glm::vec2 &v) const;

	void setVec3(const char *name, float value1, float value2, float value3) const;
	void setVec3(const char *name, float *values) const;
	void setVec3(const char *name, const glm::vec3 &v) const;

	void setMat2(const char *name, float *m) const;
	void setMat2(const char *name, const glm::mat2 &m) const;

	void setMat2x3(const char *name, float *m) const;
	void setMat2x3(const char *name, const glm::mat2x3 &m) const;

	void setMat3x2(const char *name, float *m) const;
	void setMat3x2(const char *name, const glm::mat3x2 &m) const;

	void setMat3(const char *name, float *m) const;
	void setMat3(const char *name, const glm::mat3 &m) const;

	void setMat4(const char *name, float *m) const;
	void setMat4(const char *name, const glm::mat4 &m) const;

	void setCamera(const Camera2D &c) const;

private:
	void compileErrors(unsigned int shader, const char *type) const;
};