#pragma once
#include <httplib.h>
#include <Windows.h>
#include "Json.h"
#include "Utils/Log.h"

namespace Request {
    static Gesture::JsonObject Post(const std::string& url, const Gesture::JsonObject& payload) {
        size_t protocolEndPos = url.find("//") + 2; // Skip the "//" part
        size_t pathStartPos = url.find('/', protocolEndPos);
        if (pathStartPos == std::string::npos) {
            CORE_WARN("Invalid URL, no path found: {0}" ,url);
            return Gesture::JsonObject();
        }

        std::string host = url.substr(0, pathStartPos);
        std::string path = url.substr(pathStartPos);
        
        httplib::Client cli(host);
        std::string payloadString = payload.ToString();
        auto res = cli.Post(path, payloadString.c_str(), "application/json");

        Gesture::JsonObject jsonResponse;

        if (res && res->status == 200) {
           
            jsonResponse.FromString(res->body);
        }
        else {
            CORE_ERROR("HTTP POST request failed");
        }

        return jsonResponse;
    }
}