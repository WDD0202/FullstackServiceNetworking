#include "crow_all.h"
#include "json.hpp"

using json = nlohmann::json;


std::unordered_map<std::string, std::string> parse_params(const std::string& body)
{
    std::unordered_map<std::string, std::string> result;
    std::string key, value;
    std::size_t start = 0;

    while (start < body.size()) {
        std::size_t eq_pos = body.find('=', start);
        if (eq_pos == std::string::npos) break;
        key = body.substr(start, eq_pos - start);

        std::size_t amp_pos = body.find('&', eq_pos + 1);
        if (amp_pos == std::string::npos) {
            value = body.substr(eq_pos + 1);
            start = body.size();
        }
        else {
            value = body.substr(eq_pos + 1, amp_pos - (eq_pos + 1));
            start = amp_pos + 1;
        }
        result[key] = value;
    }

    return result;
}


class MembershipHandler
{
private:
    std::map<std::string, std::string> database;

public:
    MembershipHandler() = default;

    json create(const std::string& id, const std::string& value)
    {

        if (database.find(id) != database.end())
        {
            return json{ { id, "None" } };
        }
        else
        {
            database[id] = value;
            return json{ { id, database[id] } };
        }

    }

    json read(const std::string& id)
    {

        if (database.find(id) != database.end())
        {
            return json{ { id, database[id] } };
        }
        else
        {
            return json{ { id, "None" } };
        }

    }

    json update(const std::string& id, const std::string& value)
    {
        json result;
        if (database.find(id) != database.end())
        {
            database[id] = value;
            return json{ { id, database[id] } };
        }
        else
        {
            return json{ { id, "None" } };
        }
        
    }

    json Delete(const std::string& id)
    {

        if (database.find(id) != database.end())
        {
            database.erase(id);
            return json{ { id, "Removed" } };
        }
        else
        {
            return json{ { id, "None" } };
        }
    }
};


int main()
{
    crow::SimpleApp app;
    MembershipHandler myManager;

    CROW_ROUTE(app, "/membership_api/<string>")
        .methods(crow::HTTPMethod::Get, 
                 crow::HTTPMethod::Post, 
                 crow::HTTPMethod::Put, 
                 crow::HTTPMethod::Delete)
        ([&](const crow::request& req, std::string member_id) {

        json result;

        if (req.method == crow::HTTPMethod::Post)
        {
            std::unordered_map < std::string, std::string> params = parse_params(req.body);
            std::string value = params.count(member_id) ? params[member_id] : "";
            result = myManager.create(member_id, value);
        }
        else if (req.method == crow::HTTPMethod::Get)
        {
            result = myManager.read(member_id);
        }
        else if (req.method == crow::HTTPMethod::Put)
        {
            std::unordered_map < std::string, std::string> params = parse_params(req.body);
            std::string value = params.count(member_id) ? params[member_id] : "";
            result = myManager.update(member_id, value);
        }
        else if (req.method == crow::HTTPMethod::Delete)
        {
            result = myManager.Delete(member_id);
        }

        return crow::response(result.dump());
            });

    app.port(5000).run();
}