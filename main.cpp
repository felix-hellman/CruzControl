#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "web.h"

int main()
{

	std::string result = "", lastTweet = "";
	std::string target = "https://twitter.com/tedcruz";
	while(1)
	{
		checkStatus(result,target);
		if(lastTweet == "") //First time init
			lastTweet = result;
		if(lastTweet != result)
			system("eject");
		sleep(60);
	}

	return 0;
}
