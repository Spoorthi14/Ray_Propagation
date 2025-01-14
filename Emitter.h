#include <utility>

#ifndef EMITTER_H_
#define EMITTER_H_
class Emitter
{
	public:
	Emitter() : _initialAngle(0.0)
	{
		_emitterPosition.first = 0.0;
		_emitterPosition.second = 0.0;
	}
	float _initialAngle; //initial angle with respect to horizontal, entered as degrees
	std::pair<float,float> _emitterPosition; //(x,z) position
	void InitializeEmitter(float,float,float); //set emitter x, z, and initial angle
};

#endif
