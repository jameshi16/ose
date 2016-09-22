#ifndef TAG_HEADER
#define TAG_HEADER

#include "osuBeatmap.h"

class TagAgent
{
public:
	TagAgent();
	~TagAgent();

	//Copy constructor
	TagAgent(TagAgent& t)
	{
		//Copy stuff here
	}

	//Move constructor
	TagAgent(TagAgent&& t)
	{
		swap(*this, RHS);
	}

	//operator=
	TagAgent& operator=(TagAgent RHS)
	{
		swap(*this, RHS); //swaps
	}

	friend void swap(TagAgent& LHS, TagAgent& RHS)
	{
		using std::swap; //ADL.

		//Swap stuff here
	}

	void Tag(osuBeatmap&)

protected:
private:
}

#endif