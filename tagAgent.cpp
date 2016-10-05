#include "tagAgent.h"

void TagAgent::autoTag(osuBeatmap& ob)
{
	TagLib::MPEG::File audioFile(ob.MusicLocation.c_str()); //the audio file
	TagLib::ID3v2::Tag *t = audioFile.ID3v2Tag(true); //initializes a tag object, with the audiofile, turning on IDv2Tag at the same time

	//Telling TagLib we don't need ID3v1Tag
	audioFile.ID3v1Tag(false);

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
			if (isImage(ob) == PNG)
			{
				frame->setMimeType("image/png"); //sets cover art as png file type
				frame->setPicture(ImageFile(&ImageManipulation::asIOStream(ImageManipulation::makePerfectSize(ob.BackgroundPhoto), PNG)).data()); //set image
				t->addFrame(frame); //adds frame.
			}
			if (isImage(ob) == JPEG)
			{
				frame->setMimeType("image/jpeg"); //sets the cover art as jpeg file type
				frame->setPicture(ImageFile(&ImageManipulation::asIOStream(ImageManipulation::makePerfectSize(ob.BackgroundPhoto), JPEG)).data()); //set image
				t->addFrame(frame); //adds frame.
			}
		}
		else
		{
			return; //returns straight away, nothing we can do here.
		}
	}

	//Ultimately, save the file (Windows doesn't like ID3v2.4 AT ALL. Instead, I'll use ID3v2.3, so that windows can see the cover art.)
	audioFile.save(TagLib::MPEG::File::TagTypes::AllTags, false, 3);
}
