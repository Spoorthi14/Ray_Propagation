#include "Emitter.h"

void Emitter::InitializeEmitter(std::pair<float,float> pos, float angle,std::vector<float> pol, float amplitude)
{
	_initialAngle = angle*3.14159/180.0;
	_emitterPosition = pos;
	this->SetPolarization(pol);
	_emitterAmplitude = amplitude;
}
