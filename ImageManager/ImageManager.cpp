#include "ImageManager.h"
#include <wx/mstream.h>
#include <tbytevector.h>

wxImage ImageManipulation::makePerfectSize(std::string imageLocation)
{
	/*Handlers*/
	if (wxImage::FindHandler("PNG file") == NULL || wxImage::FindHandler("JPEG file") == NULL) //checks to ensure that handlers have not already been declared
	{
		wxImage::AddHandler(new wxPNGHandler()); //handler added
		wxImage::AddHandler(new wxJPEGHandler()); //handler added
	}

	/*Objects*/
	wxImage theImage(imageLocation); //opens the image

	/*Check for existing size*/
	if (theImage.GetSize().GetWidth() >= 600 || theImage.GetSize().GetHeight() >= 600) //if it is more than 600
	{
		wxPoint thePoint; //the top left of the cropped image
		thePoint.x = (theImage.GetSize().GetWidth() / 2) - 300; //the center - 600
		thePoint.y = (theImage.GetSize().GetHeight() /2) - 300; //the center - 600
		//The point is now fully initialized.

		theImage = theImage.GetSubImage(wxRect(thePoint, wxSize(600, 600))); //crops the image.
		return theImage;
	}
	if (theImage.GetSize().GetWidth() >= 300 || theImage.GetSize().GetHeight() >= 300) //if it is more than 300, less than 600
	{
		wxPoint thePoint; //the top left of the cropped image
		thePoint.x = (theImage.GetSize().GetWidth() / 2) - 150; //the center - 600
		thePoint.y = (theImage.GetSize().GetHeight() /2) - 150; //the center - 600
		//The point is now fully initialized.

		theImage = theImage.GetSubImage(wxRect(thePoint, wxSize(300, 300))); //crops the image.
		return theImage;
	}
	//Everything else will be ignored because...
	//why not?
	return theImage; //returns the image.
}

TagLib::ByteVectorStream* ImageManipulation::asIOStream(wxImage theImage, int imageType)
{
	/*Output Stream*/
	wxMemoryOutputStream theOutStream; //this is where the file is going to be saved

	/*Process*/
	if (imageType == 1)
		theImage.SaveFile(theOutStream, "image/png"); //saves the file into the output stream
	if (imageType == 2)
		theImage.SaveFile(theOutStream, "image/jpeg"); //saves the file into the output stream

	/*Reads the stream into a character array*/
	char *buffer = new char[theOutStream.GetSize() + 1]; //new character array
	theOutStream.CopyTo(buffer, theOutStream.GetSize()); //writes to the buffer

	buffer[theOutStream.GetSize()] = '\0'; //null end it.

	/*Write Buffer into ByteVectorStream through ByteVector*/
	TagLib::ByteVectorStream *bvs = new TagLib::ByteVectorStream(TagLib::ByteVector(buffer, theOutStream.GetSize())); //returns the ByteVectorStream
	delete[] buffer;
	return bvs; //returns the ByteVectorStream
}
