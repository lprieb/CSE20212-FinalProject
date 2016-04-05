#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

using namespace std;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture(SDL_Window*, SDL_Renderer*, int SCREEN_WIDTH, int SCREEN_HEIGHT);

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(string path );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y, double wprop, double hprop, SDL_Rect* clip = NULL ); // Renders image with altered proportions.
		void render( int x, int y, SDL_Rect* clip = NULL); // Overloaded version renders image in original size
		void render( int x, int y, int width, int height, SDL_Rect* clip = NULL);
		//Gets image dimensions
		int getWidth();
		int getHeight();
		

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
		
		SDL_Window* gWindow ;
		SDL_Renderer* gRenderer;
		
		// Window Dimensions
		const int SCREEN_WIDTH;
		const int SCREEN_HEIGHT;
};

#endif