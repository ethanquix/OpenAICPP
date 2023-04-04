# pragma once

#include <ostream>
#include "lib/httplib.hpp"
#include "openai/models/chat.hpp"
#include "enums.hpp"
#include "api_utils.hpp"


/// Example:
/// @code{.cpp}
///    #include "openai/openai.hpp"
///
///    int main() {
///     openai::API api;
///
///     // chat with chatgpt -- the library will always send back the full history
///     openai::Chat chat = api.new_chat(openai::AI_MODELS::GPT3Dot5Turbo);
///
///     auto chat_response = chat.say("Hello ChatGPT! My name is Dimitri");
///     std::cout << "chatgpt: " << chat_response->text() << std::endl;
///
///     chat_response = chat.say("What is my name?");
///     std::cout << "chatgpt: " << chat_response->text() << std::endl;
///
///     // send multiple messages
///     chat_response = chat.say(std::vector<openai::models::ChatCompletionRequestMessage>{
///         {to_str(openai::CHAT_ROLES::system), "You are a french teacher and answer in french"},
///         {to_str(openai::CHAT_ROLES::user), "How are you?"}
///     });
///     std::cout << "chatgpt: " << chat_response->text() << std::endl;
///
///     // Display the entire conversation
///     std::cout << "\nConversation:\n" << chat << std::endl;
///    }
/// @endcode

namespace openai {

  // Given a chat conversation, the model will return a chat completion response.
  // This chat class encapsulate a conversation
  // We will always send back the full history, you don't have to handle that!
  //
  // see: https://platform.openai.com/docs/api-reference/chat
  class Chat {
   private:
    // http client
    http::HttpClient *http_client;
    AI_MODELS model;

    std::vector<models::ChatCompletionRequestMessage> chat_history;

   public:
    explicit Chat(http::HttpClient *http_client, AI_MODELS model) {
      this->http_client = http_client;
      this->model = model;
    }

    // send a message
    models::ChatCompletionsResponse *say(const std::string &text) {
      models::ChatCompletionRequest chat_request = this->new_default_request();
      models::ChatCompletionRequestMessage message;
      message.role = to_str(CHAT_ROLES::user);
      message.content = text;

      chat_request.messages = std::vector<models::ChatCompletionRequestMessage>{message};

      return this->send_message(chat_request);
    }

    // send a message by specifying everything in the request
    models::ChatCompletionsResponse *say(models::ChatCompletionRequest &chat_request) {
      return this->send_message(chat_request);
    }

    friend std::ostream &operator<<(std::ostream &os, const Chat &chat) {
      std::string out;
      for (const auto &item : chat.chat_history) {
        os << item.role << ": " << item.content << "\n";
      }
      return os;
    }

    // send multiple messages
    models::ChatCompletionsResponse *say(const std::vector<models::ChatCompletionRequestMessage> &new_messages) {
      models::ChatCompletionRequest chat_request = this->new_default_request();
      models::ChatCompletionRequestMessage message;

      chat_request.model = to_str(this->model);
      chat_request.messages = new_messages;

      return this->send_message(chat_request);
    }

   private:
    inline models::ChatCompletionRequest new_default_request() {
      models::ChatCompletionRequest chat_request;

      chat_request.model = to_str(this->model);
      chat_request.temperature = 1;
      chat_request.top_p = 1;
      chat_request.n = 1;
      chat_request.stream = false; // not supported for now
      chat_request.presence_penalty = 0;
      chat_request.frequency_penalty = 0;
      chat_request.user = "";

      return chat_request;
    }

    models::ChatCompletionsResponse *send_message(models::ChatCompletionRequest &msg) {
      if (msg.stream) {
        throw std::runtime_error("stream for chat is not enabled for now. Feel free to open a PR!");
      }

      // add new message to message history
      this->chat_history.insert(this->chat_history.end(), msg.messages.begin(), msg.messages.end());

      // use message history as message source
      msg.messages = this->chat_history;

      auto response =
          this->http_client->post<models::ChatCompletionRequest, models::ChatCompletionsResponse *>(
              "/v1/chat/completions",
              msg
          );
      const auto resp = response->choices[0].message;
      this->chat_history.push_back({.role = resp.role, .content = resp.content});
      return response;
    }
  };
}