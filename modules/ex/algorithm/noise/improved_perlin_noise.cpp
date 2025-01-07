#include "improved_perlin_noise.h"
#include "core/string/print_string.h"
void ex::algorithm::noise::ImprovedPerlinNoise::_bind_methods() {
	ClassDB::bind_compatibility_method(D_METHOD("get_noise1d", "x"), &ImprovedPerlinNoise::get_noise1d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise2d", "x", "y"), &ImprovedPerlinNoise::get_noise2d);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise3d", "x", "y", "z"), &ImprovedPerlinNoise::get_noise3d);
	ClassDB::bind_static_method("ImprovedPerlinNoise", D_METHOD("get_from_seed", "seed"), &ImprovedPerlinNoise::get_from_seed);
}

real_t ex::algorithm::noise::ImprovedPerlinNoise::lerp(real_t t, real_t a, real_t b) {
	return a + t * (b - a);
}

real_t ex::algorithm::noise::ImprovedPerlinNoise::fade(real_t t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

real_t ex::algorithm::noise::ImprovedPerlinNoise::grad(int16_t hash, real_t x, real_t y, real_t z) {
	int16_t h = hash & 15;
	double u = h < 8 ? x : y;
	double v = h < 4 ? y : (h == 12 || h == 14) ? x
												: z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void ex::algorithm::noise::ImprovedPerlinNoise::reset_noise() {
	this->_permutations.resize(256);
	for (int64_t i = 0; i < this->_permutations.size(); ++i) {
		this->_permutations.set(i, i);
	}
	ex::algorithm::shuffle(this->_permutations, _rng);
	this->_permutations.append_array(this->_permutations);
}

real_t ex::algorithm::noise::ImprovedPerlinNoise::get_noise1d(real_t x) {
	return this->get_noise3d(x, 0.0, 0.0);
	;
}

Ref<ex::algorithm::noise::ImprovedPerlinNoise> ex::algorithm::noise::ImprovedPerlinNoise::get_from_seed(uint64_t seed) {
	return Ref<ImprovedPerlinNoise>(memnew(ImprovedPerlinNoise(seed)));
}

ex::algorithm::noise::ImprovedPerlinNoise::ImprovedPerlinNoise() :
		RNGBasedNoise() { this->reset_noise(); }

ex::algorithm::noise::ImprovedPerlinNoise::ImprovedPerlinNoise(uint64_t seed) : RNGBasedNoise(seed) {
	this->reset_noise();
}

real_t ex::algorithm::noise::ImprovedPerlinNoise::get_noise2d(real_t x, real_t y) {
	return this->get_noise3d(x, y, 0.0);
}

real_t ex::algorithm::noise::ImprovedPerlinNoise::get_noise3d(real_t x, real_t y, real_t z) {
	// Находим координаты ячейки
	int16_t X = static_cast<int64_t>(Math::floor(x)) & 255;
	int16_t Y = static_cast<int64_t>(Math::floor(y)) & 255;
	int16_t Z = static_cast<int64_t>(Math::floor(z)) & 255;

	// Находим относительные координаты внутри ячейки
	x -= Math::floor(x);
	y -= Math::floor(y);
	z -= Math::floor(z);

	// Вычисляем функции затухания
	real_t u = fade(x);
	real_t v = fade(y);
	real_t w = fade(z);

	// Хеширование координат углов куба
	int16_t A = this->_permutations[X] + Y;
	int16_t AA = this->_permutations[A] + Z;
	int16_t AB = this->_permutations[A + 1] + Z;
	int16_t B = this->_permutations[X + 1] + Y;
	int16_t BA = this->_permutations[B] + Z;
	int16_t BB = this->_permutations[B + 1] + Z;

	// Градиентная интерполяция
	return lerp(w,
			lerp(v,
					lerp(u,
							grad(this->_permutations[AA], x, y, z),
							grad(this->_permutations[BA], x - 1, y, z)),
					lerp(u,
							grad(this->_permutations[AB], x, y - 1, z),
							grad(this->_permutations[BB], x - 1, y - 1, z))),
			lerp(v,
					lerp(u,
							grad(this->_permutations[AA + 1], x, y, z - 1),
							grad(this->_permutations[BA + 1], x - 1, y, z - 1)),
					lerp(u,
							grad(this->_permutations[AB + 1], x, y - 1, z - 1),
							grad(this->_permutations[BB + 1], x - 1, y - 1, z - 1))));
}
