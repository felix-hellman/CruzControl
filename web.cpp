#include "web.h"

//
// https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string
//

size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}
void checkStatus(std::string &result, const std::string &target)
{

	CURL *curl;
  	CURLcode res;

	std::string start = "<div class=\"js-tweet-text-container\">";
	std::string stop  = "</div>";

	std::string buffer;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, target.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		res = curl_easy_perform(curl);

		unsigned int first = buffer.find(start);
		unsigned int last = buffer.find(stop,first);
		//first = buffer.find(start,last);
		//last = buffer.find(stop,first); //Because we want to skip pinned tweet
		result = buffer.substr(first,last-first);

		curl_easy_cleanup(curl);
		curl_global_cleanup();
	}

	curl_global_cleanup();
}
