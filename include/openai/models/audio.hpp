#pragma once

#include <tuple>
#include <cstdint>
#include <string>
#include <daw/json/daw_json_link.h>
#include "commons.hpp"

namespace openai::models {
  struct AudioResponse {
    std::string text;
  };
}

namespace daw::json {
  template<>
  struct json_data_contract<openai::models::AudioResponse> {
    static constexpr char const mem_text[] = "text";
    using type = json_member_list<
        json_string<mem_text>
    >;

    static inline auto to_json_data(openai::models::AudioResponse const &value) {
      return std::forward_as_tuple(value.text);
    }
  };
}
