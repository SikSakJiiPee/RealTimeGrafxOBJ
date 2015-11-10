#include <SDL.h>
#include <stdio.h>
#include <glew.h>
#include <glm.hpp>

///////////////////
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

static void quit(int code);
static void handleKeyDown(int code);
static void processEvents();
static void drawScreen(SDL_Window* ptr);
static void setupOpengl(int w, int h);

int main(int argc, char** argv)
{
	//const SDL_VideoInfo info = NULL; SDL1.2
	int width = 0;
	int height = 0;
	int bpp = 0;
	int flags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "\nVideo initialization failed";
		quit(1);
	}

	width = 640;
	height = 480;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5); // at least 5bpp
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//flags = SDL_OPENGL;


	SDL_Window *mWindow = SDL_CreateWindow("SDL project",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_OPENGL);// | SDL_WINDOW_FULLSCREEN
	if (mWindow == NULL)//Verify window
		quit(1);

	SDL_GLContext renderingContex = SDL_GL_CreateContext(mWindow);
	if (renderingContex == NULL)//Verify rendering contex
		quit(1);

	setupOpengl(width, height);

	//Main loop
	while (true)
	{
		processEvents();
		drawScreen(mWindow);
	}

	return 0;
}



static void quit(int code)
{
	SDL_Quit();
	exit(code);
}
static void handleKeyDown(SDL_Keysym* keysym)
{
	switch (keysym->sym)
	{
	case SDLK_ESCAPE:
		quit(0);
		break;
	default:
		break;
	}
}
static void processEvents()
{
	SDL_Event mEvent;
	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
		case SDL_KEYDOWN:
			handleKeyDown(&mEvent.key.keysym);
			break;
		case SDL_QUIT:
			quit(0);
			break;
		}
	}
}
static void drawScreen(SDL_Window* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, -0.5, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0.5, 0, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0.5, 0);
	glEnd();

	SDL_GL_SwapWindow(window);
}
static void setupOpengl(int width, int height)
{
	glClearColor(0, 0, 0, 0);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

