#include "tagAgent.h"

void TagAgent::autoTag(osuBeatmap& ob)
{
	TagLib::MPEG::File audioFile(ob.MusicLocation.c_str()); //the audio file
	TagLib::ID3v2::Tag *t = audioFile.ID3v2Tag(true); //initializes a tag object, with the audiofile, turning on IDv2Tag at the same time

	/*Begin self-promoting block*/
	t->setTitle(ob.BeatmapName); //sets the title
	t->setArtist("JamesLab Softwares"); //sets the artist
	t->setAlbum("osu!"); //sets the album
	t->setComment("Extracted by OSE!"); //sets the comment
	t->setGenre("osu!"); //sets the genre

	{
		using namespace osuBeatmapFunctions;
		if (isMusicMp3(ob))
		{
			TagLib::ID3v2::AttachedPictureFrame *frame = new TagLib::ID3v2::AttachedPictureFrame;
			if (isImagePng(ob))
			{
				frame->setMimeType("image/png"); //sets cover art as png file type
				//frame->setPicture(); //to implement

				t->addFrame(frame); //adds frame.
			}
		}
	}

	//Ultimately, save the file.
	audioFile.save();
}