#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <string>

using namespace httplib;
using json = nlohmann::json;


int main()
{
    httplib::Client cli("http://127.0.0.1:5000");

    std::string path_0001 = "/membership_api/0001";
    std::string path_0002 = "/membership_api/0002";

    httplib::Result r = cli.Get(path_0001.c_str());
    json reqJson = json::parse(r->body);
    std::cout << "#1 Code: " << r->status << " >> JSON: " << reqJson << " Json Result: " << reqJson["0001"] << std::endl;

    httplib::Params params1;
    params1.emplace("0001", "apple");
    r = cli.Post(path_0001.c_str(), params1);
    reqJson = json::parse(r->body);
    std::cout << "#2 Code: " << r->status << " >> JSON: " << reqJson << " Json Result: " << reqJson["0001"] << std::endl;

    r = cli.Get(path_0001.c_str());
    reqJson = json::parse(r->body);
    std::cout << "#3 Code: " << r->status << " >> JSON: " << reqJson << " Json Result: " << reqJson["0001"] << std::endl;

    httplib::Params params2;
    params2.emplace("0001", "xpple");
    r = cli.Post(path_0001.c_str(), params2);
    reqJson = json::parse(r->body);
    std::cout << "#4 Code: " << r->status << " >> JSON: " << reqJson << " Json Result: " << reqJson["0001"] << std::endl;


    httplib::Params params3;
    params3.emplace("0002", "xrange");
    r = cli.Put(path_0002.c_str(), params3);
    reqJson = json::parse(r->body);
    std::cout << "#5 Code: " << r->status << " >> JSON: " << reqJson << " Json Result: " << reqJson["0002"] << std::endl;

    httplib::Params params4;
    params4.emplace("0002", "orange");

    r = cli.Post(path_0002.c_str(), params3); 
    r = cli.Put(path_0002.c_str(), params4);  
    reqJson = json::parse(r->body);   
    std::cout << "#6 Code: " << r->status << " >> JSON: " << reqJson << " Json Result: " << reqJson["0002"] << std::endl;

    r = cli.Delete(path_0001.c_str());
    reqJson = json::parse(r->body);
    std::cout << "#7 Code: " << r->status << " >> JSON: " << reqJson << " Json Result: " << reqJson["0001"] << std::endl;

    r = cli.Delete(path_0001.c_str());
    reqJson = json::parse(r->body);
    std::cout << "#8 Code: " << r->status << " >> JSON: " << reqJson << " Json Result: " << reqJson["0001"] << std::endl;

    return 0;
}
