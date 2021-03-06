#ifndef TAGAGENT_HEADER
#define TAGAGENT_HEADER

#include "osuBeatmap.h"
#include "ImageManager/ImageManager.h"

//le tagging library
#include <tag.h>
#include <mpeg/id3v2/id3v2tag.h>
#include <mpeg/mpegfile.h>
#include <mpeg/id3v2/frames/attachedpictureframe.h>

//boost filesystem
#include <boost/filesystem.hpp>

class TagAgent
{
public:
	TagAgent()
	{

	}
	~TagAgent()
	{

	}

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
		return *this;
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
