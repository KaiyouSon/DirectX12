#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include <string>
#include <vector>

class Tag : public IComponent
{
private:
	std::string tag;

public:
	Tag();
	void SetTag(std::string tag);
	std::string GetTag();
};

class TagList
{
private:
	std::vector<std::string> list;
public:
	TagList();
	void AddTag(std::string tag);
	void DestroyTag(std::string tag);
};

extern TagList* tagList;