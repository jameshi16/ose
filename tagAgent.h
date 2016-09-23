#ifndef TAG_HEADER
#define TAG_HEADER

#include "osuBeatmap.h"

//le tagging library
#include <tag.h>
#include <mpeg/id3v2/id3v2tag.h>
#include <mpeg/mpegfile.h>
#include <mpeg/id3v2/frames/attachedpictureframe.h>

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
		swap(*this, t);
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

	void autoTag(osuBeatmap&);

protected:
private:
};

#endif