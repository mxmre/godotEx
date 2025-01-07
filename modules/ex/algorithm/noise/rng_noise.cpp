#include "rng_noise.h"

void ex::algorithm::noise::RNGBasedNoise::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_seed", "seed"), &RNGBasedNoise::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &RNGBasedNoise::get_seed);

	ClassDB::bind_method(D_METHOD("reset_noise"), &RNGBasedNoise::reset_noise);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"),
				 "set_seed", "get_seed");
}

void ex::algorithm::noise::RNGBasedNoise::reset_noise() {}

ex::algorithm::noise::RNGBasedNoise::RNGBasedNoise() :
		BasicNoise(),
		_rng(memnew(RandomNumberGenerator())) {
	this->_rng->randomize();
}

ex::algorithm::noise::RNGBasedNoise::RNGBasedNoise(uint64_t seed) :
		BasicNoise(),
		_rng(memnew(RandomNumberGenerator())) {
	this->set_seed(seed);
}

void ex::algorithm::noise::RNGBasedNoise::set_seed(uint64_t seed) {
	this->_rng->set_seed(seed);
}

uint64_t ex::algorithm::noise::RNGBasedNoise::get_seed() {
	return this->_rng->get_seed();
}

