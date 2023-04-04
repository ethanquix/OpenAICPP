#pragma once

#include <string>
#include <utility>
#include "openai/api_utils.hpp"
#include "openai/enums.hpp"

// models
#include "openai/models/models.hpp"
#include "openai/models/chat.hpp"
#include "openai/models/image_generation.hpp"
#include "chat.hpp"
#include "openai/models/files.hpp"
#include "openai/models/completions.hpp"
#include "openai/models/edits.hpp"
#include "openai/models/moderations.hpp"
#include "openai/models/embedding.hpp"
#include "openai/models/audio.hpp"
#include "openai/models/fine_tune.hpp"

namespace openai {
  class API {
   private:
    std::string api_key;
    std::string organization;
    std::string domain;

    // http client
    http::HttpClient *http_client;

   public:
    /// Create a new API object that you will use to query the OpenAI API
    /// \param api_key API Key. If empty will use the value from the OPENAI_API_KEY env var
    /// \param organization optional: Organization ID. Used when your account has multiple organizations
    /// \param domain OpenAPI domain. Modify it if you want to test on a beta or a private API mocking the OpenAPI one
    explicit API(std::string api_key = "",
                 std::string organization = "",
                 std::string domain = "https://api.openai.com") {
      if (api_key.empty()) {
        // get key from ENV as specified in API guidelines
        auto _api_key_env = std::getenv("OPENAI_API_KEY");
        if (_api_key_env != nullptr) {
          api_key = std::string{_api_key_env};
        }
      }

      if (api_key.empty()) {
        throw std::runtime_error(
            "api key not found. You can specify it with the OPENAI_API_KEY env var or as first argument when creating the OpenAI object");
      }

      this->api_key = api_key;
      this->organization = std::move(organization);
      this->domain = std::move(domain);

      this->http_client = new http::HttpClient(this->domain, this->create_authorization_headers());
    }

   private:
    httplib::Headers create_authorization_headers() {
      if (!this->organization.empty()) {
        return {
            {"Authorization", "Bearer " + this->api_key},
            {"OpenAI-Organization", this->organization},
        };
      }
      return {
          {"Authorization", "Bearer " + this->api_key}
      };
    }

   public:
    // Endpoints

    // Given a prompt, the model will return one or more predicted completions,
    //  and can also return the probabilities of alternative tokens at each position.
    // GET /v1/completions
    // see: https://platform.openai.com/docs/api-reference/completions
    models::CompletionsResponse *get_completions(const std::string &prompt,
                                                 const int max_tokens = 16,
                                                 const AI_MODELS model = AI_MODELS::GPT3TextDavinci003
    ) {
      auto req = models::get_default_completions_request();
      req.prompt = prompt;
      req.model = to_str(model);
      req.max_tokens = max_tokens;

      return this->http_client->post<models::CompletionsRequest, models::CompletionsResponse *>(
          "/v1/completions",
          req
      );
    }

    // Given a prompt and an instruction, the model will return an edited version of the prompt.
    // GET /v1/edits
    // see: https://platform.openai.com/docs/api-reference/edits
    models::EditsResponse *get_edits(
        const std::string &input,
        const std::string &instructions,
        const AI_MODELS_EDITS model = AI_MODELS_EDITS::TextDavinciEdit001
    ) {
      auto req = models::get_default_edits_request();
      req.input = input;
      req.instruction = instructions;
      req.model = to_str(model);

      return this->http_client->post<models::EditsRequest, models::EditsResponse *>(
          "/v1/edits",
          req
      );
    }

    // Lists the currently available models,
    // and provides basic information about each one such as the owner and availability.
    // GET /v1/models
    // see: https://platform.openai.com/docs/api-reference/models
    models::ListModelsResponse *list_models() {
      return this->http_client->get<models::ListModelsResponse *>("/v1/models");
    }

    // Retrieves a model instance, providing basic information about the model such as the owner and permissioning.
    // GET /v1/models/{model_id}
    // see: https://platform.openai.com/docs/api-reference/models
    models::Model *get_model(const std::string &model_id) {
      return this->http_client->get<models::Model *>("/v1/models/" + model_id);
    }

