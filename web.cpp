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
		first = buffer.find(start,last);
		last = buffer.find(stop,first); //Because we want to skip pinned tweet
		result = buffer.substr(first,last-first);

		curl_easy_cleanup(curl);
		curl_global_cleanup();
	}

	curl_global_cleanup();
}
void postImageToImgur()
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *chunk = NULL;
  curl_mime *mime1 = NULL;
  curl_mimepart *part1 = NULL;
  curl_mimepart *part2 = NULL;


  std::string buffer;

  std::string clientid = decrypt(locker::clientkey,locker::key);
  std::string accesstoken = decrypt(locker::accesstoken,locker::key);
  std::string url  = "https://api.imgur.com/3/image";
  std::string auth = "authorization: Bearer " + accesstoken;
  std::string data =  base64_encode("/tmp/out.jpg");

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  /*Start*/
  mime1 = curl_mime_init(curl);
  part1 = curl_mime_addpart(mime1);
  part2 = curl_mime_addpart(mime1);
  curl_mime_data(part1,data.c_str(),CURL_ZERO_TERMINATED);
  curl_mime_name(part1,"image");
  curl_mime_data(part2,"vMLlw",CURL_ZERO_TERMINATED);
  curl_mime_name(part2,"album");
  curl_easy_setopt(curl,CURLOPT_MIMEPOST,mime1);
  /*Set up header*/
  chunk = curl_slist_append(chunk,auth.c_str());
  chunk = curl_slist_append(chunk,"content-type: multipart/form-data;");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POST,1);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
  curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);

  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

  /*Do request*/
  res = curl_easy_perform(curl);
  //std::cout << buffer << std::endl;
  /*End*/
  curl_easy_cleanup(curl);
  curl_slist_free_all(chunk);
  curl_global_cleanup();



}
