#include <iostream>
#include "httplib.h"

using namespace httplib;

int main()
{

	httplib::Client cli("http://localhost:8080");

	std::cout << "## HTTP client started" << std::endl;

	std::cout << "## GET request for http://localhost:8080/temp/" << std::endl;
	httplib::Result http_request = cli.Get("/temp");
	std::cout << "## GET response [start]" << std::endl;
	std::cout << http_request->body << std::endl;
	std::cout << "## GET response [end]" << std::endl;


}
