#ifndef EX_ALGORITHM_H
#define EX_ALGORITHM_H
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
		for (int64_t i = 0, index_to_shuffle = this->_rng->randi_range(0, vector.size() - 1); i < vector.size(); ++i) {
			if (i != index_to_shuffle) {
				T a = vector[i];
				T b = vector[index_to_shuffle];
				T c = a;
				a = b;
				b = c;
				vector.set(i, a);
				vector.set(index_to_shuffle, b);
			}
		}
	}
}

#endif
