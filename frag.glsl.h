#ifndef FRAG_GLSL_H_
#define FRAG_GLSL_H_

const char *frag_glsl =
	"#version 330 core\n"
	"\n"
	"out vec4 FragColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\n";

#endif /* FRAG_GLSL_H_ */
