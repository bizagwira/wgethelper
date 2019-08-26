#include "wgethelper.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

static size_t writer_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

WgetHelper::WgetHelper(const std::string url)
:_url(url) {
    _curl = curl_easy_init();
}

WgetHelper::~WgetHelper() {
}


bool
WgetHelper::download(std::string& content) {
  CURLcode res;
  if(_curl) {
    curl_easy_setopt(_curl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, writer_callback);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &content);
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);

    //! Check if the request has been successfully completed
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return false;
    }
  }
  else{
    std::cout << "Unable to init curl!" << std::endl;  
    return false;
  }
  return true;
}


std::string 
WgetHelper::filename(){
    std::string fname = "filename.dat";
    std::regex rgx("([a-zA-Z0-9\\-\\.]+\\.[a-z]+)$"); 
     
    std::smatch match;

    if (std::regex_search(_url, match, rgx)){
      fname = match[1];
    }
    return fname;
}

bool 
WgetHelper::save(const std::string& data, const std::string& filepath){
    ofstream f;
    const char *filename = filepath.c_str();
    f.open (filename);
    f << data;
    f.close();
    return true;
}