    // Delete a fine-tuned model. You must have the Owner role in your organization.
    // DELETE /v1/models/{model_id}
    // see: https://platform.openai.com/docs/api-reference/models
    models::ModelDeleteResponse *delete_model(const std::string &model_id) {
      return this->http_client->delete_<models::ModelDeleteResponse *>("/v1/models/" + model_id);
    }

    // Given a prompt and/or an input image, the model will generate a new image.
    // POST /v1/images/generations
    // see: https://platform.openai.com/docs/api-reference/images
    models::ImagesResponse *get_image(
        const std::string &prompt,
        const IMAGE_SIZE image_size = IMAGE_SIZE::px_1024_1024,
        const int number_of_images = 1,
        const IMAGE_RESPONSE_FORMAT response_format = IMAGE_RESPONSE_FORMAT::url
    ) {
      models::ImagesGenerationsRequest request;
      request.size = to_str(image_size);
      request.n = number_of_images;
      request.prompt = prompt;
      request.response_format = to_str(response_format);

      return this->http_client->post<models::ImagesGenerationsRequest, models::ImagesResponse *>(
          "/v1/images/generations", request
      );
    }

    // Creates an edited or extended image given an original image and a prompt.
    // POST /v1/images/edits
    //
    // The image to edit must be a valid PNG file, less than 4MB, and square.
    //  If mask is not provided, image must have transparency, which will be used as the mask.
    //
    // mask:
    //  An additional image whose fully transparent areas (e.g. where alpha is zero) indicate where image should be edited.
    //    Must be a valid PNG file, less than 4MB, and have the same dimensions as image.
    //
    // prompt: A text description of the desired image(s). The maximum length is 1000 characters.
    // n: The number of images to generate. Must be between 1 and 10.
    // response_format: The format in which the generated images are returned. Must be one of url or b64_json.
    //
    // see: https://platform.openai.com/docs/api-reference/images
    models::ImagesResponse *get_image_edits(
        const std::string &prompt,
        const std::string &image_data,
        const std::string &mask_data = "",
        const IMAGE_SIZE image_size = IMAGE_SIZE::px_1024_1024,
        const int number_of_images = 1,
        const IMAGE_RESPONSE_FORMAT response_format = IMAGE_RESPONSE_FORMAT::url
    ) {
      httplib::MultipartFormDataItems form_data = {
          {"prompt", prompt, "", "text/plain"},
          {"n", std::to_string(number_of_images), "", "text/plain"},
          {"size", to_str(image_size), "", "text/plain"},
          {"response_format", to_str(response_format), "", "text/plain"},
          {"image", image_data, "image.png", "image/png"},
      };

      if (!mask_data.empty()) {
        form_data.push_back({"mask", mask_data});
      }

      return this->http_client->post<models::ImagesResponse *>("/v1/images/edits", form_data);
    }

    // Create a variation of a given image
    // POST /v1/images/variations
    //
    // The image to use as the basis for the variation(s).
    //  Must be a valid PNG file, less than 4MB, and square.
    // see: https://platform.openai.com/docs/api-reference/images
    models::ImagesResponse *get_image_variations(
        const std::string &image_data,
        const IMAGE_SIZE image_size = IMAGE_SIZE::px_1024_1024,
        const int number_of_images = 1,
        const IMAGE_RESPONSE_FORMAT response_format = IMAGE_RESPONSE_FORMAT::url
    ) {
      httplib::MultipartFormDataItems form_data = {
          {"n", std::to_string(number_of_images)},
          {"size", to_str(image_size)},
          {"response_format", to_str(response_format)},
          {"image", image_data},
      };

      return this->http_client->post<models::ImagesResponse *>("/v1/images/variations", form_data);
    }

    // Get a vector representation of a given input that can be easily consumed by machine learning models and algorithms.
    // POST /v1/embeddings
    // see: https://platform.openai.com/docs/api-reference/embeddings
    models::EmbeddingResponse *get_embeddings(
        const std::string &input,
        const std::string &model = "text-embedding-ada-002",
        const std::string &user = ""
    ) {
      models::EmbeddingRequest request;
      request.input = input;
      request.model = model;
      request.user = user;

      return this->http_client->post<models::EmbeddingRequest, models::EmbeddingResponse *>(
          "/v1/embeddings", request
      );
    }

