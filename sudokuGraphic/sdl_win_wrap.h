#ifndef SDL_WIN_WRAP
#define SDL_WIN_WRAP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDL_Win_Wrap
{
	public:
	SDL_Win_Wrap(int nScreenWidth = 640, int nScreenHeight = 480);
	~SDL_Win_Wrap();
	int getScreenWidth();
	int getScreenHeight();
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	bool init();
	void close();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	//The window we'll be rendering to
	SDL_Window* gWindow ;

	//The window renderer
	SDL_Renderer* gRenderer;
};

#endif