#ifndef EX_FRACTAL_SUM_NOISE_H
#define EX_FRACTAL_SUM_NOISE_H
#include <functional>
#include "shell_noise.h"
namespace ex::algorithm::noise::fractal
{
	class FractalNoise : public ShellNoise
	{
		GDCLASS(FractalNoise, ShellNoise);

	protected:
		static void _bind_methods();
		int32_t _octaves;
		real_t _persistence;
		real_t _lacunarity;
		real_t _frequency;
		real_t _amplitude;

	public:
		FractalNoise();
		virtual real_t get_noise1d(real_t x) = 0;
		virtual real_t get_noise2d(real_t x, real_t y) = 0;
		virtual real_t get_noise3d(real_t x, real_t y, real_t z) = 0;

		void set_octaves(int32_t p_octaves);
		void set_persistence(real_t p_persistence);
		void set_lacunarity(real_t p_lacunarity);
		void set_frequency(real_t p_frequency);
		void set_amplitude(real_t p_amplitude);

		int32_t get_octaves() const;
		real_t get_persistence() const;
		real_t get_lacunarity() const;
		real_t get_frequency() const;
		real_t get_amplitude() const;
	};
	class FractionalBrownianMotion : public FractalNoise
	{
		GDCLASS(FractionalBrownianMotion, FractalNoise);
		template <typename NoiseFunc>
		real_t _calculate_fractal(NoiseFunc noise_func) {
			if (!this->_check_basic_noise()) {
				return 0.0;
			}

			real_t total = 0.0;
			real_t max_value = 0.0;
			real_t current_amplitude = this->_amplitude;
			real_t current_frequency = this->_frequency;

			for (int i = 0; i < this->_octaves; i++) {
				total += noise_func(current_frequency) * current_amplitude;
				max_value += current_amplitude;
				current_amplitude *= this->_persistence;
				current_frequency *= this->_lacunarity;
			}

			return total / max_value;
		}
	protected:
		static void _bind_methods();
		
	public:
		FractionalBrownianMotion();

		virtual real_t get_noise1d(real_t x);
		virtual real_t get_noise2d(real_t x, real_t y);
		virtual real_t get_noise3d(real_t x, real_t y, real_t z);
	};

	class TurbulenceNoise : public FractalNoise
	{
		GDCLASS(TurbulenceNoise, FractalNoise);
		template <typename NoiseFunc>
		real_t _calculate_fractal(NoiseFunc noise_func) {
			if (!this->_check_basic_noise()) {
				return 0.0;
			}

			real_t total = 0.0;
			real_t current_amplitude = this->_amplitude;
			real_t current_frequency = this->_frequency;

			for (int i = 0; i < this->_octaves; i++) {
				total += Math::abs(noise_func(current_frequency)) * current_amplitude;
				current_amplitude *= this->_persistence;
				current_frequency *= this->_lacunarity;
			}

			return total;
		}
	protected:
		static void _bind_methods();
	public:
		TurbulenceNoise();

		virtual real_t get_noise1d(real_t x);
		virtual real_t get_noise2d(real_t x, real_t y);
		virtual real_t get_noise3d(real_t x, real_t y, real_t z);
	};

	class BillowNoise : public FractalNoise {
		GDCLASS(BillowNoise, FractalNoise);
		template <typename NoiseFunc>
		real_t _calculate_fractal(NoiseFunc noise_func) {
			if (!this->_check_basic_noise()) {
				return 0.0;
			}

			real_t total = 0.0;
			real_t max_value = 0.0;
			real_t current_amplitude = this->_amplitude;
			real_t current_frequency = this->_frequency;

			for (int i = 0; i < this->_octaves; i++) {
				total += (2.0 * Math::abs(noise_func(current_frequency)) - 1.0) * current_amplitude;
				max_value += current_amplitude;
				current_amplitude *= this->_persistence;
				current_frequency *= this->_lacunarity;
			}

			return total / max_value;
		}

	protected:
		static void _bind_methods();

	public:
		BillowNoise();

		virtual real_t get_noise1d(real_t x);
		virtual real_t get_noise2d(real_t x, real_t y);
		virtual real_t get_noise3d(real_t x, real_t y, real_t z);
	};

	class HybridMultiFractal : public FractalNoise {
		GDCLASS(HybridMultiFractal, FractalNoise);
		template <typename NoiseFunc>
		real_t _calculate_fractal(NoiseFunc noise_func) {
			if (!this->_check_basic_noise()) {
				return 0.0;
			}

			real_t total = noise_func(1.0);
			real_t current_amplitude = this->_amplitude;
			real_t current_frequency = this->_frequency;
			real_t weight = 1.0;

			for (int i = 0; i < this->_octaves; i++) {
				current_amplitude *= this->_persistence;
				current_frequency *= this->_lacunarity;
				weight = total;
				total += noise_func(current_frequency) * weight * current_amplitude;
			}

			return total;
		}

	protected:
		static void _bind_methods();

	public:
		HybridMultiFractal();

		virtual real_t get_noise1d(real_t x);
		virtual real_t get_noise2d(real_t x, real_t y);
		virtual real_t get_noise3d(real_t x, real_t y, real_t z);
	};
	}

#endif
