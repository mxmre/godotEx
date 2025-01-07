#include "fractal_noise.h"

void ex::algorithm::noise::fractal::FractionalBrownianMotion::_bind_methods() {
	ClassDB::bind_compatibility_method(D_METHOD("get_noise1d", "x"), &FractionalBrownianMotion::get_noise1d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise2d", "x", "y"), &FractionalBrownianMotion::get_noise2d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise3d", "x", "y", "z"), &FractionalBrownianMotion::get_noise3d);

}

ex::algorithm::noise::fractal::FractionalBrownianMotion::FractionalBrownianMotion() :
		FractalNoise(){
}

real_t ex::algorithm::noise::fractal::FractionalBrownianMotion::get_noise1d(real_t x) {
	return this->_calculate_fractal([this, x](real_t freq) {
		return this->_basic_noise->get_noise1d(x * freq);
	});
}

real_t ex::algorithm::noise::fractal::FractionalBrownianMotion::get_noise2d(real_t x, real_t y) {
	return this->_calculate_fractal([this, x, y](real_t freq) {
		return this->_basic_noise->get_noise2d(x * freq, y * freq);
	});
}

real_t ex::algorithm::noise::fractal::FractionalBrownianMotion::get_noise3d(real_t x, real_t y, real_t z) {
	return this->_calculate_fractal([this, x, y, z](real_t freq) {
		return this->_basic_noise->get_noise3d(x * freq, y * freq, z * freq);
	});
}

void ex::algorithm::noise::fractal::FractalNoise::set_octaves(int32_t p_octaves) {
	_octaves = p_octaves;
}

void ex::algorithm::noise::fractal::FractalNoise::set_persistence(real_t p_persistence) {
	_persistence = p_persistence;
}

void ex::algorithm::noise::fractal::FractalNoise::set_lacunarity(real_t p_lacunarity) {
	_lacunarity = p_lacunarity;
}

void ex::algorithm::noise::fractal::FractalNoise::set_frequency(real_t p_frequency) {
	_frequency = p_frequency;
}

void ex::algorithm::noise::fractal::FractalNoise::set_amplitude(real_t p_amplitude) {
	_amplitude = p_amplitude;
}

int32_t ex::algorithm::noise::fractal::FractalNoise::get_octaves() const {
	return _octaves;
}

real_t ex::algorithm::noise::fractal::FractalNoise::get_persistence() const {
	return _persistence;
}

real_t ex::algorithm::noise::fractal::FractalNoise::get_lacunarity() const {
	return _lacunarity;
}

real_t ex::algorithm::noise::fractal::FractalNoise::get_frequency() const {
	return _frequency;
}

real_t ex::algorithm::noise::fractal::FractalNoise::get_amplitude() const {
	return _amplitude;
}

void ex::algorithm::noise::fractal::TurbulenceNoise::_bind_methods() {
	ClassDB::bind_compatibility_method(D_METHOD("get_noise1d", "x"), &TurbulenceNoise::get_noise1d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise2d", "x", "y"), &TurbulenceNoise::get_noise2d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise3d", "x", "y", "z"), &TurbulenceNoise::get_noise3d);
}

ex::algorithm::noise::fractal::TurbulenceNoise::TurbulenceNoise() :
		FractalNoise() {
}

real_t ex::algorithm::noise::fractal::TurbulenceNoise::get_noise1d(real_t x) {
	return this->_calculate_fractal([this, x](real_t freq) {
		return this->_basic_noise->get_noise1d(x * freq);
	});
}

real_t ex::algorithm::noise::fractal::TurbulenceNoise::get_noise2d(real_t x, real_t y) {
	return this->_calculate_fractal([this, x, y](real_t freq) {
		return this->_basic_noise->get_noise2d(x * freq, y * freq);
	});
}

real_t ex::algorithm::noise::fractal::TurbulenceNoise::get_noise3d(real_t x, real_t y, real_t z) {
	return this->_calculate_fractal([this, x, y, z](real_t freq) {
		return this->_basic_noise->get_noise3d(x * freq, y * freq, z * freq);
	});
}

