#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "web.h"
#include "utility.h"


int main()
{
	std::cout << decrypt(locker::apikey,locker::key) << std::endl;
	exit(0);
	//We are doing some testing
	//daemonize();
	std::string result = "", lastTweet = "";
	std::string search = "hashtag_click";
	while(1)
	{
		int count = 0;
		checkStatus(result,getHandle());
		auto found = result.find(search,0);
		while(found != std::string::npos)
		{
			found = result.find(search,found+1);
			count++;
		}

		if(lastTweet == "") //First time init
			lastTweet = result;
		if(lastTweet != result)
		{
			execute(commandMap(count));
		}
		sleep(60);
		lastTweet = result;
	}

	return 0;
}
