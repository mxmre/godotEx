#ifndef EX_NOISE_H
#define EX_NOISE_H

#include "core/object/ref_counted.h"
namespace ex::algorithm::noise
{
	class BasicNoise : public RefCounted
	{
	GDCLASS(BasicNoise, RefCounted);

	protected:
		static void _bind_methods();

	public:
		BasicNoise();
		virtual real_t get_noise1d(real_t x) = 0;
		virtual real_t get_noise2d(real_t x, real_t y) = 0;
		virtual real_t get_noise3d(real_t x, real_t y, real_t z) = 0;
		real_t get_noise2dv(Vector2 point);
		real_t get_noise3dv(Vector3 point);
	};
} //namespace ex::algorithm::noise

#endif