void ex::algorithm::noise::fractal::FractalNoise::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_octaves", "octaves"), &FractalNoise::set_octaves);
	ClassDB::bind_method(D_METHOD("get_octaves"), &FractalNoise::get_octaves);
	ClassDB::bind_method(D_METHOD("set_persistence", "persistence"), &FractalNoise::set_persistence);
	ClassDB::bind_method(D_METHOD("get_persistence"), &FractalNoise::get_persistence);
	ClassDB::bind_method(D_METHOD("set_lacunarity", "lacunarity"), &FractalNoise::set_lacunarity);
	ClassDB::bind_method(D_METHOD("get_lacunarity"), &FractalNoise::get_lacunarity);
	ClassDB::bind_method(D_METHOD("set_frequency", "frequency"), &FractalNoise::set_frequency);
	ClassDB::bind_method(D_METHOD("get_frequency"), &FractalNoise::get_frequency);
	ClassDB::bind_method(D_METHOD("set_amplitude", "amplitude"), &FractalNoise::set_amplitude);
	ClassDB::bind_method(D_METHOD("get_amplitude"), &FractalNoise::get_amplitude);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "octaves"), "set_octaves", "get_octaves");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "persistence"), "set_persistence", "get_persistence");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lacunarity"), "set_lacunarity", "get_lacunarity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frequency"), "set_frequency", "get_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");
}

ex::algorithm::noise::fractal::FractalNoise::FractalNoise() :
		ShellNoise(),
		_octaves{ 1 },
		_persistence{ 1.0 },
		_lacunarity{ 1.0 },
		_frequency{ 1.0 },
		_amplitude{ 1.0 } {
}

void ex::algorithm::noise::fractal::BillowNoise::_bind_methods() {
	ClassDB::bind_compatibility_method(D_METHOD("get_noise1d", "x"), &BillowNoise::get_noise1d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise2d", "x", "y"), &BillowNoise::get_noise2d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise3d", "x", "y", "z"), &BillowNoise::get_noise3d);
}

ex::algorithm::noise::fractal::BillowNoise::BillowNoise() :
		FractalNoise() {
}

real_t ex::algorithm::noise::fractal::BillowNoise::get_noise1d(real_t x) {
	return this->_calculate_fractal([this, x](real_t freq) {
		return this->_basic_noise->get_noise1d(x * freq);
	});
}

real_t ex::algorithm::noise::fractal::BillowNoise::get_noise2d(real_t x, real_t y) {
	return this->_calculate_fractal([this, x, y](real_t freq) {
		return this->_basic_noise->get_noise2d(x * freq, y * freq);
	});
}

real_t ex::algorithm::noise::fractal::BillowNoise::get_noise3d(real_t x, real_t y, real_t z) {
	return this->_calculate_fractal([this, x, y, z](real_t freq) {
		return this->_basic_noise->get_noise3d(x * freq, y * freq, z * freq);
	});
}

void ex::algorithm::noise::fractal::HybridMultiFractal::_bind_methods() {
	ClassDB::bind_compatibility_method(D_METHOD("get_noise1d", "x"), &HybridMultiFractal::get_noise1d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise2d", "x", "y"), &HybridMultiFractal::get_noise2d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise3d", "x", "y", "z"), &HybridMultiFractal::get_noise3d);
}

ex::algorithm::noise::fractal::HybridMultiFractal::HybridMultiFractal() : FractalNoise() {
}

real_t ex::algorithm::noise::fractal::HybridMultiFractal::get_noise1d(real_t x) {
	return this->_calculate_fractal([this, x](real_t freq) {
		return this->_basic_noise->get_noise1d(x * freq);
	});
}

real_t ex::algorithm::noise::fractal::HybridMultiFractal::get_noise2d(real_t x, real_t y) {
	return this->_calculate_fractal([this, x, y](real_t freq) {
		return this->_basic_noise->get_noise2d(x * freq, y * freq);
	});
}

real_t ex::algorithm::noise::fractal::HybridMultiFractal::get_noise3d(real_t x, real_t y, real_t z) {
	return this->_calculate_fractal([this, x, y, z](real_t freq) {
		return this->_basic_noise->get_noise3d(x * freq, y * freq, z * freq);
	});
}
