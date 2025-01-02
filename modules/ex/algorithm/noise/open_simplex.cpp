#include "open_simplex.h"

void ex::algorithm::noise::OpenSimplex::_bind_methods() {
	ClassDB::bind_compatibility_method(D_METHOD("get_noise2d_at", "x", "y"), &OpenSimplex::get_noise2d_at);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise3d_at", "x", "y", "z"), &OpenSimplex::get_noise3d_at);
	ClassDB::bind_static_method("OpenSimplex", D_METHOD("get_from_seed", "seed"), &OpenSimplex::get_from_seed);
}

void ex::algorithm::noise::OpenSimplex::_init_noise() {
	this->_permutations.resize(PSIZE);

	for (int64_t i = 0; i < PSIZE; ++i) {
		this->_permutations.set(i, i);
	}
	ex::algorithm::shuffle(this->_permutations, this->_rng);
}

Ref<ex::algorithm::noise::OpenSimplex> ex::algorithm::noise::OpenSimplex::get_from_seed(uint64_t seed) {
	return Ref<OpenSimplex>(memnew(OpenSimplex(seed)));
}

ex::algorithm::noise::OpenSimplex::OpenSimplex() :
		BasicNoise() {

}

ex::algorithm::noise::OpenSimplex::OpenSimplex(uint64_t seed) :
		BasicNoise(seed) {
	
}

real_t ex::algorithm::noise::OpenSimplex::get_noise2d_at(real_t x, real_t y) {
	// Преобразование координат
	real_t stretchOffset = (x + y) * STRETCH_2D;
	real_t xs = x + stretchOffset;
	real_t ys = y + stretchOffset;

	// Целочисленные координаты базовой ячейки
	int xsb = floor(xs);
	int ysb = floor(ys);

	// Относительные координаты внутри ячейки
	real_t xins = xs - xsb;
	real_t yins = ys - ysb;

	// Вклады от вершин
	real_t value = 0;

	real_t squishOffset = (xsb + ysb) * SQUISH_2D;
	real_t dx0 = x - (xsb + squishOffset);
	real_t dy0 = y - (ysb + squishOffset);

	// Вычисление вкладов от каждой вершины
	for (int i = 0; i < 4; i++) {
		int vertex = i & 3;
		real_t dx = dx0 + (vertex & 2);
		real_t dy = dy0 + ((vertex >> 1) & 2);

		real_t attn = 2 - dx * dx - dy * dy;
		if (attn > 0) {
			int pxi = xsb + (vertex & 2);
			int pyi = ysb + ((vertex >> 1) & 2);

			int gi = this->_permutations[(pxi & PMASK) + this->_permutations[pyi & PMASK]] & 7;

			attn *= attn;
			value += attn * attn * (GRAD_2D[gi * 2] * dx + GRAD_2D[gi * 2 + 1] * dy);
		}
	}

	return value * 27;
}

real_t ex::algorithm::noise::OpenSimplex::get_noise3d_at(real_t x, real_t y, real_t z) {
	// Преобразование координат
	real_t stretchOffset = (x + y + z) * STRETCH_3D;
	real_t xs = x + stretchOffset;
	real_t ys = y + stretchOffset;
	real_t zs = z + stretchOffset;

	// Целочисленные координаты базовой ячейки
	int xsb = floor(xs);
	int ysb = floor(ys);
	int zsb = floor(zs);

	// Относительные координаты внутри ячейки
	real_t xins = xs - xsb;
	real_t yins = ys - ysb;
	real_t zins = zs - zsb;

	// Вклады от вершин
	real_t value = 0;

	real_t squishOffset = (xsb + ysb + zsb) * SQUISH_3D;
	real_t dx0 = x - (xsb + squishOffset);
	real_t dy0 = y - (ysb + squishOffset);
	real_t dz0 = z - (zsb + squishOffset);

	// Вычисление вкладов от каждой вершины
	for (int i = 0; i < 8; i++) {
		int vertex = i & 7;
		real_t dx = dx0 + (vertex & 4);
		real_t dy = dy0 + ((vertex >> 1) & 4);
		real_t dz = dz0 + ((vertex >> 2) & 4);

		real_t attn = 2 - dx * dx - dy * dy - dz * dz;
		if (attn > 0) {
			int pxi = xsb + (vertex & 4);
			int pyi = ysb + ((vertex >> 1) & 4);
			int pzi = zsb + ((vertex >> 2) & 4);

			int gi = this->_permutations[(pxi & PMASK) + this->_permutations[(pyi & PMASK) + this->_permutations[pzi & PMASK]]] % 12;

			attn *= attn;
			value += attn * attn * (GRAD_3D[gi * 3] * dx + GRAD_3D[gi * 3 + 1] * dy + GRAD_3D[gi * 3 + 2] * dz);
		}
	}

	return value * 32;
}
// Инициализация градиентов
const Vector<real_t> ex::algorithm::noise::OpenSimplex::GRAD_2D = {
	5, 2, 2, 5,
	-5, 2, -2, 5,
	5, -2, 2, -5,
	-5, -2, -2, -5
};

const Vector<real_t> ex::algorithm::noise::OpenSimplex::GRAD_3D = {
	1, 1, 0, -1, 1, 0, 1, -1, 0, -1, -1, 0,
	1, 0, 1, -1, 0, 1, 1, 0, -1, -1, 0, -1,
	0, 1, 1, 0, -1, 1, 0, 1, -1, 0, -1, -1
};
