#include "tagAgent.h"

void TagAgent::autoTag(osuBeatmap& ob)
{

	//Returns if neither background photo or music location is found
	if (!boost::filesystem::exists(boost::filesystem::path(ob.BackgroundPhoto)) || !boost::filesystem::exists(boost::filesystem::path(ob.MusicLocation)))
		return;
		
	if (!osuBeatmapFunctions::isMusicMp3(ob))
		return; //returns straight away if the music file is not mp3

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
		TagLib::ID3v2::AttachedPictureFrame *frame = new TagLib::ID3v2::AttachedPictureFrame;
		if (isImage(ob) == PNG)
		{
			frame->setMimeType("image/png"); //sets cover art as png file type
			TagLib::ByteVectorStream *bvs = ImageManipulation::asIOStream(ImageManipulation::makePerfectSize(ob.BackgroundPhoto), PNG);
			frame->setPicture(ImageFile(bvs).data()); //set image
			t->addFrame(frame); //adds frame.
			delete bvs; //frees bvs
		}
		if (isImage(ob) == JPEG)
		{
			frame->setMimeType("image/jpeg"); //sets the cover art as jpeg file type
			TagLib::ByteVectorStream *bvs = ImageManipulation::asIOStream(ImageManipulation::makePerfectSize(ob.BackgroundPhoto), JPEG);
			frame->setPicture(ImageFile(bvs).data()); //set image
			t->addFrame(frame); //adds frame.
			delete bvs; //frees bvs
		}
	}

	//Ultimately, save the file (Windows doesn't like ID3v2.4 AT ALL. Instead, I'll use ID3v2.3, so that windows can see the cover art.)
	audioFile.save(TagLib::MPEG::File::TagTypes::AllTags, false, 3);

	//Memory management
	delete t;
}
