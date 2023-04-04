#pragma once

#include <string>
#include <utility>
#include <daw/json/daw_json_link.h>
#include "openai/api_utils.hpp"
#include "../lib/httplib.hpp"

namespace openai {
  namespace http {
    class HttpClient {
      httplib::Client *client;
      httplib::Headers headers;

     public:
      explicit HttpClient(const std::string &domain, httplib::Headers headers) : headers(std::move(headers)) {
        this->client = new httplib::Client(domain);
      }

      // parsing json
      template<typename Ret>
      Ret parse_response_content(const std::string &body) {
        auto obj = daw::json::from_json<Ret>(body,
                                             daw::json::options::parse_flags<daw::json::options::UseExactMappingsByDefault::no,
                                                                             daw::json::options::CheckedParseMode::no>);
        return std::move(obj);
      }

      template<typename Ret>
      Ret parse_http_response(httplib::Result *result,
                              const std::string &path,
                              const std::string *query_body = nullptr) {
        if (result->error() != httplib::Error::Success) {
          throw std::runtime_error(httplib::to_string(result->error()));
        }

        auto const value = result->value();
        if (value.status == 200) {
          try {
            if constexpr (std::is_same<Ret, std::string>::value) {
              return value.body;
            }
            return parse_response_content<Ret>(value.body);
          } catch (const std::exception &exc) {
            throw std::runtime_error(
                "exception: " + std::string{exc.what()} +
                    "\nurl is: " + path +
                    "\nResponse body is:\n" + value.body
            );
          }
        }

        if (query_body != nullptr) {
          throw std::runtime_error(
              "Response status not success: " + std::to_string(value.status) +
                  "\nurl is: " + path +
                  "\nQuery body:\n" + *query_body +
                  "\nResponse body:\n" + value.body);
        } else {
          throw std::runtime_error(
              "Response status not success: " + std::to_string(value.status) +
                  "\nurl is: " + path +
                  "\nResponse body is:\n" + value.body);
        }
      }

      // GET
      template<typename Ret>
      Ret get(const std::string &path) {
        auto result = this->client->Get(path, headers);
        return parse_http_response<Ret>(&result, path);
      }

      // POST without body
      template<typename Ret>
      Ret post(const std::string &path) {
        // req
        auto result = this->client->Post(path, headers);
        // parse
        return parse_http_response<Ret>(&result, path);
      }

      // POST + JSON body
      template<typename Input, typename Ret>
      Ret post(const std::string &path, const Input &data, const std::string &content_type = "application/json") {
        // parse json
        const auto body = daw::json::to_json(data);
        // req
        auto result = this->client->Post(path, headers, body, content_type);
        // parse
        return parse_http_response<Ret>(&result, path, &body);
      }

      // POST + Multipart
      template<typename Ret>
      Ret post(const std::string &path, const httplib::MultipartFormDataItems &data_items) {
        // req
        auto result = this->client->Post(path, headers, data_items);
        // parse
        return parse_http_response<Ret>(&result, path);
      }

      // DELETE
      template<typename Ret>
      Ret delete_(const std::string &path) {
        auto result = this->client->Delete(path, headers);
        return parse_http_response<Ret>(&result, path);
      }
    };
  }
}