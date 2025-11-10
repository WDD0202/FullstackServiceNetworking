#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "httplib.h"
using namespace httplib;

httplib::Server svr;


void print_http_request_detail(const Request& req)
{
	std::cout << "::Client address : " << req.remote_addr << std::endl;
	std::cout << "::Client port      : " << req.remote_port << std::endl;
	std::cout << "::Request command  : " << req.method << std::endl;
	std::cout << "::Request line     : " << req.method + " " + req.path + " HTTP/" + req.version << std::endl;
	std::cout << "::Request path     : " << req.path << std::endl;
	std::cout << "::Request version  : " << "HTTP/" << req.version << std::endl;
}

int simple_calc(int para1 = 0, int para2 = 0)
{
	return para1 * para2;
}


std::vector<int> parameter_retrieval(std::string msg)
{
	std::vector<int> result;
	std::stringstream ss(msg);
	std::string pair;

	while (getline(ss, pair, '&'))
	{
		auto pos = pair.find('=');

		if (pos != std::string::npos)
		{
			std::string value = pair.substr(pos+1);
			result.push_back((std::stoi(value)));
		}
	}
	return result;
}

int main()
{
	std::string server_name = "localhost";
	int server_port = 8080;

	Server svr;

	svr.Get("/temp", [](const Request& req, Response& res) {
		res.set_content("Hello World!", "text/plain");
		});

	std::cout << "## HTTP server started at http://" << server_name << server_port << std::endl;
	svr.listen(server_name, 8080);
}