#ifndef osuBeatmapH_FILE
#define osuBeatmapH_FILE

#include <iostream>
#include <string>
#include <vector>

using namespace std; //lazy people gotta remain lazy!

/* This structure contains the osu! Beatmap*/
struct osuBeatmap
{
	string BeatmapName; //BeatmapName, will be used in the song title
	string BackgroundPhoto; //background photo, will be processed and cropped
	string MusicLocation; //music, will be tagged

	bool operator==(const osuBeatmap& other)
	{
		return (this->BeatmapName == other.BeatmapName
			&& this->BackgroundPhoto == other.BackgroundPhoto
			&& this->MusicLocation == other.MusicLocation);
	}

	osuBeatmap& operator=(osuBeatmap other) //this constructor requires a copy of an object
	{
		swap(*this, other); //swaps this with the object given
		return *this;
	}

	friend void swap(osuBeatmap& LHS, osuBeatmap& RHS) //this won't throw an exception
	{
		//Enable ADL (it's good practice, apparently) //Also, ADL's needed to find this function
		using std::swap;

		//swap members of the two classes
		swap(LHS.BeatmapName, RHS.BeatmapName);
		swap(LHS.BackgroundPhoto, RHS.BackgroundPhoto);
		swap(LHS.MusicLocation, RHS.MusicLocation);
	}
};

/* This structure contains the functions that is used to manipulate the osuBeatmaps*/
namespace osuBeatmapFunctions
{
	bool isMusicMp3(string); //surface check if music is mp3
	bool isMusicMp3(osuBeatmap); //can also use osuBeatmap to check
	void fixBeatmapDuplicates(vector<osuBeatmap>&); //fix beatmap duplicates
};

#endif