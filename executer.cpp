#include "executer.h"

Executer::Executer(){}
Executer::~Executer(){}

void Executer::execute(const std::string &command)
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
