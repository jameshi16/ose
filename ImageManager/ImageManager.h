#ifndef ImageManagerHEADER
#define ImageManagerHEADER

#include <mpeg/mpegfile.h>
#include <tbytevectorstream.h>
#include <wx/image.h>

class ImageFile : public TagLib::File
{
public:
	ImageFile(const char *file) : TagLib::File(file) //initializes the class using a class intializer
	{
		//do nothing
	}

	ImageFile(TagLib::IOStream* stream) : TagLib::File(stream) //Initialize image from stream
	{
		//do nothing
	}

	TagLib::ByteVector data()
	{
		return readBlock(length()); //reads and returns the data
	}

	bool save()
	{
		return false;
	}

	TagLib::Tag *tag() const
	{
		return 0;
	}

	TagLib::AudioProperties *audioProperties() const
	{
		return 0;
	}
};

namespace ImageManipulation
{
	wxImage makePerfectSize(std::string); //resizes the image to the perfect size
	TagLib::ByteVectorStream& asIOStream(wxImage, int); //takes the wxImage and returns it as a stream
};

#endif //ImageManagerHEADER
