// Code auto generated from json file 'assets/json/embed.json'

#pragma once

#include <tuple>
#include <string>
#include <daw/json/daw_json_link.h>

namespace openai::models {
  // Request
  struct EmbeddingRequest {
    // ID of the model to use.
    // You can use the List models API to see all of your available models,
    //  or see our Model overview for descriptions of them.
    // see: https://platform.openai.com/docs/api-reference/models/list
    // see: https://platform.openai.com/docs/models/overview
    //
    // example: text-embedding-ada-002
    std::string model;
    // Input text to get embeddings for, encoded as a string.
    // Must not exceed 8192 tokens in length.
    std::string input;
    // A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse
    std::string user;
  };

  // Response
  struct EmbeddingResponseElement {
    int64_t index;
    std::string object;
    std::vector<float> embedding;
  };

  struct EmbeddingResponseUsage {
    int64_t prompt_tokens;
    int64_t total_tokens;
  };

  struct EmbeddingResponse {
    std::string object;
    std::string model;
    std::vector<EmbeddingResponseElement> data;
    EmbeddingResponseUsage usage;
  };
}

// jSON defs
namespace daw::json {
  // Request
  template<>
  struct json_data_contract<openai::models::EmbeddingRequest> {
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_input[] = "input";
    static constexpr char const mem_user[] = "user";
    using type = json_member_list<
        json_string<mem_model>, json_string<mem_input>, json_string<mem_user>
    >;

    static inline auto to_json_data(openai::models::EmbeddingRequest const &value) {
      return std::forward_as_tuple(value.model, value.input, value.user);
    }
  };

  // Response
  template<>
  struct json_data_contract<openai::models::EmbeddingResponseElement> {
    static constexpr char const mem_index[] = "index";
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_embedding[] = "embedding";
    using type = json_member_list<
        json_number<mem_index, int64_t>,
        json_string<mem_object>,
        json_array<mem_embedding, float, std::vector<float>>
    >;

    static inline auto to_json_data(openai::models::EmbeddingResponseElement const &value) {
      return std::forward_as_tuple(value.index, value.object, value.embedding);
    }
  };

  template<>
  struct json_data_contract<openai::models::EmbeddingResponseUsage> {
    static constexpr char const mem_prompt_tokens[] = "prompt_tokens";
    static constexpr char const mem_total_tokens[] = "total_tokens";
    using type = json_member_list<
        json_number<mem_prompt_tokens, int64_t>, json_number<mem_total_tokens, int64_t>
    >;

    static inline auto to_json_data(openai::models::EmbeddingResponseUsage const &value) {
      return std::forward_as_tuple(value.prompt_tokens, value.total_tokens);
    }
  };

  template<>
  struct json_data_contract<openai::models::EmbeddingResponse> {
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_data[] = "data";
    static constexpr char const mem_usage[] = "usage";
    using type = json_member_list<
        json_string<mem_object>,
        json_string<mem_model>,
        json_array<mem_data,
                   json_class_no_name<openai::models::EmbeddingResponseElement>,
                   std::vector<openai::models::EmbeddingResponseElement>>,
        json_class<mem_usage, openai::models::EmbeddingResponseUsage>
    >;

    static inline auto to_json_data(openai::models::EmbeddingResponse const &value) {
      return std::forward_as_tuple(value.object, value.model, value.data, value.usage);
    }
  };
}
