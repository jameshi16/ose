#include "osuBeatmap.h" //requires this to work

/* Finds out if the file given is an Mp3 */
bool osuBeatmapFunctions::isMusicMp3(string s_string)
{
	if (s_string.rfind(".mp3") != string::npos && s_string.rfind(".mp3") == s_string.size() - 4)
		return true; //returns true

	return false; //default return
}

/* Finds out if the osuBeatmap structure given is an Mp3 */
bool osuBeatmapFunctions::isMusicMp3(osuBeatmap ob)
{
	return isMusicMp3(ob.MusicLocation); //use already defined function
}

/* Finds out if the file given is an Mp3 */
osuBeatmapFunctions::imageType osuBeatmapFunctions::isImage(string s_string)
{
	if (s_string.rfind(".png") != string::npos && s_string.rfind(".png") == s_string.size() - 4)
		return PNG; //returns png

	if (s_string.rfind(".jpg") != string::npos && s_string.rfind(".jpg") == s_string.size() - 4)
		return JPEG; //returns jpeg

	if (s_string.rfind(".jpeg") != string::npos && s_string.rfind(".jpeg") == s_string.size() - 4)
		return JPEG; //returns jpeg

	return NOIMAGE; //default return
}

/* Finds out if the osuBeatmap structure given is an Mp3 */
osuBeatmapFunctions::imageType osuBeatmapFunctions::isImage(osuBeatmap ob)
{
	return isImage(ob.BackgroundPhoto); //use already defined function
}

/* Find duplicates of beatmaps (Code is broken)*/
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
		while (vec_[iii] == osuBeatmap{"","",""} && vec_.size() != 0)
			vec_.erase(vec_.begin() + iii); //erases the element
	}
	//end of function
}
