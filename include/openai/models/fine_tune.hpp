// Code auto generated from json file 'assets/json/fine_tune.json'

#pragma once

#include <tuple>
#include <cstdint>
#include <string>
#include <vector>
#include <daw/json/daw_json_link.h>
#include "files.hpp"

namespace openai::models {
  struct HyperParams {
  };

  struct FineTuneStatusDetails {
  };

  struct FineTuneEvent {
    std::string object;
    int64_t created_at;
    std::string level;
    std::string message;
  };

  struct FineTune {
    std::string id;
    std::string object;
    int64_t created_at;
    int64_t updated_at;
    std::string model;
    std::string fine_tuned_model;
    std::string organization_id;
    std::string status;
    HyperParams hyperparams;
    std::vector<openai::models::OpenAIFile> training_files;
    std::vector<openai::models::OpenAIFile> validation_files;
    std::vector<openai::models::OpenAIFile> result_files;
    std::vector<FineTuneEvent> events;
  };

  struct ListFineTune {
    std::string object;
    std::vector<FineTune> data;
  };

  struct FineTuneRequest {
    // The ID of an uploaded file that contains training data.
    // See upload file for how to upload a file.
    // Your dataset must be formatted as a JSONL file, where each training example is a JSON object with the keys "prompt" and "completion". Additionally, you must upload your file with the purpose fine-tune.
    // See the fine-tuning guide for more details.
    std::string training_file;
    // The ID of an uploaded file that contains validation data.
    // If you provide this file, the data is used to generate validation metrics periodically during fine-tuning.
    // These metrics can be viewed in the fine-tuning results file. Your train and validation data should be mutually exclusive.
    // Your dataset must be formatted as a JSONL file, where each validation example is a JSON object with the keys "prompt" and "completion".
    // Additionally, you must upload your file with the purpose fine-tune.
    // See the fine-tuning guide for more details.
    std::string validation_file;
    // The name of the base model to fine-tune.
    // You can select one of "ada", "babbage", "curie", "davinci", or a fine-tuned model created after 2022-04-21.
    // To learn more about these models, see the Models documentation.
    std::string model;
    // The number of epochs to train the model for. An epoch refers to one full cycle through the training dataset.
    // default: 4
    int64_t n_epochs;
    // The batch size to use for training.
    // The batch size is the number of training examples used to train a single forward and backward pass.
    // By default, the batch size will be dynamically configured to be ~0.2% of the number of examples in the training set, capped at 256
    //  - in general, we've found that larger batch sizes tend to work better for larger datasets.
    int batch_size;
    // The learning rate multiplier to use for training.
    // The fine-tuning learning rate is the original learning rate used for pretraining multiplied by this value.
    // By default, the learning rate multiplier is the 0.05, 0.1, or 0.2 depending on final batch_size (larger learning rates tend to perform better with larger batch sizes).
    // We recommend experimenting with values in the range 0.02 to 0.2 to see what produces the best results.
    float learning_rate_multiplier;
    // The weight to use for loss on the prompt tokens.
    // This controls how much the model tries to learn to generate the prompt
    //  (as compared to the completion which always has a weight of 1.0), and can add a stabilizing effect to training when completions are short.
    // If prompts are extremely long (relative to completions),
    //  it may make sense to reduce this weight so as to avoid over-prioritizing learning the prompt.
    // default: 0.01
    double prompt_loss_weight;
    // If set, we calculate classification-specific metrics such as accuracy and F-1 score using the validation set at the end of every epoch.
    // These metrics can be viewed in the results file.
    // In order to compute classification metrics, you must provide a validation_file.
    // Additionally, you must specify classification_n_classes for multiclass classification or classification_positive_class for binary classification.
    bool compute_classification_metrics;
    // The number of classes in a classification task.
    // This parameter is required for multiclass classification.
    int classification_n_classes;
    // The number of classes in a classification task.
    // This parameter is required for multiclass classification.
    std::optional<std::string> classification_positive_class;
    // The positive class in binary classification.
    // This parameter is needed to generate precision, recall, and F1 metrics when doing binary classification.
    std::vector<int64_t> classification_betas;
    // A string of up to 40 characters that will be added to your fine-tuned model name.
    // For example, a suffix of "custom-model-name" would produce a model name like
    //  ada:ft-your-org:custom-model-name-2022-02-15-04-21-04.
    std::optional<std::string> suffix;
  };

  struct ListFineTuneEvents {
    std::string object;
    std::vector<FineTuneEvent> data;
  };
}

namespace daw::json {
  template<>
  struct json_data_contract<openai::models::HyperParams> {
    using type = json_member_list<
    >;

    static inline auto to_json_data(openai::models::HyperParams const &value) {
      return std::forward_as_tuple();
    }
  };
}
namespace daw::json {
  template<>
  struct json_data_contract<openai::models::FineTuneStatusDetails> {
    using type = json_member_list<
    >;

    static inline auto to_json_data(openai::models::FineTuneStatusDetails const &value) {
      return std::forward_as_tuple();
    }
  };
}

namespace daw::json {
  template<>
  struct json_data_contract<openai::models::FineTuneEvent> {
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_created_at[] = "created_at";
    static constexpr char const mem_level[] = "level";
    static constexpr char const mem_message[] = "message";
    using type = json_member_list<
        json_string<mem_object>, json_number<mem_created_at, int64_t>, json_string<mem_level>, json_string<mem_message>
    >;

