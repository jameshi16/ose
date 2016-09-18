#include "osuBeatmap.h" //requires this to work

/* Finds out if the file given is an Mp3 */
bool osuBeatmapFunctions::isMusicMp3(string s_string)
{
	if (s_string.rfind(".mp3") != string::npos && s_string.rfind(".mp3") == s_string.size() + 1 - 4)
		return true; //returns true

	return false; //default return
}

/* Finds out if the osuBeatmap structure given is an Mp3 */
bool osuBeatmapFunctions::isMusicMp3(osuBeatmap ob)
{
	return isMusicMp3(ob.MusicLocation); //use already defined function
}

/* Find duplicates of beatmaps */
void osuBeatmapFunctions::fixBeatmapDuplicates(vector<osuBeatmap> &vec_)
{
	/*Memory buffer of the members to compare*/
	osuBeatmap ob_Buffer;
	for (unsigned int iii = 0; iii < vec_.size(); iii++)
	{
		if (ob_Buffer.BeatmapName == vec_[iii].BeatmapName 
			|| ob_Buffer.BackgroundPhoto == vec_[iii].BackgroundPhoto
			|| ob_Buffer.MusicLocation == vec_[iii].MusicLocation)
		{
			vec_[iii] = osuBeatmap{"","",""}; //empty it out first ()
		}
		ob_Buffer = vec_[iii]; //Simple and easy
	}

	/*This loop will remove all of the osuBeatmap{"","",""} from the vector*/
	for (unsigned int iii = 0; iii < vec_.size(); iii++) //vec_ size changes in the loop
	{
		if (vec_[iii] == osuBeatmap{"","",""})
			vec_.erase(vec_.begin() + iii); //erases the element
	}
	//end of function
}