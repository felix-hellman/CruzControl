#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "web.h"
#include "executer.h"

int main()
{
	for(int i = 0; i < 1024; i++)
		close(i);
	/*open("/dev/null",O_RWDR);
	dup(0);
	dup(0);*/

	std::string result = "", lastTweet = "";
	std::string target = "https://twitter.com/tedcruz";
	Executer ex;
	while(1)
	{
		checkStatus(result,target);
		if(lastTweet == "") //First time init
			lastTweet = result;
		if(lastTweet != result)
		{
			std::cout << result << std::endl;
			ex.execute("screen");
		}
		sleep(60);
		lastTweet = result;
	}

	return 0;
}
