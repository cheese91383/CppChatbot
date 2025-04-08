#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include <crow.h>
#include <crow/middlewares/cors.h>

#include "./src/bot_engine.hpp"

crow::App<crow::CORSHandler> app;
// map of session_id to bot_engine
std::map<std::string, bot_engine> sessions;

void setupCrow() {
    // CORS = Cross-Origin Resource Sharing
    // allows receiving requests from frontend on port 80
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
            .origin("http://localhost:80");
    // route for open a chat session
    CROW_ROUTE(app, "/open-session")
        .methods("POST"_method)
        ([](const crow::request& req) {
            // decide session_id
            std::string session_id;
            do{
                session_id = std::to_string(rand());
            } while(sessions.find(session_id) != sessions.end());
            
            // create a new bot_engine
            bot_engine engine;
            // add to sessions map
            sessions[session_id] = engine;
            return session_id;
        });
    // route for closing a chat session
    CROW_ROUTE(app, "/close-session/<string>")
        .methods("DELETE"_method)
        ([](const crow::request& req, std::string session_id) {
            // remove session from map
            sessions.erase(session_id);
            // return 200 OK
            return crow::response(200);
        });
    // route for sending a message to a chat session
    CROW_ROUTE(app, "/send-message/<string>")
        .methods("POST"_method)
        ([](const crow::request& req, std::string session_id) {
            // get message from request body
            auto json = nlohmann::json::parse(req.body);
            std::string message = json["message"];
            std::string user_id = json["user_id"];
            // get answer from bot_engine
            std::string answer = sessions[session_id].process_message(message, user_id);
            std::string response = "{\"message\": \"" + answer + "\"}";
            return response;
        });
}

int main() {
    setupCrow();
    app.port(8080).multithreaded().run();
    return 0;
}