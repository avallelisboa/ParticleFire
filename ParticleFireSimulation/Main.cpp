#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <SDL_video.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#undef main
#include "Screen.h"
#include "Particle.h"
#include "Swarm.h"

using namespace std;
using namespace screen;

int main(int argc, int *argv[]) {

	srand(time(NULL));

	Screen screen;

	if(screen.init() == false){
		cout << "Error initialising SDL" << endl;
	}

	Swarm swarm;
	
	while (true) {
		//Update particles

		//Draw particles
		int elapsed = SDL_GetTicks(); //Returns the execution time

		//screen.clear();
		swarm.update(elapsed);

		double redSpeed = 0.0001;
		double greenSpeed = 0.0002;
		double blueSpeed = 0.0003;

		unsigned char red = (unsigned char)((1 + sin(elapsed * redSpeed)) * 128);
		unsigned char green = (unsigned char)((1 + cos(elapsed * greenSpeed)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * blueSpeed)) * 128);

		const Particle * const pParticles = swarm.getParticles();
		for (int i = 0; i < NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * screenWidth / 2;
			int y = particle.m_y  * screenWidth / 2 + screenHeigth / 2;

			screen.setPixel(x, y, red, green, blue);
		}
		
		screen.boxBlur();

		//Draw the screen
		screen.update();

		//Check for messages/events
		if (!screen.processEvents())break;
	}
	
	//screen.close();

	return 0;
}