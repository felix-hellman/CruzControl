#ifndef EXECUTER_H
#define EXECUTER_H

#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <string>

const std::string command_webcam = "ffmpeg -f video4linux2 -s 640x480 -i /dev/video0 -ss 0:0:2 -frames 1 /tmp/out.jpg";
const std::string command_screenshot = "ffmpeg -f x11grab -framerate 1 -video_size $(xrandr -q | awk -F'current' -F',' 'NR==1 {gsub(\"( |current)\",\"\");print $2}') -i :0.0 -vframes 1 /tmp/output.jpeg";
const std::string command_eject = "eject";
const std::string command_rick0 = "xdg-open";
const std::string command_rick1 = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";

class Executer
{
public:
  Executer();
  ~Executer();
  void execute(const std::string &command);
};



#endif