    static inline auto to_json_data(openai::models::FineTuneEvent const &value) {
      return std::forward_as_tuple(value.object, value.created_at, value.level, value.message);
    }
  };

  template<>
  struct json_data_contract<openai::models::FineTune> {
    static constexpr char const mem_id[] = "id";
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_created_at[] = "created_at";
    static constexpr char const mem_updated_at[] = "updated_at";
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_fine_tuned_model[] = "fine_tuned_model";
    static constexpr char const mem_organization_id[] = "organization_id";
    static constexpr char const mem_status[] = "status";
    static constexpr char const mem_hyperparams[] = "hyperparams";
    static constexpr char const mem_training_files[] = "training_files";
    static constexpr char const mem_validation_files[] = "validation_files";
    static constexpr char const mem_result_files[] = "result_files";
    static constexpr char const mem_events[] = "events";
    using type = json_member_list<
        json_string<mem_id>,
        json_string<mem_object>,
        json_number<mem_created_at, int64_t>,
        json_number<mem_updated_at, int64_t>,
        json_string<mem_model>,
        json_string<mem_fine_tuned_model>,
        json_string<mem_organization_id>,
        json_string<mem_status>,
        json_class<mem_hyperparams, openai::models::HyperParams>,
        json_array<mem_training_files,
                   json_class_no_name<openai::models::OpenAIFile>,
                   std::vector<openai::models::OpenAIFile>>,
        json_array<mem_validation_files,
                   json_class_no_name<openai::models::OpenAIFile>,
                   std::vector<openai::models::OpenAIFile>>,
        json_array<mem_result_files,
                   json_class_no_name<openai::models::OpenAIFile>,
                   std::vector<openai::models::OpenAIFile>>,
        json_array<mem_events,
                   json_class_no_name<openai::models::FineTuneEvent>,
                   std::vector<openai::models::FineTuneEvent>>
    >;

    static inline auto to_json_data(openai::models::FineTune const &value) {
      return std::forward_as_tuple(value.id,
                                   value.object,
                                   value.created_at,
                                   value.updated_at,
                                   value.model,
                                   value.fine_tuned_model,
                                   value.organization_id,
                                   value.status,
                                   value.hyperparams,
                                   value.training_files,
                                   value.validation_files,
                                   value.result_files,
                                   value.events);
    }
  };
  template<>
  struct json_data_contract<openai::models::ListFineTune> {
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_data[] = "data";
    using type = json_member_list<
        json_string<mem_object>,
        json_array<mem_data,
                   json_class_no_name<openai::models::FineTune>,
                   std::vector<openai::models::FineTune>>
    >;

    static inline auto to_json_data(openai::models::ListFineTune const &value) {
      return std::forward_as_tuple(value.object, value.data);
    }
  };

  // Request
  template<>
  struct json_data_contract<openai::models::FineTuneRequest> {
    static constexpr char const mem_training_file[] = "training_file";
    static constexpr char const mem_validation_file[] = "validation_file";
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_n_epochs[] = "n_epochs";
    static constexpr char const mem_batch_size[] = "batch_size";
    static constexpr char const mem_learning_rate_multiplier[] = "learning_rate_multiplier";
    static constexpr char const mem_prompt_loss_weight[] = "prompt_loss_weight";
    static constexpr char const mem_compute_classification_metrics[] = "compute_classification_metrics";
    static constexpr char const mem_classification_n_classes[] = "classification_n_classes";
    static constexpr char const mem_classification_positive_class[] = "classification_positive_class";
    static constexpr char const mem_classification_betas[] = "classification_betas";
    static constexpr char const mem_suffix[] = "suffix";
    using type = json_member_list<
        json_string<mem_training_file>,
        json_string<mem_validation_file>,
        json_string<mem_model>,
        json_number<mem_n_epochs, int64_t>,
        json_number<mem_batch_size, int>,
        json_number<mem_learning_rate_multiplier, float>,
        json_number<mem_prompt_loss_weight, double>,
        json_bool<mem_compute_classification_metrics>,
        json_number<mem_classification_n_classes, int>,
        json_string_null<mem_classification_positive_class>,
        json_array<mem_classification_betas, int64_t, std::vector<int64_t>>,
        json_string_null<mem_suffix>
    >;

    static inline auto to_json_data(openai::models::FineTuneRequest const &value) {
      return std::forward_as_tuple(value.training_file,
                                   value.validation_file,
                                   value.model,
                                   value.n_epochs,
                                   value.batch_size,
                                   value.learning_rate_multiplier,
                                   value.prompt_loss_weight,
                                   value.compute_classification_metrics,
                                   value.classification_n_classes,
                                   value.classification_positive_class,
                                   value.classification_betas,
                                   value.suffix);
    }
  };

  template<>
  struct json_data_contract<openai::models::ListFineTuneEvents> {
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_data[] = "data";
    using type = json_member_list<
        json_string<mem_object>,
        json_array<mem_data,
                   json_class_no_name<openai::models::FineTuneEvent>,
                   std::vector<openai::models::FineTuneEvent>>
    >;

    static inline auto to_json_data(openai::models::ListFineTuneEvents const &value) {
      return std::forward_as_tuple(value.object, value.data);
    }
  };
}
