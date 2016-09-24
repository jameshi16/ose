#include "ImageManager.h"
#include <wx/mstream.h>
#include <tbytevector.h>

wxImage ImageManipulation::makePerfectSize(std::string imageLocation)
{
	/*Handlers*/
	wxImage::AddHandler(new wxPNGHandler()); //handler added

	/*Objects*/
	wxImage theImage(imageLocation); //opens the image

	/*Check for existing size*/
	if (theImage.GetSize().GetWidth() >= 600 || theImage.GetSize().GetHeight() >= 600) //if it is more than 600
	{
		wxPoint thePoint; //the top left of the cropped image
		thePoint.x = (theImage.GetSize().GetWidth() / 2) - 300; //the center - 600
		thePoint.y = (theImage.GetSize().GetHeight() /2) - 300; //the center - 600
		//The point is now fully initialized.

		theImage.Resize(wxSize(600, 600), thePoint); //crops the image.
	}
	if (theImage.GetSize().GetWidth() >= 300 || theImage.GetSize().GetHeight() >= 300) //if it is more than 300, less than 600
	{
		wxPoint thePoint; //the top left of the cropped image
		thePoint.x = (theImage.GetSize().GetWidth() / 2) - 150; //the center - 600
		thePoint.y = (theImage.GetSize().GetHeight() /2) - 150; //the center - 600
		//The point is now fully initialized.

		theImage.Resize(wxSize(300, 300), thePoint); //crops the image.
	}
	//Everything else will be ignored because...
	//why not?
	return theImage; //returns the image.
}

TagLib::ByteVectorStream& ImageManipulation::asIOStream(wxImage theImage)
{
	/*Output Stream*/
	wxMemoryOutputStream theOutStream; //this is where the file is going to be saved

	/*Process*/
	theImage.SaveFile(theOutStream, "image/png"); //saves the file into the output stream

	/*Reads the stream into a character array*/
	char *buffer = new char[theOutStream.GetSize() + 1]; //new character array
	theOutStream.Write(buffer, theOutStream.GetSize()); //writes to the buffer

	buffer[theOutStream.GetSize()] = '\0'; //null end it.

	/*Write Buffer into ByteVectorStream through ByteVector*/
	return *(new TagLib::ByteVectorStream(TagLib::ByteVector(buffer, theOutStream.GetSize()))); //returns the ByteVectorStream

}