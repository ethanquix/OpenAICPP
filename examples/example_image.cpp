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