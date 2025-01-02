#ifndef EX_BASIC_NOISE_H
#define EX_BASIC_NOISE_H
#include "core/math/random_number_generator.h"

#include "core/object/ref_counted.h"
namespace ex::algorithm::noise
{
	class BasicNoise : public RefCounted {
		GDCLASS(BasicNoise, RefCounted);

	protected:
		static void _bind_methods();
		virtual void _init_noise() = 0;
		Ref<RandomNumberGenerator> _rng;
	public:
		BasicNoise();
		BasicNoise(uint64_t seed);

		void set_seed(uint64_t seed);
		uint64_t get_seed();
		virtual real_t get_noise2d_at(real_t x, real_t y) = 0;
		virtual real_t get_noise3d_at(real_t x, real_t y, real_t z) = 0;
		real_t get_noise2d_at_v(Vector2 point);
		real_t get_noise3d_at_v(Vector3 point);
	};
}

#endif // EX_REGISTER_TYPES_H
