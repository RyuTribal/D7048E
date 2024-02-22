#pragma once

#include <json.hpp>
#include "Utils/Log.h"

using json = nlohmann::json;

namespace Gesture {
    class JsonObject {
    public:
        JsonObject() = default;
        void FromString(const std::string& jsonString) {
            try {
                data_ = json::parse(jsonString);
            }
            catch (json::parse_error& e) {
                CORE_ERROR("JSON parse error: {0}", e.what());
            }
        }

        std::string ToString() const {
            return data_.dump();
        }

        template<typename T>
        void SetValue(const std::string& key, const T& value) {
            data_[key] = value;
        }

        template<typename T>
        T GetValue(const std::string& key) const {
            try {
                return data_.at(key).get<T>();
            }
            catch (json::out_of_range& e) {
                CORE_ERROR("JSON key error: {0}",  e.what());
                return T();
            }
        }

    private:
        json data_;
    };
}
