#include "open_simplex.h"
#include "core/string/print_string.h"

void ex::algorithm::noise::OpenSimplex::_bind_methods() {
	ClassDB::bind_compatibility_method(D_METHOD("get_noise2d_at", "x", "y"), &OpenSimplex::get_noise2d_at);
	ClassDB::bind_compatibility_method(D_METHOD("get_noise3d_at", "x", "y", "z"), &OpenSimplex::get_noise3d_at);
	ClassDB::bind_static_method("OpenSimplex", D_METHOD("get_from_seed", "seed"), &OpenSimplex::get_from_seed);
}

void ex::algorithm::noise::OpenSimplex::init_noise() {
	print_line(this->_permutations.size());
	this->_permutations.resize(PSIZE);
	print_line(this->_permutations.size());
	for (int64_t i = 0; i < PSIZE; ++i) {
		this->_permutations.set(i, i);
	}
	print_line(this->_permutations.size());
	ex::algorithm::shuffle(this->_permutations, this->_rng);
	print_line(this->_permutations.size());
}

Ref<ex::algorithm::noise::OpenSimplex> ex::algorithm::noise::OpenSimplex::get_from_seed(uint64_t seed) {
	return Ref<OpenSimplex>(memnew(OpenSimplex(seed)));
}

ex::algorithm::noise::OpenSimplex::OpenSimplex() :
		BasicNoise() {
	this->init_noise();
}

ex::algorithm::noise::OpenSimplex::OpenSimplex(uint64_t seed) :
		BasicNoise(seed) {
	this->init_noise();
}

real_t ex::algorithm::noise::OpenSimplex::get_noise2d_at(real_t x, real_t y) {
	// Place input coordinates onto grid.
	double stretchOffset = (x + y) * STRETCH_2D;
	double xs = x + stretchOffset;
	double ys = y + stretchOffset;

	// Floor to get grid coordinates of rhombus (stretched square) super-cell origin.
	int xsb = floor(xs);
	int ysb = floor(ys);

	// Compute grid coordinates relative to rhombus origin.
	double squishOffset = (xsb + ysb) * SQUISH_2D;
	double dx0 = x - (xsb + squishOffset);
	double dy0 = y - (ysb + squishOffset);

	double value = 0;

	// Sum contributions from each corner
	for (int i = 0; i < 4; i++) {
		int vertex = i & 3;
		double dx = dx0 + (vertex & 2);
		double dy = dy0 + ((vertex >> 1) & 2);

		double attn = 0.5 - dx * dx - dy * dy;
		if (attn > 0) {
			int pxi = xsb + (vertex & 2);
			int pyi = ysb + ((vertex >> 1) & 2);

			print_line("1");
			int gi = _permutations[(pxi & PMASK) + _permutations[pyi & PMASK]] % 12;
			print_line("2");

			attn *= attn;
			value += attn * attn * (GRAD_2D[gi][0] * dx + GRAD_2D[gi][1] * dy);
		}
	}

	return value * 70;
}

real_t ex::algorithm::noise::OpenSimplex::get_noise3d_at(real_t x, real_t y, real_t z) {
	// Place input coordinates on simplectic honeycomb.
	double stretchOffset = (x + y + z) * STRETCH_3D;
	double xs = x + stretchOffset;
	double ys = y + stretchOffset;
	double zs = z + stretchOffset;

	int xsb = floor(xs);
	int ysb = floor(ys);
	int zsb = floor(zs);

	double squishOffset = (xsb + ysb + zsb) * SQUISH_3D;
	double dx0 = x - (xsb + squishOffset);
	double dy0 = y - (ysb + squishOffset);
	double dz0 = z - (zsb + squishOffset);

	double value = 0;

	for (int i = 0; i < 8; i++) {
		int vertex = i & 7;
		double dx = dx0 + (vertex & 4);
		double dy = dy0 + ((vertex >> 1) & 4);
		double dz = dz0 + ((vertex >> 2) & 4);

		double attn = 0.6 - dx * dx - dy * dy - dz * dz;
		if (attn > 0) {
			int pxi = xsb + (vertex & 4);
			int pyi = ysb + ((vertex >> 1) & 4);
			int pzi = zsb + ((vertex >> 2) & 4);

			
			int gi = _permutations[(pxi & PMASK) + _permutations[(pyi & PMASK) + _permutations[pzi & PMASK]]] % 12;

			attn *= attn;
			value += attn * attn * (GRAD_3D[gi][0] * dx + GRAD_3D[gi][1] * dy + GRAD_3D[gi][2] * dz);
		}
	}

	return value * 32;
}
// Правильные значения градиентов для 2D шума
const real_t ex::algorithm::noise::OpenSimplex::GRAD_2D[12][2] = {
	{ 0.130526192220052, 0.99144486137381 },
	{ 0.38268343236509, 0.923879532511287 },
	{ 0.608761429008721, 0.793353340291235 },
	{ 0.793353340291235, 0.608761429008721 },
	{ 0.923879532511287, 0.38268343236509 },
	{ 0.99144486137381, 0.130526192220052 },
	{ 0.99144486137381, -0.130526192220052 },
	{ 0.923879532511287, -0.38268343236509 },
	{ 0.793353340291235, -0.608761429008721 },
	{ 0.608761429008721, -0.793353340291235 },
	{ 0.38268343236509, -0.923879532511287 },
	{ 0.130526192220052, -0.99144486137381 }
};


const double ex::algorithm::noise::OpenSimplex::GRAD_3D[12][3] = {
	{ 1, 1, 0 }, { -1, 1, 0 }, { 1, -1, 0 }, { -1, -1, 0 },
	{ 1, 0, 1 }, { -1, 0, 1 }, { 1, 0, -1 }, { -1, 0, -1 },
	{ 0, 1, 1 }, { 0, -1, 1 }, { 0, 1, -1 }, { 0, -1, -1 }
};
