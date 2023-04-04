#include <openai/openai.hpp>
#include <openai/models/chat.hpp>

auto api = new openai::API();

// utils
std::string read_file(std::string_view path) {
  std::ifstream file(path, std::ios::binary);
  return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

// Examples

void image_generation() {
  // generate image
  const auto ret = api->get_image("a white siamese cat");
  std::cout << ret->data[0].url.value() << std::endl;
}

void chat_example() {
  // chat with chatgpt
  auto chat = api->new_chat(openai::AI_MODELS::GPT3Dot5Turbo);

  auto chat_response = chat.say("Hello ChatGPT! My name is Georges");
  std::cout << "chatgpt: " << chat_response->text() << std::endl;

  chat_response = chat.say("What is my name?");
  std::cout << "chatgpt: " << chat_response->text() << std::endl;

  chat_response = chat.say(std::vector<openai::models::ChatCompletionRequestMessage>{
      {to_str(openai::CHAT_ROLES::system), "You are a french teacher and answer in french"},
      {to_str(openai::CHAT_ROLES::user), "How are you?"}
  });
  std::cout << "chatgpt: " << chat_response->text() << std::endl;

  // Display the entire conversation
//  std::cout << chat << std::endl;
}

void get_file_example() {
  const auto files = api->get_files();
  for (const auto f : files->data) {
    std::cout << "Fetching file content for file: " << f.id << std::endl;
    auto content = api->get_file_content(f.id);
    std::cout << content << std::endl;
  }
}

void get_model_example() {
  auto models = api->list_models();
  for (auto m : models->data) {
    std::cout << m.id << std::endl; // print: babbage davinci, ...
  }

  auto model = api->get_model("gpt-3.5-turbo");
  std::cout << model->owned_by << std::endl; // print: openai
}

void get_completions() {
  auto resp = api->get_completions("Give me a good punchline for a ice cream shop!");
  std::cout << resp->choices[0].text << std::endl;
}

void get_edits() {
  auto resp = api->get_edits("What day of the wek is it?", "Fix the spelling mistakes");
  std::cout << resp->choices[0].text << std::endl;
}

void moderations() {
  auto resp = api->get_moderations("I want to kill them.");
  std::cout << resp->results[0].category_scores.hate_threatening << std::endl;
}

void embeddings() {
  auto resp = api->get_embeddings("Hello world");
  for (const auto emb : resp->data[0].embedding) {
    std::cout << emb << std::endl;
  }
}

void image_variations() {
  // image to binary
  auto image_data = read_file("assets/images/red_square.png");

  auto resp = api->get_image_variations(image_data);
  std::cout << resp->data[0].url.value() << std::endl;
}

void image_edits() {
  // image to binary
  auto image_data = read_file("assets/images/square_with_transparency.png");

  auto resp = api->get_image_edits("Add a cat with a hat", image_data);
  std::cout << resp->data[0].url.value() << std::endl;
}

void upload_file() {
  auto fine_tune_data = read_file("assets/json/fine_tune_data.jsonl");

  auto resp = api->upload_file(fine_tune_data, "fine_tune_data.json");
  std::cout << resp->filename << " " << resp->purpose << std::endl;
}

void fine_tunes() {
  // Start a fine tune
  openai::models::FineTuneRequest request;
  request.batch_size = 2;
  request.model = "davinci";
  request.training_file = "file-123";
  request.validation_file = "file-456";
  auto create_fine_tune_resp = api->create_fine_tune(request);
  std::cout << create_fine_tune_resp->id << std::endl;


  // List all fine tunes
  auto resp = api->list_fine_tunes();
  for (const auto &f : resp->data) {
    std::cout << f.id << std::endl;
  }

  // Get events for a specific fine tune job
  auto fine_tune_events = api->get_fine_tune_events("fine_tune_123");
  for (const auto &ev : fine_tune_events->data) {
    std::cout << ev.message << std::endl;
  }
}

int main() {
  get_completions();
  get_edits();
  get_model_example();
  image_generation();
  chat_example();
  get_file_example();
  embeddings();
  moderations();
  image_variations();
  image_edits();
  upload_file();
  fine_tunes();
}