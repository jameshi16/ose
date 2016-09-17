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
};

/* This structure contains the functions that is used to manipulate the osuBeatmaps*/
namespace osuBeatmapFunctions
{
	bool isMusicMp3(string); //surface check if music is mp3
	bool isMusicMp3(osuBeatmap); //can also use osuBeatmap to check
	void fixBeatmapDuplicates(vector<osuBeatmap>&); //fix beatmap duplicates
};

#endif