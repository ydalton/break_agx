#ifndef VERT_GLSL_H_
#define VERT_GLSL_H_

const char *vert_glsl =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos, 1.0);\n"
	"}\n";

#endif /* VERT_GLSL_H_ */
