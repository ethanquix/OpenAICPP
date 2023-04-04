#pragma once

#include <tuple>
#include <cstdint>
#include <string>
#include <daw/json/daw_json_link.h>
#include "commons.hpp"

// Models
namespace openai::models {
  // Request

  struct EditsRequest {
    // ID of the model to use.
    // You can use the text-davinci-edit-001 or code-davinci-edit-001 model with this endpoint.
    std::string model;
    // The input text to use as a starting point for the edit.
    //  example: What day of the wek is it?
    std::string input;
    // The instruction that tells the model how to edit the prompt.
    //  example: Fix the spelling mistakes.
    std::string instruction;
    // How many edits to generate for the input and instruction.
    int64_t n;
    // What sampling temperature to use, between 0 and 2. Higher values like 0.8 will make the output more random, while lower values like 0.2 will make it more focused and deterministic.
    // We generally recommend altering this or top_p but not both.
    // minimum: 0
    // maximum: 2
    // default: 1
    int64_t temperature;
    // An alternative to sampling with temperature, called nucleus sampling, where the model considers the results of the tokens with top_p probability mass. So 0.1 means only the tokens comprising the top 10% probability mass are considered.
    // We generally recommend altering this or temperature but not both.
    // minimum: 0
    // maximum: 1
    // default: 1
    int64_t top_p;
  };

  // Response
  struct EditsResponseChoices {
    std::string text;
    int64_t index;
    std::optional<std::string> finish_reason;
  };

  struct EditsResponse {
    std::string object;
    int64_t created;
    std::vector<EditsResponseChoices> choices;
    Usage usage;
  };
}

// JSON defs
namespace daw::json {
  // Request
  template<>
  struct json_data_contract<openai::models::EditsRequest> {
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_input[] = "input";
    static constexpr char const mem_instruction[] = "instruction";
    static constexpr char const mem_n[] = "n";
    static constexpr char const mem_temperature[] = "temperature";
    static constexpr char const mem_top_p[] = "top_p";
    using type = json_member_list<
        json_string<mem_model>,
        json_string<mem_input>,
        json_string<mem_instruction>,
        json_number<mem_n, int64_t>,
        json_number<mem_temperature, int64_t>,
        json_number<mem_top_p, int64_t>
    >;

    static inline auto to_json_data(openai::models::EditsRequest const &value) {
      return std::forward_as_tuple(value.model,
                                   value.input,
                                   value.instruction,
                                   value.n,
                                   value.temperature,
                                   value.top_p);
    }
  };

  // Response
  template<>
  struct json_data_contract<openai::models::EditsResponseChoices> {
    static constexpr char const mem_text[] = "text";
    static constexpr char const mem_index[] = "index";
    static constexpr char const mem_finish_reason[] = "finish_reason";
    using type = json_member_list<
        json_string<mem_text>, json_number<mem_index, int64_t>, json_string_null<mem_finish_reason>
    >;

    static inline auto to_json_data(openai::models::EditsResponseChoices const &value) {
      return std::forward_as_tuple(value.text, value.index, value.finish_reason);
    }
  };

  template<>
  struct json_data_contract<openai::models::EditsResponse> {
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_created[] = "created";
    static constexpr char const mem_choices[] = "choices";
    static constexpr char const mem_usage[] = "usage";
    using type = json_member_list<
        json_string<mem_object>,
        json_number<mem_created, int64_t>,
        json_array<mem_choices,
                   json_class_no_name<openai::models::EditsResponseChoices>,
                   std::vector<openai::models::EditsResponseChoices>>,
        json_class<mem_usage, openai::models::Usage>
    >;

    static inline auto to_json_data(openai::models::EditsResponse const &value) {
      return std::forward_as_tuple(value.object, value.created, value.choices, value.usage);
    }
  };
}

// defaults
namespace openai::models {
  inline EditsRequest get_default_edits_request() {
    EditsRequest req;
    req.model = "text-davinci-edit-001";
    req.n = 1;
    req.temperature = 1;
    req.top_p = 1;

    return req;
  }
}