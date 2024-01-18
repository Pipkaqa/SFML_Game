#include "Object.h"

namespace Base
{
	Object::Object()
	{

	}

	Object::~Object()
	{

	}

	std::string Object::get_type_name()
	{
		return "Object";
	}

	std::string Object::get_object_type_name() const
	{
		return "Object";
	}
}
