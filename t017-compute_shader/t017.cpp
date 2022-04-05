/*
 ÷°ª∫≥Â,  ‰÷»æµΩŒ∆¿Ì
*/

#include "../common/common.out.h"
#include <chrono>

using namespace std;
#define WINDOW_WIDTH 4096
#define WINDOW_HEIGHT 4096

int g_size = WINDOW_WIDTH * WINDOW_HEIGHT * 4;

namespace
{
	typedef struct
	{
		GLuint vertex;
		GLuint fragment;
		GLuint geometry;
		GLuint compute;
	} shaders_t;

	char* loadFile(const char* fname, GLint& fSize)
	{
		ifstream::pos_type size;
		char* memblock;
		std::string text;

		// file read based on example in cplusplus.com tutorial
		ifstream file(fname, ios::in | ios::binary | ios::ate);
		if (file.is_open())
		{
			size = file.tellg();
			fSize = static_cast<GLuint>(size);
			memblock = new char[size];
			file.seekg(0, ios::beg);
			file.read(memblock, size);
			file.close();
			cout << "file " << fname << " loaded" << endl;
			text.assign(memblock);
		}
		else
		{
			cout << "Unable to open file " << fname << endl;
			exit(1);
		}
		return memblock;
	}

	void printShaderInfoLog(GLint shader)
	{
		int infoLogLen = 0;
		int charsWritten = 0;
		GLchar* infoLog;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

		// should additionally check for OpenGL errors here

		if (infoLogLen > 0)
		{
			infoLog = new GLchar[infoLogLen];
			// error check for fail to allocate memory omitted
			glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
			cout << "InfoLog:" << endl << infoLog << endl;
			delete[] infoLog;
		}

		// should additionally check for OpenGL errors here
	}

	void printLinkInfoLog(GLint prog)
	{
		int infoLogLen = 0;
		int charsWritten = 0;
		GLchar* infoLog;

		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

		// should additionally check for OpenGL errors here

		if (infoLogLen > 0)
		{
			infoLog = new GLchar[infoLogLen];
			// error check for fail to allocate memory omitted
			glGetProgramInfoLog(prog, infoLogLen, &charsWritten, infoLog);
			cout << "InfoLog:" << endl << infoLog << endl;
			delete[] infoLog;
		}
	}

	GLuint initshaders(GLenum type, const char* filename)
	{
		GLuint shader = glCreateShader(type);
		GLint compiled;
		char* ss;
		GLint slen;

		ss = loadFile(filename, slen);
		const char* cs = ss;

		glShaderSource(shader, 1, &cs, &slen);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			cout << "Shader not compiled." << endl;
			printShaderInfoLog(shader);
		}
		delete[] ss;

		return shader;
	}

	shaders_t loadShaders(const char* vert_path, const char* frag_path, const char* geom_path, const char* compute_path)
	{
		GLuint f = 0, v = 0, g = 0, c = 0;

		if (vert_path)
			v = initshaders(GL_VERTEX_SHADER, vert_path);
		if (frag_path)
			f = initshaders(GL_FRAGMENT_SHADER, frag_path);
		if (geom_path)
			g = initshaders(GL_GEOMETRY_SHADER, geom_path);
		if (compute_path)
			c = initshaders(GL_COMPUTE_SHADER, compute_path);

		shaders_t out;
		out.vertex = v;
		out.fragment = f;
		out.geometry = g;
		out.compute = c;

		return out;
	}

	void attachAndLinkProgram(GLuint program, shaders_t shaders)
	{
		if (shaders.vertex)
			glAttachShader(program, shaders.vertex);
		if (shaders.fragment)
			glAttachShader(program, shaders.fragment);
		if (shaders.geometry)
			glAttachShader(program, shaders.geometry);
		if (shaders.compute)
			glAttachShader(program, shaders.compute);
		glLinkProgram(program);
		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			cout << "Program did not link." << endl;
			printLinkInfoLog(program);
		}
	}
}

int genLinearBuffer(int size, GLenum format, GLuint* tex, GLuint* tbo)
{
	GLenum err;

	if ((*tbo) > 0)
		glDeleteBuffers(1, tbo); //delete previously created tbo

	glGenBuffers(1, tbo);

	glBindBuffer(GL_TEXTURE_BUFFER, *tbo);
	glBufferData(GL_TEXTURE_BUFFER, size, nullptr, GL_STATIC_DRAW);
	err = glGetError();

	if ((*tex) > 0)
		glDeleteTextures(1, tex); //delete previously created texture

	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_BUFFER, *tex);
	glTexBuffer(GL_TEXTURE_BUFFER, format, *tbo);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);

	err = glGetError();
	if (err > 0)
		cout << glewGetErrorString(err) << endl;
	return err;
}

void main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();


	//---------------------------------------------load compute shader
	auto shaderSet = loadShaders(nullptr, nullptr, nullptr, "test_compute_shader.com.glsl");

	auto program = glCreateProgram();

	attachAndLinkProgram(program, shaderSet);

	Shader shader(program);
	shader.Use();


	auto t1 = std::chrono::high_resolution_clock::now();

	int num = 1024 * 1024;
	shader.setUniform1i("u_num", num);

	GLuint buf_tex = 0u, tbo = 0u;
	genLinearBuffer(sizeof(GLuint) * num, GL_R32F, &buf_tex, &tbo);

	glBindImageTexture(0, buf_tex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	glDispatchCompute(num / 256, 1, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);


	//---------------------------------------------map buffer to cpu
	glBindBuffer(GL_TEXTURE_BUFFER, tbo);
	GLfloat* buf = static_cast<GLfloat*>(glMapBufferRange(
		GL_TEXTURE_BUFFER, 0, sizeof(GLfloat) * num, GL_MAP_READ_BIT));

	vector<GLfloat> vec(num);

	for (int kk = 0; kk < num; kk++)
	{
		vec[kk] = buf[kk];
	}

	glUnmapBuffer(GL_TEXTURE_BUFFER);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);

	auto t2 = std::chrono::high_resolution_clock::now();

	vector<GLfloat> vec2(num);
	for (int kk = 0; kk < num; kk++)
	{
		float val = kk * 2 + 1;

		for (int j = 0; j < 1000; j++)
			val = sqrtf(val + 7);
		vec2[kk] = val;
	}

	auto t3 = std::chrono::high_resolution_clock::now();


	std::cout << "  t1:   " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
		<< "    t2:    " << std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();


	//---------------------------------------------check valid
	for (int kk = 0; kk < num; kk++)
	{
		if (abs(vec[kk] - vec2[kk]) > 1e-5)
			std::cout << kk << "     " << vec[kk] << "    " << vec2[kk] << endl;
	}


	std::cout << "\nTHE END\n";
	getchar();
}
