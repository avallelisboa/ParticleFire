#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <SDL_video.h>
#include "Screen.h"

using namespace std;

namespace screen {
	Screen::Screen(): m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL){}

	Screen::~Screen() {
		delete[] m_buffer1;
		delete[] m_buffer2;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	bool Screen::init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			cout << "SDL init failed" << endl;
			return false;
		}

		//Creates a window. It gives the window a name, defines de 'x' and 'y' position,
		//defines de width and the heigth and sets the windows to be shown
		m_window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeigth, SDL_WINDOW_SHOWN);

		if (m_window == NULL) {
			SDL_Quit();
			return false;
		}

		//Creates a renderer. It assigns the renderer to a window
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		//Creates a texture. It assigns the texture to a renderer
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, screenWidth, screenHeigth);

		if (m_renderer == NULL) {
			cout << "Renderer could not be created" << endl;
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyTexture(m_texture);
			SDL_Quit();
			return false;
		}
		if (m_texture == NULL) {
			cout << "Texture could not be created" << endl;
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyTexture(m_texture);
			SDL_Quit();
			return false;
		}

		m_buffer1 = new Uint32[pixelsNumber];
		m_buffer2 = new Uint32[pixelsNumber];

		memset(m_buffer1, 0, pixelsNumber * sizeof(Uint32));
		memset(m_buffer2, 0, pixelsNumber * sizeof(Uint32));
		
		return true;
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeigth) {
			return;
		}

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		m_buffer1[(y * screenWidth) + x] = color;
	}

	bool Screen::processEvents() {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}

	void Screen::boxBlur() {
		//Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer1
		Uint32 *temp = m_buffer1;
		m_buffer1 = m_buffer2;
		m_buffer2 = temp;		

		for (int y = 0; y < screenHeigth; y++) {
			for (int x = 0; x < screenWidth; x++) {

				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++) {
					for (int col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < screenWidth && currentY >= 0 && currentY < screenHeigth) {
							Uint32 color = m_buffer2[currentY * screenWidth + currentX];
							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}

				Uint8 red = redTotal/9;
				Uint8 green = greenTotal/9;
				Uint8 blue = blueTotal/9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	void Screen::update() {
		SDL_UpdateTexture(m_texture, NULL, m_buffer1, screenWidth * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	void Screen::close() {
		delete[] m_buffer1;
		delete[] m_buffer2;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
}