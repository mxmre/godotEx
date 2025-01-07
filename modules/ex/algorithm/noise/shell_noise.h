#ifndef EX_FRACTAL_NOISE_H
#define EX_FRACTAL_NOISE_H

#include "basic_noise.h"
#include "rng_noise.h"
namespace ex::algorithm::noise
{
	class ShellNoise : public BasicNoise
	{
	GDCLASS(ShellNoise, BasicNoise);

	protected:
		static void _bind_methods();
		Ref<BasicNoise> _basic_noise;
		bool _check_basic_noise();
	public:
		ShellNoise();

		virtual real_t get_noise1d(real_t x) = 0;
		virtual real_t get_noise2d(real_t x, real_t y) = 0;
		virtual real_t get_noise3d(real_t x, real_t y, real_t z) = 0;

		void set_basic_noise(Ref<BasicNoise> noise);
		Ref<BasicNoise> get_basic_noise();
	};
}

#endif
