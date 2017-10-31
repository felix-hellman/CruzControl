#ifndef WEB_H
#define WEB_H

#include <curl/curl.h>
#include <cstring>
#include <iostream>
#include <string>
#include "utility.h"

size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size,
                                        size_t nmemb, std::string *s);
void checkStatus(std::string &result, const std::string &target);
void postImageToImgur();

#endif
