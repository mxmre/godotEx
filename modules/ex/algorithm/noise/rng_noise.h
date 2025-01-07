#ifndef EX_RNG_NOISE_H
#define EX_RNG_NOISE_H
#include "core/math/random_number_generator.h"

#include "basic_noise.h"
namespace ex::algorithm::noise
{
	class RNGBasedNoise : public BasicNoise {
	GDCLASS(RNGBasedNoise, BasicNoise);

	protected:
		static void _bind_methods();
		
		Ref<RandomNumberGenerator> _rng;
	public:
		RNGBasedNoise();
		RNGBasedNoise(uint64_t seed);
		virtual void reset_noise() = 0;

		void set_seed(uint64_t seed);
		uint64_t get_seed();
	};
}

#endif // EX_REGISTER_TYPES_H
