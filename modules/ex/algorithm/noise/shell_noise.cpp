#include "shell_noise.h"

void ex::algorithm::noise::ShellNoise::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_basic_noise", "basic_noise"), &ShellNoise::set_basic_noise);
	ClassDB::bind_method(D_METHOD("get_basic_noise"), &ShellNoise::get_basic_noise);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "basic_noise"),
			"set_basic_noise", "get_basic_noise");
}

bool ex::algorithm::noise::ShellNoise::_check_basic_noise() {
	if(this->_basic_noise.is_null())
	{
		ERR_PRINT("basic_noise is null");
		return false;
	}
	return true;
}

ex::algorithm::noise::ShellNoise::ShellNoise() :
		_basic_noise{ nullptr } {
}

void ex::algorithm::noise::ShellNoise::set_basic_noise(Ref<BasicNoise> noise) {
	this->_basic_noise = noise;
}

Ref<ex::algorithm::noise::BasicNoise> ex::algorithm::noise::ShellNoise::get_basic_noise() {
	return this->_basic_noise;
}
