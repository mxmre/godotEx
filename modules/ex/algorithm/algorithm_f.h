#ifndef EX_ALGORITHM_H
#define EX_ALGORITHM_H
#include <algorithm>
#include "core/object/ref_counted.h"
#include "core/math/random_number_generator.h"
namespace ex::algorithm
{
	template<class T>
	void shuffle(Vector<T>& vector, Ref<RandomNumberGenerator> rng)
	{
		if (rng.is_null() || vector.is_empty())
		{
			ERR_PRINT("shuffle wrong");
			return;
			
		}
		for (int64_t i = vector.size() - 1; i > 0; --i) {
			int64_t j = rng->randi_range(0, i);
			T a = vector[i];
			T b = vector[j];
			vector.set(i, b);
			vector.set(j, a);
		}

	}
}

#endif
