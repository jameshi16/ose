#include "osuBeatmap.h" //requires this to work

#include <algorithm> //requires algorithm to work

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

	if (s_string.rfind(".jpeg") != string::npos && s_string.rfind(".jpeg") == s_string.size() - 5)
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
	for (unsigned int iii = 0; iii < vec_.size() - 1; iii++)
	{
		if (!(vec_[iii] == osuBeatmap{"","",""}))
		{
			for (unsigned int jjj = 0; jjj < vec_.size(); jjj++) //a loop to see if the buffer matches with anything already in the array
			{
					if (iii == jjj) //if the indexing is the same, just continue
						continue;

					if (vec_[iii].MusicLocation == vec_[jjj].MusicLocation)
					{
						vec_[jjj] = osuBeatmap{"","",""}; //sets the vec at [jjj] to be empty
					}
				}
		}
	}

	/*This loop will remove all of the osuBeatmap{"","",""} from the vector*/
	vec_.erase(std::remove(vec_.begin(), vec_.end(), osuBeatmap{"", "", ""}), vec_.end()); //removes all the empty vectors
	//end of function
}
