#include "json.hpp"
#include <iostream>

using json = nlohmann::ordered_json;

int main()
{
    json superHeroes_source = {
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

    std::string superHeroes_mid = superHeroes_source.dump(1, '\t');
    json superHeros = json::parse(superHeroes_mid);


    // json 객체를 문자열로 dump
    // 문자열을 다시 json 객체로 load

    std::cout << superHeros["homeTown"] << std::endl;

    //출력 시 " " 표시가 있으므로 json 객체임을 알 수 있음 
}