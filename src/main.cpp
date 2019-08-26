#include "wgethelper.hpp"
#include <iostream>
#include <string>



int main(int argc, char** argv) {
    const std::string url = "https://image.flaticon.com/icons/png/512/1411/1411596.png";
    
    WgetHelper downloader(url);
    
    std::string content;
    if(downloader.download(content)){
        std::string filepath = downloader.filename();
        WgetHelper::save(content, filepath);         
    }
}
