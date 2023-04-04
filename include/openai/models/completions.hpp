#pragma once

#include <string>
#include <daw/json/daw_json_link.h>
#include "commons.hpp"

namespace openai::models {
  // Request

  struct CompletionsRequest {
    // ID of the model to use.
    // You can use the List models API to see all of your available models,
    //  or see our Model overview for descriptions of them.
    // see: https://platform.openai.com/docs/api-reference/models/list
    // see: https://platform.openai.com/docs/models/overview
    std::string model;
    // WARNING: Only support `string` for now
    // The prompt(s) to generate completions for, encoded as a string, array of strings, array of tokens, or array of token arrays.
    //
    // Note that <|endoftext|> is the document separator that the model sees during training,
    //  so if a prompt is not specified the model will generate as if from the beginning of a new document.
    std::string prompt;
    // The suffix that comes after a completion of inserted text.
    std::string suffix;
    // The maximum number of tokens to generate in the completion.
    // The token count of your prompt plus max_tokens cannot exceed the model's context length.
    // Most models have a context length of 2048 tokens (except for the newest models, which support 4096).
    // see: // see: https://platform.openai.com/tokenizer
    int64_t max_tokens;
    // What sampling temperature to use, between 0 and 2.
    // Higher values like 0.8 will make the output more random,
    //  while lower values like 0.2 will make it more focused and deterministic.
    //
    // We generally recommend altering this or top_p but not both.
    //
    // minimum: 0
    // maximum: 2
    // default: 1
    int64_t temperature;
    // An alternative to sampling with temperature, called nucleus sampling,
    //  where the model considers the results of the tokens with top_p probability mass.
    // So 0.1 means only the tokens comprising the top 10% probability mass are considered.
    //
    // We generally recommend altering this or temperature but not both.
    //
    // minimum: 0
    // maximum: 1
    // default: 1
    int64_t top_p;
    // How many chat completion choices to generate for each input message.
    int64_t n;
    // Echo back the prompt in addition to the completion
    bool echo;
    // 1 sequence where the API will stop generating further tokens. The returned text will not contain the stop sequence.
    std::string stop;
    // Number between -2.0 and 2.0.
    // Positive values penalize new tokens based on whether they appear in the text so far,
    //  increasing the model's likelihood to talk about new topics.
    // see: https://platform.openai.com/docs/api-reference/parameter-details
    int64_t presence_penalty;
    // Number between -2.0 and 2.0.
    // Positive values penalize new tokens based on their existing frequency in the text so far,
    //  decreasing the model's likelihood to repeat the same line verbatim.
    // see: https://platform.openai.com/docs/api-reference/parameter-details
    int64_t frequency_penalty;
    // Generates best_of completions server-side and returns the "best" (the one with the highest log probability per token).
    // Results cannot be streamed.
    // When used with n, best_of controls the number of candidate completions and n specifies how many to return
    //  – best_of must be greater than n.

    // Note: Because this parameter generates many completions, it can quickly consume your token quota.
    // Use carefully and ensure that you have reasonable settings for max_tokens and stop.
    //  default: 1
    //  minimum: 0
    //  maximum: 20
    int64_t best_of;
    // A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
    // see: https://platform.openai.com/docs/guides/safety-best-practices/end-user-ids
    std::string user;
  };

  // Response

  struct CompletionsResponseChoices {
    std::string text;
    int64_t index;
    std::string finish_reason;
  };

  struct CompletionsResponse {
    std::string id;
    std::string object;
    int64_t created;
    std::string model;
    std::vector<CompletionsResponseChoices> choices;
    openai::models::Usage usage;
  };
}

// JSON defs
namespace daw::json {
  template<>
  struct json_data_contract<openai::models::CompletionsRequest> {
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_prompt[] = "prompt";
    static constexpr char const mem_suffix[] = "suffix";
    static constexpr char const mem_max_tokens[] = "max_tokens";
    static constexpr char const mem_temperature[] = "temperature";
    static constexpr char const mem_top_p[] = "top_p";
    static constexpr char const mem_n[] = "n";
    static constexpr char const mem_echo[] = "echo";
    static constexpr char const mem_stop[] = "stop";
    static constexpr char const mem_presence_penalty[] = "presence_penalty";
    static constexpr char const mem_frequency_penalty[] = "frequency_penalty";
    static constexpr char const mem_best_of[] = "best_of";
    static constexpr char const mem_user[] = "user";
    using type = json_member_list<
        json_string<mem_model>,
        json_string<mem_prompt>,
        json_string<mem_suffix>,
        json_number<mem_max_tokens, int64_t>,
        json_number<mem_temperature, int64_t>,
        json_number<mem_top_p, int64_t>,
        json_number<mem_n, int64_t>,
        json_bool<mem_echo>,
        json_string<mem_stop>,
        json_number<mem_presence_penalty, int64_t>,
        json_number<mem_frequency_penalty, int64_t>,
        json_number<mem_best_of, int64_t>,
        json_string<mem_user>
    >;

    static inline auto to_json_data(openai::models::CompletionsRequest const &value) {
      return std::forward_as_tuple(value.model,
                                   value.prompt,
                                   value.suffix,
                                   value.max_tokens,
                                   value.temperature,
                                   value.top_p,
                                   value.n,
                                   value.echo,
                                   value.stop,
                                   value.presence_penalty,
                                   value.frequency_penalty,
                                   value.best_of,
                                   value.user);
    }
  };

  template<>
  struct json_data_contract<openai::models::CompletionsResponseChoices> {
    static constexpr char const mem_text[] = "text";
    static constexpr char const mem_index[] = "index";
    static constexpr char const mem_finish_reason[] = "finish_reason";
    using type = json_member_list<
        json_string<mem_text>,
        json_number<mem_index, int64_t>,
        json_string<mem_finish_reason>
    >;

    static inline auto to_json_data(openai::models::CompletionsResponseChoices const &value) {
      return std::forward_as_tuple(value.text, value.index, value.finish_reason);
    }
  };

  template<>
  struct json_data_contract<openai::models::CompletionsResponse> {
    static constexpr char const mem_id[] = "id";
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_created[] = "created";
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_choices[] = "choices";
    static constexpr char const mem_usage[] = "usage";
    using type = json_member_list<
        json_string<mem_id>,
        json_string<mem_object>,
        json_number<mem_created, int64_t>,
        json_string<mem_model>,
        json_array<mem_choices,
                   json_class_no_name<openai::models::CompletionsResponseChoices>,
                   std::vector<openai::models::CompletionsResponseChoices>>,
        json_class<mem_usage, openai::models::Usage>
    >;

    static inline auto to_json_data(openai::models::CompletionsResponse const &value) {
      return std::forward_as_tuple(value.id, value.object, value.created, value.model, value.choices, value.usage);
    }
  };
}

namespace openai::models {
  inline CompletionsRequest get_default_completions_request() {
    CompletionsRequest req;
    req.model = "text-davinci-003";
    req.prompt = "";
    req.suffix = "";
    req.max_tokens = 16;
    req.temperature = 1;
    req.top_p = 1;
    req.n = 1;
    req.echo = false;
    req.presence_penalty = 0;
    req.frequency_penalty = 0;
    req.best_of = 1;
    req.user = "";

    return req;
  }
}