    /// Transcribes audio into the input language.
    /// POST /v1/audio/transcriptions
    //
    /// @param file The audio file to transcribe, in one of these formats: mp3, mp4, mpeg, mpga, m4a, wav, or webm.
    /// @param model ID of the model to use. Only whisper-1 is currently available.
    /// @param response_format The format of the transcript output, in one of these options: json, text, srt, verbose_json, or vtt.
    /// @param prompt An optional text to guide the model's style or continue a previous audio segment. The prompt should match the audio language.
    ///         see: https://platform.openai.com/docs/guides/speech-to-text/prompting
    /// @param temperature The sampling temperature, between 0 and 1. Higher values like 0.8 will make the output more random, while lower values like 0.2 will make it more focused and deterministic. If set to 0, the model will use log probability to automatically increase the temperature until certain thresholds are hit.
    /// @param language The language of the input audio. Supplying the input language in ISO-639-1 format will improve accuracy and latency.
    ///         see: https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
    ///
    /// see: https://platform.openai.com/docs/api-reference/audio
    models::AudioResponse *get_audio_transcription(
        const std::string &audio,
        const std::string &model = "whisper-1",
        const AUDIO_RESPONSE_FORMAT response_format = AUDIO_RESPONSE_FORMAT::json,
        const std::string &prompt = "",
        const int temperature = 0,
        const std::string &language = ""
    ) {
      httplib::MultipartFormDataItems form_data = {
          {"file", audio},
          {"model", model},
          {"response_format", to_str(response_format)},
          {"temperature", std::to_string(temperature)},
      };

      if (!prompt.empty()) {
        form_data.push_back({"prompt", prompt});
      }

      if (!prompt.empty()) {
        form_data.push_back({"language", language});
      }

      return this->http_client->post<models::AudioResponse *>("/v1/audio/transcriptions", form_data);
    }

    /// Translates audio into into English.
    /// POST /v1/audio/translations
    //
    /// @param file The audio file to transcribe, in one of these formats: mp3, mp4, mpeg, mpga, m4a, wav, or webm.
    /// @param model ID of the model to use. Only whisper-1 is currently available.
    /// @param response_format The format of the transcript output, in one of these options: json, text, srt, verbose_json, or vtt.
    /// @param prompt An optional text to guide the model's style or continue a previous audio segment. The prompt should match the audio language.
    ///         see: https://platform.openai.com/docs/guides/speech-to-text/prompting
    /// @param temperature The sampling temperature, between 0 and 1. Higher values like 0.8 will make the output more random, while lower values like 0.2 will make it more focused and deterministic. If set to 0, the model will use log probability to automatically increase the temperature until certain thresholds are hit.
    ///
    /// see: https://platform.openai.com/docs/api-reference/audio
    models::AudioResponse *get_audio_translation(
        const std::string &audio,
        const std::string &model = "whisper-1",
        const AUDIO_RESPONSE_FORMAT response_format = AUDIO_RESPONSE_FORMAT::json,
        const std::string &prompt = "",
        const int temperature = 0,
        const std::string &language = ""
    ) {
      httplib::MultipartFormDataItems form_data = {
          {"file", audio},
          {"model", model},
          {"response_format", to_str(response_format)},
          {"temperature", std::to_string(temperature)},
      };

      if (!prompt.empty()) {
        form_data.push_back({"prompt", prompt});
      }

      if (!prompt.empty()) {
        form_data.push_back({"language", language});
      }

      return this->http_client->post<models::AudioResponse *>("/v1/audio/transcriptions", form_data);
    }

    // Generate a new chat object with the given model
    // Use this object to interact with ChatGPT
    Chat new_chat(AI_MODELS model) {
      return Chat(this->http_client, model);
    }

    // Returns a list of files that belong to the user's organization.
    // GET /v1/files
    // see: https://platform.openai.com/docs/api-reference/files
    models::ListFilesResponse *get_files() {
      return this->http_client->get<models::ListFilesResponse *>("/v1/files");
    }

