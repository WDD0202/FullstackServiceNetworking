#include "json.hpp"
#include <fstream>
#include <string>
#include <iostream>

using json = nlohmann::ordered_json;

int main()
{
    std::ifstream f("lec-06-prg-03-json-example.json");
    json superHeroes = json::parse(f);

    std::cout << superHeroes["homeTown"] << std::endl;
    std::cout << superHeroes["active"] << std::endl;
    std::cout << superHeroes["members"][1]["powers"][2] << std::endl;
}