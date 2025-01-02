#include "basic_noise.h"

void ex::algorithm::noise::BasicNoise::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_seed", "seed"), &BasicNoise::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &BasicNoise::get_seed);

	ClassDB::bind_method(D_METHOD("get_noise2d_at_v", "point"), &BasicNoise::get_noise2d_at_v);
	ClassDB::bind_method(D_METHOD("get_noise3d_at_v", "point"), &BasicNoise::get_noise3d_at_v);
	ClassDB::bind_method(D_METHOD("get_noise2d_at", "x", "y"), &BasicNoise::get_noise2d_at);
	ClassDB::bind_method(D_METHOD("get_noise3d_at", "x", "y", "z"), &BasicNoise::get_noise3d_at);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"),
				 "set_seed", "get_seed");
}

void ex::algorithm::noise::BasicNoise::_init_noise() {}

ex::algorithm::noise::BasicNoise::BasicNoise() :
		_rng(memnew(RandomNumberGenerator())) {
	this->_rng->randomize();
	this->_init_noise();
}

ex::algorithm::noise::BasicNoise::BasicNoise(uint64_t seed) :
		_rng(memnew(RandomNumberGenerator())) {
	this->set_seed(seed);
	this->_init_noise();
}

void ex::algorithm::noise::BasicNoise::set_seed(uint64_t seed) {
	this->_rng->set_seed(seed);
}

uint64_t ex::algorithm::noise::BasicNoise::get_seed() {
	return this->_rng->get_seed();
}

real_t ex::algorithm::noise::BasicNoise::get_noise2d_at_v(Vector2 point) {
	return this->get_noise2d_at(point.x, point.y);
}

real_t ex::algorithm::noise::BasicNoise::get_noise3d_at_v(Vector3 point) {
	return this->get_noise3d_at(point.x, point.y, point.z);
}
