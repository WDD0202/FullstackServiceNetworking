#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "httplib.h"
using namespace httplib;

httplib::Server svr;


void print_http_request_detail(const Request& req)
{
	std::cout << "::Client address   : " << req.remote_addr << std::endl;
	std::cout << "::Client port      : " << req.remote_port << std::endl;
	std::cout << "::Request command  : " << req.method << std::endl;
	std::cout << "::Request line     : " << req.method <<" "<< req.target <<" "<< req.version << std::endl;
	std::cout << "::Request path     : " << req.target << std::endl;
	std::cout << "::Request version  : " << req.version << std::endl;
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
			result.push_back(std::stoi(value));
		}
	}
	return result;
}

int main()
{
	std::string server_name = "localhost"; 
	int server_port = 8080;

	Server svr;

	svr.Get("/.*",[](const Request& req, Response& res) {
		
		std::cout << "## do_Get() activated." << std::endl;

		print_http_request_detail(req);

		res.set_header("Content-type", "text/html");

		if (req.target.find('?') != std::string::npos)
		{
			std::string target = req.target;
			size_t pos = target.find('?');
			std::string routine = (pos != std::string::npos) ? target.substr(pos + 1) : "";
			std::vector<int> parameter = parameter_retrieval(routine);
			int result = simple_calc(int(parameter[0]), int(parameter[1]));

			std::string html_start = "<html>";
			std::string get_response = "GET request for calculation => " + std::to_string(parameter[0]) + " x " + std::to_string(parameter[1]) + " = " +  std::to_string(result);
			std::string html_end = "</html>";
			std::string body = html_start + get_response + html_end;
			res.set_content(body, "text/html");

			std::cout << "## GET request for calculation => " << parameter[0] << " x " << parameter[1] << " = " << result << ".\n";
		}
		else
		{
			std::string html_start = "<html>";
			std::string get_directory = "<p>HTTP Request GET for Path: " + req.target + "</p>";
			std::string html_end = "</html>";
			std::string body = html_start + get_directory + html_end;
			res.set_content(body, "text/html");

			std::cout << "## GET request for directory =>" << req.target << ".\n";
		}
	});

	svr.Post("/.*", [](const Request& req, Response& res) {
		std::cout << "## do_Get() activated." << std::endl;

		print_http_request_detail(req);
		res.set_header("Content-type", "text/html");
		
		std::string body = req.body;

		auto parameter = parameter_retrieval(body);

		int v1 = parameter[0];
		int v2 = parameter[1];

		int result = simple_calc(v1, v2);

		std::string post_response = "POST request for calculation => " + std::to_string(v1) + " x " + std::to_string(v2) + " = " + std::to_string(result) + ".";

		res.set_content(post_response, "text/html");

		std::cout << "## POST request data = > " << body << std::endl;
		std::cout << "## POST request for calculation => " << std::to_string(v1) + " x " + std::to_string(v2)+" = " + std::to_string(result) + "." << std::endl;
	});

	std::cout << "## HTTP server started at http://" << server_name + ":" << server_port << std::endl;
	svr.listen(server_name, 8080);
}