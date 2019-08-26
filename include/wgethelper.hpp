#ifndef HTTPDOWNLOADER_HPP
#define HTTPDOWNLOADER_HPP

#include <string>


class WgetHelper {
	public:
	    WgetHelper(const std::string url);
	    std::string filename();
	    ~WgetHelper();
	    bool download(std::string& content);
	    static bool save(const std::string& data, const std::string& filepath);
	private:
	    void* _curl;
	    std::string _url;
};

#endif  /* HTTPDOWNLOADER_HPP */
