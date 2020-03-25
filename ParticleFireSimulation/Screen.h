#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <SDL_video.h>

#ifndef SCREEN_H_
#define SCREEN_H_
//Screen dimensions
#define screenWidth 800
#define screenHeigth 600
#define pixelsNumber screenWidth * screenHeigth

namespace screen {
	class Screen {
		private:
			SDL_Window *m_window;
			SDL_Renderer *m_renderer;
			SDL_Texture *m_texture;
			Uint32 *m_buffer1;
			Uint32 *m_buffer2;
		public:
			Screen();
			~Screen();
			bool init();
			void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
			bool processEvents();
			void update();
			void close();
			void boxBlur();
	};
}
#endif

