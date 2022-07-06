#include "NewEngine/Header/Developer/Component/Tag.h"

Tag::Tag()
{
	componentName = "Tag";
}

void Tag::SetTag(std::string tag)
{
	this->tag = tag;
}

std::string Tag::GetTag()
{
	return tag;
}

TagList::TagList()
{
	list.push_back("Default");
}

void TagList::AddTag(std::string tag)
{
	list.push_back(tag);
}

void TagList::DestroyTag(std::string tag)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].c_str() == tag)
		{
			list.erase(list.begin() + i);
		}
	}
}

TagList* tagList = new TagList;