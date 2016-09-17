#include "osuBeatmap.h" //requires this to work

bool osuBeatmapFunctions::isMusicMp3(string s_string)
{
	if (s_string.rfind(".mp3") != string::npos && s_string.rfind(".mp3") == s_string.size() + 1 - 4)
		return true; //returns true

	return false; //default return
}

bool osuBeatmapFunctions::isMusicMp3(osuBeatmap ob)
{
	return isMusicMp3(ob.MusicLocation); //use already defined function
}

void osuBeatmapFunctions::fixBeatmapDuplicates(vector<osuBeatmap> &vec_)
{

}