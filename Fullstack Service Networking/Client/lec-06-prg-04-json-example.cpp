#include "json.hpp"
#include <fstream>
#include <string>
#include <iostream>

using json = nlohmann::ordered_json;

int main()
{
    json superHeroes = {
    {"squadName", "Super hero squad"},
    {"homeTown", "Metro City"},
    {"formed" , 2016},
    {"secretBase" , "Super tower"},
    {"active" , true},
    {"members",
        {
            {
                {"name", "Molecule Man"},
                {"age" , 29},
                {"secretIdentity" , "Dan Jukes"},
                {"powers" , {
                    "Radiation resistance",
                    "Turning tiny",
                    "Radiation blast"}
                }
            },
            {
                {"name", "Madame Uppercut"},
                {"age" , 39},
                {"secretIdentity" , "Jane Wilson" },
                {"powers" , {
                    "Million tonne punch",
                    "Damage resistance",
                    "Superhuman reflexes"}
                }
            },
            {
                {"name", "Eternal Flame"},
                {"age" , 1000000},
                {"secretIdentity" , "Unknown"},
                {"powers" , {
                    "Immortality",
                    "Heat Immunity",
                    "Inferno",
                    "Teleportation",
                    "Interdimensional travel"}
                }
            }
        }
    }
};


    std::cout << superHeroes["homeTown"].dump() << std::endl;
    std::cout << superHeroes["active"].dump() << std::endl;
    std::cout << superHeroes["members"][1]["powers"][2].dump() << std::endl;

    std::ofstream json_out_file("lec-06-prg-04-json-example.json");
    json_out_file << superHeroes.dump(1,'\t');

    json_out_file.close();
}