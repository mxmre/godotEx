#include "improved_perlin_noise.h"
#include "core/string/print_string.h"
void ex::algorithm::noise::ImprovedPerlin::_bind_methods() {
	ClassDB::bind_compatibility_method(D_METHOD("get_noise2d_at", "x", "y"), &ImprovedPerlin::get_noise2d_at);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise3d_at", "x", "y", "z"), &ImprovedPerlin::get_noise3d_at);
	ClassDB::bind_static_method("ImprovedPerlin", D_METHOD("get_from_seed", "seed"), &ImprovedPerlin::get_from_seed);
}

real_t ex::algorithm::noise::ImprovedPerlin::lerp(real_t t, real_t a, real_t b) {
	return a + t * (b - a);
}

real_t ex::algorithm::noise::ImprovedPerlin::fade(real_t t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

real_t ex::algorithm::noise::ImprovedPerlin::grad(int8_t hash, real_t x, real_t y, real_t z) {
	int8_t h = hash & 15;
	double u = h < 8 ? x : y;
	double v = h < 4 ? y : (h == 12 || h == 14) ? x
												: z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void ex::algorithm::noise::ImprovedPerlin::init_noise() {
	this->_permutations.resize(256);
	for (int64_t i = 0; i < this->_permutations.size(); ++i) {
		this->_permutations.set(i, i);
	}
	ex::algorithm::shuffle(this->_permutations, _rng);
	print_line(this->_permutations.size());
	this->_permutations.append_array(this->_permutations);
	print_line(this->_permutations.size());
}

Ref<ex::algorithm::noise::ImprovedPerlin> ex::algorithm::noise::ImprovedPerlin::get_from_seed(uint64_t seed) {
	return Ref<ImprovedPerlin>(memnew(ImprovedPerlin(seed)));
}

ex::algorithm::noise::ImprovedPerlin::ImprovedPerlin() :
		BasicNoise() { this->init_noise(); }

ex::algorithm::noise::ImprovedPerlin::ImprovedPerlin(uint64_t seed) : BasicNoise(seed) {
	this->init_noise();
}

real_t ex::algorithm::noise::ImprovedPerlin::get_noise2d_at(real_t x, real_t y) {
	return this->get_noise3d_at(x, y, 0.0);
}

real_t ex::algorithm::noise::ImprovedPerlin::get_noise3d_at(real_t x, real_t y, real_t z) {
	// Находим координаты ячейки
	int64_t X = static_cast<int64_t>(x) & 255;
	int64_t Y = static_cast<int64_t>(y) & 255;
	int64_t Z = static_cast<int64_t>(y) & 255;

	// Находим относительные координаты внутри ячейки
	x -= Math::floor(x);
	y -= Math::floor(y);
	z -= Math::floor(z);

	// Вычисляем функции затухания
	real_t u = fade(x);
	real_t v = fade(y);
	real_t w = fade(z);

	// Хеширование координат углов куба
	int64_t A = this->_permutations[X] + Y;
	int64_t AA = this->_permutations[A] + Z;
	int64_t AB = this->_permutations[A + 1] + Z;
	int64_t B = this->_permutations[X + 1] + Y;
	int64_t BA = this->_permutations[B] + Z;
	int64_t BB = this->_permutations[B + 1] + Z;

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
