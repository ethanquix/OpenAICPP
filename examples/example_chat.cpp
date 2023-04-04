#include <openai/openai.hpp>

int main() {
  openai::API api;

  // chat with chatgpt -- the library will always send the full history, you don't need to handle this yourself
  openai::Chat chat = api.new_chat(openai::AI_MODELS::GPT3Dot5Turbo);

  auto chat_response = chat.say("Hello ChatGPT! My name is Dimitri");
  std::cout << "chatgpt: " << chat_response->text() << std::endl;

  chat_response = chat.say("What is my name?");
  std::cout << "chatgpt: " << chat_response->text() << std::endl;

  // send multiple messages
  chat_response = chat.say(std::vector<openai::models::ChatCompletionRequestMessage>{
      {to_str(openai::CHAT_ROLES::system), "You are a french teacher and answer in french"},
      {to_str(openai::CHAT_ROLES::user), "How are you?"}
  });
  std::cout << "chatgpt: " << chat_response->text() << std::endl;

  // Display the entire conversation
  std::cout << "\nConversation:\n" << chat << std::endl;
}