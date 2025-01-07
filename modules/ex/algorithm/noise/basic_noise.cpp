#include "basic_noise.h"

void ex::algorithm::noise::BasicNoise::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_noise2dv", "point"), &BasicNoise::get_noise2dv);
	ClassDB::bind_method(D_METHOD("get_noise3dv", "point"), &BasicNoise::get_noise3dv);
	ClassDB::bind_method(D_METHOD("get_noise1d", "x"), &BasicNoise::get_noise1d);
	ClassDB::bind_method(D_METHOD("get_noise2d", "x", "y"), &BasicNoise::get_noise2d);
	ClassDB::bind_method(D_METHOD("get_noise3d", "x", "y", "z"), &BasicNoise::get_noise3d);
}

ex::algorithm::noise::BasicNoise::BasicNoise() {
}

real_t ex::algorithm::noise::BasicNoise::get_noise2dv(Vector2 point) {
	return this->get_noise2d(point.x, point.y);
}

real_t ex::algorithm::noise::BasicNoise::get_noise3dv(Vector3 point) {
	return this->get_noise3d(point.x, point.y, point.z);
}
