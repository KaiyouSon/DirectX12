#pragma once
#include <string>

class IComponent
{
public:
	std::string componentName;
	virtual ~IComponent() {}
	std::string GetComponentName();
};