    /// Upload a file that contains document(s) to be used across various endpoints/features
    /// POST /v1/files
    //
    /// @param file Content of the JSON Lines file to be uploaded.
    ///              If the purpose is set to "fine-tune", each line is a JSON record with
    ///              "prompt" and "completion" fields representing your training examples.
    /// @param file_name The name of the file
    /// @param purpose The intended purpose of the uploaded documents.
    ///                 Use "fine-tune" for Fine-tuning. This allows us to validate the format of the uploaded file.
    ///
    /// see: https://platform.openai.com/docs/api-reference/files/upload
    models::OpenAIFile *upload_file(
        const std::string &file_content,
        const std::string &file_name,
        const std::string &purpose = "fine-tune"
    ) {
      httplib::MultipartFormDataItems form_data = {
          {"file", file_content, file_name},
          {"purpose", purpose},
      };

      return this->http_client->post<models::OpenAIFile *>("/v1/files", form_data);
    }

    // Returns information about a specific file.
    // GET /v1/files/{file_id}
    // see: https://platform.openai.com/docs/api-reference/files
    models::OpenAIFile *get_file(const std::string &file_id) {
      return this->http_client->get<models::OpenAIFile *>("/v1/files/" + file_id);
    }

    // Delete a file
    // DELETE /v1/files/{file_id}
    // see: https://platform.openai.com/docs/api-reference/files
    models::FileDeleteResponse *delete_file(const std::string &file_id) {
      return this->http_client->delete_<models::FileDeleteResponse *>("/v1/files/" + file_id);
    }

    /// Returns the contents of the specified file
    /// GET /v1/files/{file_id}/content
    /// see: https://platform.openai.com/docs/api-reference/files
    std::string get_file_content(const std::string &file_id) {
      return this->http_client->get<std::string>("/v1/files/" + file_id + "/content");
    }

    // List your organization's fine-tuning jobs
    // GET /v1/fine-tunes
    models::ListFineTune *list_fine_tunes() {
      return this->http_client->get<models::ListFineTune *>("/v1/fine-tunes");
    }

    // Gets info about the fine-tune job
    // GET /v1/fine-tunes/{fine_tune_id}
    models::FineTune *get_fine_tune(const std::string &fine_tune_id) {
      return this->http_client->get<models::FineTune *>("/v1/fine-tunes/" + fine_tune_id);
    }

    // Get fine-grained status updates for a fine-tune job
    // GET /v1/fine-tunes/{fine_tune_id}/events
    models::ListFineTuneEvents *get_fine_tune_events(const std::string &fine_tune_id) {
      return this->http_client->get<models::ListFineTuneEvents *>("/v1/fine-tunes/" + fine_tune_id + "/events");
    }

    // Creates a job that fine-tunes a specified model from a given dataset.
    //  Response includes details of the enqueued job including job status and the name of the fine-tuned models once complete.
    // POST /v1/fine-tunes
    // see: https://platform.openai.com/docs/guides/fine-tuning
    models::FineTune *create_fine_tune(const models::FineTuneRequest &fine_tune_request) {
      return this->http_client->post<models::FineTuneRequest, models::FineTune *>(
          "/v1/fine-tunes",
          fine_tune_request
      );
    }

    // Immediately cancel a fine-tune job.
    // POST /v1/fine-tunes/{fine_tune_id}/cancel
    models::FineTune *cancel_fine_tune(const std::string &fine_tune_id) {
      return this->http_client->post<models::FineTune *>("/v1/fine-tunes/" + fine_tune_id + "/cancel");
    }

    // Classifies if text violates OpenAI's Content Policy
    // POST /moderations
    models::ModerationResponse *get_moderations(
        const std::string &input,
        const AI_MODELS_MODERATIONS model = AI_MODELS_MODERATIONS::TextModerationLatest
    ) {
      models::ModerationRequest request;
      request.input = "";
      request.model = to_str(model);
      return this->http_client->post<models::ModerationRequest, models::ModerationResponse *>(
          "/v1/moderations",
          request
      );
    }
  };
}
