#pragma once

#include <iostream>

namespace Base
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		static std::string get_type_name();
		virtual std::string get_object_type_name() const;
	};
}
