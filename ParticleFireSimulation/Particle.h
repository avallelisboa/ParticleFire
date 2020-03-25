#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace screen {

	struct Particle
	{
		double m_x;
		double m_y;
	public:
		Particle();
		virtual ~Particle();
		void update(int interval);
	private:
		double m_speed;
		double m_direction;
		void init();
	};
}

#endif