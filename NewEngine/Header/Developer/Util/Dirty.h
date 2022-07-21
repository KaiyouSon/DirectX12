#pragma once

template<class T>
class Dirty
{
private:
	T dirtyValue;

public:
	Dirty(T dirtyValue)
	{
		this->dirtyValue = dirtyValue;
	}

	bool GetisDirty(T dirtyValue)
	{
		if (this->dirtyValue != dirtyValue)
		{
			this->dirtyValue = dirtyValue;
			return true;
		}
		return false;
	}
};
