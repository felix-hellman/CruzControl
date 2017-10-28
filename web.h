#include <string>
#include <curl/curl.h>

size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s);
void checkStatus(std::string &result,const std::string &target);
