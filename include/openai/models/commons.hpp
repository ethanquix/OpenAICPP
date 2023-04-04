#pragma once

#include <cstdint>
#include <daw/json/daw_json_link.h>

// Models
namespace openai::models {
  struct Usage {
    int64_t prompt_tokens;
    int64_t completion_tokens;
    int64_t total_tokens;
  };
}

// JSON defs
namespace daw::json {
  template<>
  struct json_data_contract<openai::models::Usage> {
    static constexpr char const mem_prompt_tokens[] = "prompt_tokens";
    static constexpr char const mem_completion_tokens[] = "completion_tokens";
    static constexpr char const mem_total_tokens[] = "total_tokens";
    using type = json_member_list<
        json_number<mem_prompt_tokens, int64_t>,
        json_number<mem_completion_tokens, int64_t>,
        json_number<mem_total_tokens, int64_t>
    >;

    static inline auto to_json_data(openai::models::Usage const &value) {
      return std::forward_as_tuple(value.prompt_tokens, value.completion_tokens, value.total_tokens);
    }
  };
}