#include <stdlib.h> 
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#include "vert.glsl.h"
#include "frag.glsl.h"

#define W_WIDTH 	1024
#define W_HEIGHT 	768
#define W_NAME		"GLDVD"

struct vertices {
	float *data;
	size_t size;
};

struct indices {
	int **data;
	size_t size;
};

struct application {
	GLFWwindow *window;
	int width, height;
	const char *name;
	unsigned int program;
	struct vertices verts;
	struct indices inds;
};


static void app_init(void) 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

static void app_destroy(void)
{
	glfwTerminate();
}

static void draw()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

static void app_loop(struct application *app)
{
	GLFWwindow *win = app->window;
	unsigned int vbo, vao, ebo;


	glfwMakeContextCurrent(win);

	if(glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialized GLEW!\n");
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, app->width, app->height);

	app->program = create_program(vert_glsl, frag_glsl);
	if(!app->program) {
		fprintf(stderr, "Failed to create program!\n");
		return;
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, app->verts.size, app->verts.data, 
		     GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 
			      NULL);
	glEnableVertexAttribArray(0);

	glUseProgram(app->program);

	glBindVertexArray(vao);

	while(!glfwWindowShouldClose(win)) {
		glfwPollEvents();
		draw();
		glfwSwapBuffers(win);
	}
}

static struct application *app_alloc(void)
{
	struct application *app;

	app = (struct application *) calloc(1, sizeof(*app));

	return app;
}

static void app_free(struct application *app)
{
	if(!app)
		return;
	free(app);
}


int main(void)
{
	struct application *app;

	float verts[] = {
		// first triangle
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, 0.5f, 0.0f, // top left
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
	};

	app_init();

	app = app_alloc();
	app->width = W_WIDTH;
	app->height = W_HEIGHT;
	app->name = W_NAME;
	// This is the offending line
	app->verts.data = (float *) verts;

	app->window = glfwCreateWindow(app->width, app->height, app->name, 
				       NULL, NULL);
	if(!app->window) {
		fprintf(stderr, "Failed to create window!\n");
		return -1;
	}

	app_loop(app);

	app_free(app);
	app_destroy();

	return 0;
}
