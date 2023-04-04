# C++ OpenAI (community-maintained / unofficial)

This library provides C++ clients for [OpenAI API](https://platform.openai.com/).  
As of April 3 2023 we support every endpoint listed on their official [API specification](https://github.com/openai/openai-openapi/blob/master/openapi.yaml). 

You will find multiple examples and installation instructions below.

##### Table of Contents
[Examples](#Examples) 
[Installation](#Installation)  

## **Endpoints supported (24/24):**  
- [x] `POST /completions`  
- [x] `POST /chat/completions`  
- [x] `POST /edits`  
- [x] `POST /images/generations`  
- [x] `POST /images/edits`  
- [x] `POST /images/variations`  
- [x] `POST /embeddings`  
- [x] `POST /audio/transcriptions`  
- [x] `POST /audio/translations`  
- [x] `GET /files`
- [x] `POST /files`
- [x] `GET /files/{file_id}`
- [x] `DELETE /files/{file_id}`
- [x] `GET /files/{file_id}/content`  
- [x] `GET /fine-tunes`
- [x] `GET /fine-tunes/{fine_tune_id}`  
- [x] `POST /fine-tunes`
- [x] `POST /fine-tunes/{fine_tune_id}/cancel`  
- [x] `GET /fine-tunes/{fine_tune_id}/events`  
- [x] `GET /models`
- [x] `GET /models/{model}`
- [x] `DELETE /models/{model}`
- [x] `POST /moderations`

## Examples

### API Initialization
```c++
#include <openai/openai.hpp>

int main() {
  // 2 options to pass your API Key:
  
  // will get the key from the env var: OPENAI_API_KEY
  openai::API api;
  
  // as argument
  openai::API api("my api key");
}
```

### Chat
```c++
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
```

### Image Generation
```c++
#include <openai/openai.hpp>

// read file to binary
std::string read_file(std::string_view path) {
  std::ifstream file(path, std::ios::binary);
  return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

int main() {
  openai::API api;

  // generate image
  openai::models::ImagesResponse *ret = api.get_image("a white siamese cat");
  std::cout << ret->data[0].url.value() << std::endl;

  // generate image with another size
  ret = api.get_image(
      "a white siamese cat", // prompt
      openai::IMAGE_SIZE::px_512_512, // size
      2, // number of image to generate
      openai::IMAGE_RESPONSE_FORMAT::b64_json // response format (url = default)
      );
  std::cout << ret->data[0].b64_json.value() << std::endl;
  std::cout << ret->data[1].b64_json.value() << std::endl;

  // edit image
  auto image_data = read_file("assets/images/square_with_transparency.png");

  auto resp = api.get_image_edits("Add a cat with a hat", image_data);
  std::cout << resp->data[0].url.value() << std::endl;
}
```

### Text edits
> The edits endpoint can be used to edit text, rather than just completing it. You provide some text and an instruction for how to modify it, and the text-davinci-edit-001 model will attempt to edit it accordingly.
```c++
void example(openai::API *api) {
  auto resp = api->get_edits("What day of the wek is it?", "Fix the spelling mistakes");
  std::cout << resp->choices[0].text << std::endl;
}
```

### Completions
> Learn how to generate or manipulate text
```c++
void example(openai:: API *api) {
  auto resp = api->get_completions("Give me a good punchline for a ice cream shop!");
  std::cout << resp->choices[0].text << std::endl;
}
```

### Files
> Manage files (upload fine-tune files, ...)
```c++
void example(openai::API *api) {
  auto fine_tune_data = read_file("assets/json/fine_tune_data.jsonl");

  auto resp = api->upload_file(fine_tune_data, "fine_tune_data.json");
  std::cout << resp->filename << " " << resp->purpose << std::endl;
  
  const auto files = api->get_files();
  for (const auto f : files->data) {
    std::cout << "Fetching file content for file: " << f.id << std::endl;
    auto content = api->get_file_content(f.id);
    std::cout << content << std::endl;
  }
}
```


### Models
> Lists the currently available models, and provides basic information about each one such as the owner and availability.
```c++
void example(openai::API *api) {
  auto models = api->list_models();
  for (auto m : models->data) {
    std::cout << m.id << std::endl; // print: babbage davinci, ...
  }
}
```

> Retrieves a model instance, providing basic information about the model such as the owner and permissioning.
```c++
void example(openai::API *api) {
  auto model = api->get_model("gpt-3.5-turbo");
  std::cout << model->owned_by << std::endl; // print: openai
}
```

### Fine Tunes
> Learn how to customize a model for your application.
```c++
void example(openai:: API *api) {
  // Start a fine tune
  openai::models::FineTuneRequest request;
  request.batch_size = 2;
  request.model = "davinci";
  request.training_file = "file-123";
  request.validation_file = "file-456";
  auto create_fine_tune_resp = api->create_fine_tune(request);
  std::cout << create_fine_tune_resp->id << std::endl;


  // List all fine-tunes
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
```

### Moderations
> The moderation endpoint is a tool you can use to check whether content complies with OpenAI's usage policies. Developers can thus identify content that our usage policies prohibits and take action, for instance by filtering it.
```c++
void example(openai:: API *api) {
  auto resp = api->get_moderations("I want to kill them.");
  std::cout << resp->results[0].category_scores.hate_threatening << std::endl; 
}
```

## Installation
> This is a header only library
### Clone and install this repository
```bash
git clone git@github.com:ethanquix/OpenAICPP.git
cd OpenAICPP
mkdir build && cd build
cmake ..
sudo make install
```

### Add to your CMake
```cmake
# Add the required library `https://github.com/beached/daw_json_link`
include( FetchContent )
FetchContent_Declare(
  daw_json_link
  GIT_REPOSITORY https://github.com/beached/daw_json_link
  GIT_TAG release
)
FetchContent_MakeAvailable(daw_json_link)

find_package(OpenAI CONFIG REQUIRED)

# Now just add this to link the OpenAI library:
target_link_libraries(my_executable PRIVATE OpenAI::OpenAI)

# Add those flags to enable `https` support (on MacOS)
set(OPENSSL_SUPPORT "-DCPPHTTPLIB_OPENSSL_SUPPORT -I/opt/homebrew/opt/openssl@1.1/include -L/opt/homebrew/opt/openssl@1.1/lib -lssl -lcrypto -framework CoreFoundation -framework Security")
set(CMAKE_CXX_FLAGS ${OPENSSL_SUPPORT}) 
```