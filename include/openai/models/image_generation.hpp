// Code auto generated from json file 'assets/json/images_generations_response.json'

#pragma once

#include <tuple>
#include <cstdint>
#include <string>
#include <vector>
#include <daw/json/daw_json_link.h>

namespace openai {
  namespace models {
    // Request
    struct ImagesGenerationsRequest {
      // A text description of the desired image(s). The maximum length is 1000 characters.
      std::string prompt;
      // The number of images to generate. Must be between 1 and 10.
      int64_t n;
      // The size of the generated images. Must be one of 256x256, 512x512, or 1024x1024.
      std::string size;
      // The format in which the generated images are returned. Must be one of url or b64_json.
      std::string response_format;
      // A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
      std::string user;
    };

    // Response
    struct ImagesResponseElement {
      std::optional<std::string> url;
      std::optional<std::string> b64_json;
    };

    struct ImagesResponse {
      int64_t created;
      std::vector<ImagesResponseElement> data;
    };

  }
}

// JSON defs
namespace daw::json {
  // Request
  template<>
  struct json_data_contract<openai::models::ImagesGenerationsRequest> {
    static constexpr char const mem_prompt[] = "prompt";
    static constexpr char const mem_n[] = "n";
    static constexpr char const mem_size[] = "size";
    static constexpr char const mem_response_format[] = "response_format";
    static constexpr char const mem_user[] = "user";
    using type = json_member_list<
        json_string<mem_prompt>,
        json_number<mem_n, int64_t>,
        json_string<mem_size>,
        json_string<mem_response_format>,
        json_string<mem_user>
    >;

    static inline auto to_json_data(openai::models::ImagesGenerationsRequest const &value) {
      return std::forward_as_tuple(value.prompt, value.n, value.size, value.response_format, value.user);
    }
  };

  // Response

  template<>
  struct json_data_contract<openai::models::ImagesResponseElement> {

    static constexpr char const mem_url[] = "url";
    static constexpr char const mem_b64_json[] = "b64_json";
    using type = json_member_list<
        json_string_null<mem_url>, json_string_null<mem_b64_json>
    >;

    static inline auto to_json_data(openai::models::ImagesResponseElement const &value) {
      return std::forward_as_tuple(value.url, value.b64_json);
    }
  };

  template<>
  struct json_data_contract<openai::models::ImagesResponse> {
    static constexpr char const mem_created[] = "created";
    static constexpr char const mem_data[] = "data";
    using type = json_member_list<
        json_number<mem_created, int64_t>,
        json_array<mem_data,
                   json_class_no_name<openai::models::ImagesResponseElement>,
                   std::vector<openai::models::ImagesResponseElement>>
    >;

    static inline auto to_json_data(openai::models::ImagesResponse const &value) {
      return std::forward_as_tuple(value.created, value.data);
    }
  };
}