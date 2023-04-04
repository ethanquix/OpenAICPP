#pragma once

#include <tuple>
#include <optional>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <daw/json/daw_json_link.h>
#include "commons.hpp"

namespace openai {
  namespace models {
    // Request Models

    struct ChatCompletionRequestMessage {
      // The role of the author of this message.
      // [system, user, assistant]
      //  - system = helps set the behavior of the assistant Eg: You are a french teacher
      //  - user = the user. Eg: How to say hello in french?
      //  - assistant = chatGPT answer. Eg: Bonjour
      //
      // warning: gpt-3.5-turbo-0301 does not always pay strong attention to system messages.
      //  Future models will be trained to pay stronger attention to system messages.
      std::string role;
      // The contents of the message
      std::string content;
      // The name of the user in a multi-user chat
      std::optional<std::string> name;
    };

    struct ChatCompletionRequest {
      // ID of the model to use. Currently, only gpt-3.5-turbo and gpt-3.5-turbo-0301 are supported.
      std::string model;
      // The messages to generate chat completions for, in the chat format.
      // see: https://platform.openai.com/docs/guides/chat/introduction
      std::vector<ChatCompletionRequestMessage> messages;
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
      // WARNING: NOT SUPPORTED FOR NOW!!!
      //
      // If set, partial message deltas will be sent, like in ChatGPT.
      // Tokens will be sent as data-only server-sent events as they become available,
      //  with the stream terminated by a data: [DONE] message.
      bool stream;
      // The maximum number of tokens allowed for the generated answer.
      // By default, the number of tokens the model can return will be (4096 - prompt tokens).
      std::optional<int64_t> max_tokens;
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
      // A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
      // see: https://platform.openai.com/docs/guides/safety-best-practices/end-user-ids
      std::string user;
    };

    // Response Models
    struct ChatCompletionResponseMessage {
      // The role of the author of this message.
      // [system, user, assistant]
      std::string role;
      // The contents of the message
      std::string content;
    };

    struct ChatCompletionResponseMessageWrapper {
      // The list of messages sent back by the AI
      ChatCompletionResponseMessage message;
      std::string finish_reason;
      int64_t index;
    };

    struct ChatCompletionsResponse {
      std::string id;
      std::string object;
      int64_t created;
      std::string model;
      std::vector<ChatCompletionResponseMessageWrapper> choices;
      Usage usage;

      std::string text() {
        if (this->choices.size() == 0) {
          return "";
        }
        return this->choices[0].message.content;
      }
    };
  }
}

// JSON defs
namespace daw::json {
  // Request
  template<>
  struct json_data_contract<openai::models::ChatCompletionRequestMessage> {
    static constexpr char const mem_role[] = "role";
    static constexpr char const mem_content[] = "content";
    static constexpr char const mem_name[] = "name";
    using type = json_member_list<
        json_string<mem_role>, json_string<mem_content>, json_string_null<mem_name>
    >;

    static inline auto to_json_data(openai::models::ChatCompletionRequestMessage const &value) {
      return std::forward_as_tuple(value.role, value.content, value.name);
    }
  };

  template<>
  struct json_data_contract<openai::models::ChatCompletionRequest> {
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_messages[] = "messages";
    static constexpr char const mem_temperature[] = "temperature";
    static constexpr char const mem_top_p[] = "top_p";
    static constexpr char const mem_n[] = "n";
    static constexpr char const mem_stream[] = "stream";
    static constexpr char const mem_max_tokens[] = "max_tokens";
    static constexpr char const mem_presence_penalty[] = "presence_penalty";
    static constexpr char const mem_frequency_penalty[] = "frequency_penalty";
    static constexpr char const mem_user[] = "user";
    using type = json_member_list<
        json_string<mem_model>,
        json_array<mem_messages,
                   json_class_no_name<openai::models::ChatCompletionRequestMessage>,
                   std::vector<openai::models::ChatCompletionRequestMessage>>,
        json_number<mem_temperature, int64_t>,
        json_number<mem_top_p, int64_t>,
        json_number<mem_n, int64_t>,
        json_bool<mem_stream>,
        json_number_null<mem_max_tokens, int64_t>,
        json_number<mem_presence_penalty, int64_t>,
        json_number<mem_frequency_penalty, int64_t>,
        json_string<mem_user>
    >;

    static inline auto to_json_data(openai::models::ChatCompletionRequest const &value) {
      return std::forward_as_tuple(value.model,
                                   value.messages,
                                   value.temperature,
                                   value.top_p,
                                   value.n,
                                   value.stream,
                                   value.max_tokens,
                                   value.presence_penalty,
                                   value.frequency_penalty,
                                   value.user);
    }
  };

  // Response
  template<>
  struct json_data_contract<openai::models::ChatCompletionResponseMessage> {
    static constexpr char const mem_role[] = "role";
    static constexpr char const mem_content[] = "content";
    using type = json_member_list<
        json_string<mem_role>, json_string<mem_content>
    >;

    static inline auto to_json_data(openai::models::ChatCompletionResponseMessage const &value) {
      return std::forward_as_tuple(value.role, value.content);
    }
  };

  template<>
  struct json_data_contract<openai::models::ChatCompletionResponseMessageWrapper> {
    static constexpr char const mem_message[] = "message";
    static constexpr char const mem_finish_reason[] = "finish_reason";
    static constexpr char const mem_index[] = "index";
    using type = json_member_list<
        json_class<mem_message, openai::models::ChatCompletionResponseMessage>,
        json_string<mem_finish_reason>,
        json_number<mem_index, int64_t>
    >;

    static inline auto to_json_data(openai::models::ChatCompletionResponseMessageWrapper const &value) {
      return std::forward_as_tuple(value.message, value.finish_reason, value.index);
    }
  };

  template<>
  struct json_data_contract<openai::models::ChatCompletionsResponse> {
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
                   json_class_no_name<openai::models::ChatCompletionResponseMessageWrapper>,
                   std::vector<openai::models::ChatCompletionResponseMessageWrapper>>,
        json_class<mem_usage, openai::models::Usage>
    >;

    static inline auto to_json_data(openai::models::ChatCompletionsResponse const &value) {
      return std::forward_as_tuple(value.id, value.object, value.created, value.model, value.choices, value.usage);
    }
  };
}
