#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

#define NPARTICLES 5000

namespace screen {
	class Swarm
	{
		private:
			Particle* m_pParticles;
			int lastTime;

		public:
			Swarm();
			~Swarm();
			void update(int elapsed);

			const Particle * const getParticles() { return m_pParticles; };
	};
}
#endif
