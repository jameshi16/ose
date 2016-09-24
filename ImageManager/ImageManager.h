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

	}

	TagLib::ByteVector data()
	{
		return readBlock(length()); //reads and returns the data
	}
};

namespace ImageManipulation
{
	wxImage makePerfectSize(std::string); //resizes the image to the perfect size
	TagLib::ByteVectorStream& asIOStream(wxImage); //takes the wxImage and returns it as a stream
};

#endif //ImageManagerHEADER