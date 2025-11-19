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

	std::cout << "## GET request for http://localhost:8080/?var1=9&var2=9" << std::endl;
	http_request = cli.Get("/?var1=9&var2=9");
	std::cout << "## GET response [start]" << std::endl;
	std::cout << http_request->body << std::endl;
	std::cout << "## GET response [end]" << std::endl;

	std::cout << "## POST request for http://localhost:8080/ with var1 is 9 and var2 is 9" << std::endl;
	http_request = cli.Post("/");
	std::cout << "## Post response [start]" << std::endl;
	std::cout << http_request->body << std::endl;
	std::cout << "## Post response [end]" << std::endl;

	std::cout << "## HTTP client completed." << std::endl;
}
