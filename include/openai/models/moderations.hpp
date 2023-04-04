#pragma once

#include <tuple>
#include <string>
#include <daw/json/daw_json_link.h>

namespace openai::models {
  // Request

  struct ModerationRequest {
    // The input text to classify
    std::string input;
    // Two content moderations models are available:
    //  text-moderation-stable and text-moderation-latest.
    //
    // The default is text-moderation-latest which will be automatically upgraded over time.
    // This ensures you are always using our most accurate model.
    // If you use text-moderation-stable, we will provide advanced notice before updating the model.
    // Accuracy of text-moderation-stable may be slightly lower than for text-moderation-latest.
    std::string model;
  };

  // Response

  struct ModerationResponseCategories {
    bool hate;
    bool hate_threatening;
    bool self_harm;
    bool sexual;
    bool sexual_minors;
    bool violence;
    bool violence_graphic;
  };

  struct ModerationResponseCategoryScores {
    float hate;
    float hate_threatening;
    float self_harm;
    float sexual;
    float sexual_minors;
    float violence;
    float violence_graphic;
  };

  struct ModerationResponseResult {
    bool flagged;
    ModerationResponseCategories categories;
    ModerationResponseCategoryScores category_scores;
  };

  struct ModerationResponse {
    std::string id;
    std::string model;
    std::vector<ModerationResponseResult> results;
  };
}

// JSON defs
namespace daw::json {
  template<>
  struct json_data_contract<openai::models::ModerationRequest> {
    static constexpr char const mem_input[] = "input";
    static constexpr char const mem_model[] = "model";
    using type = json_member_list<
        json_string<mem_input>, json_string<mem_model>
    >;

    static inline auto to_json_data(openai::models::ModerationRequest const &value) {
      return std::forward_as_tuple(value.input, value.model);
    }
  };

  template<>
  struct json_data_contract<openai::models::ModerationResponseCategories> {
    static constexpr char const mem_hate[] = "hate";
    static constexpr char const mem_hate_threatening[] = "hate/threatening";
    static constexpr char const mem_self_harm[] = "self-harm";
    static constexpr char const mem_sexual[] = "sexual";
    static constexpr char const mem_sexual_minors[] = "sexual/minors";
    static constexpr char const mem_violence[] = "violence";
    static constexpr char const mem_violence_graphic[] = "violence/graphic";
    using type = json_member_list<
        json_bool<mem_hate>,
        json_bool<mem_hate_threatening>,
        json_bool<mem_self_harm>,
        json_bool<mem_sexual>,
        json_bool<mem_sexual_minors>,
        json_bool<mem_violence>,
        json_bool<mem_violence_graphic>
    >;

    static inline auto to_json_data(openai::models::ModerationResponseCategories const &value) {
      return std::forward_as_tuple(value.hate,
                                   value.hate_threatening,
                                   value.self_harm,
                                   value.sexual,
                                   value.sexual_minors,
                                   value.violence,
                                   value.violence_graphic);
    }
  };

  template<>
  struct json_data_contract<openai::models::ModerationResponseCategoryScores> {
    static constexpr char const mem_hate[] = "hate";
    static constexpr char const mem_hate_threatening[] = "hate/threatening";
    static constexpr char const mem_self_harm[] = "self-harm";
    static constexpr char const mem_sexual[] = "sexual";
    static constexpr char const mem_sexual_minors[] = "sexual/minors";
    static constexpr char const mem_violence[] = "violence";
    static constexpr char const mem_violence_graphic[] = "violence/graphic";
    using type = json_member_list<
        json_number<mem_hate, float>,
        json_number<mem_hate_threatening, float>,
        json_number<mem_self_harm, float>,
        json_number<mem_sexual, float>,
        json_number<mem_sexual_minors, float>,
        json_number<mem_violence, float>,
        json_number<mem_violence_graphic, float>
    >;

    static inline auto to_json_data(openai::models::ModerationResponseCategoryScores const &value) {
      return std::forward_as_tuple(value.hate,
                                   value.hate_threatening,
                                   value.self_harm,
                                   value.sexual,
                                   value.sexual_minors,
                                   value.violence,
                                   value.violence_graphic);
    }
  };

  template<>
  struct json_data_contract<openai::models::ModerationResponseResult> {
    static constexpr char const mem_flagged[] = "flagged";
    static constexpr char const mem_categories[] = "categories";
    static constexpr char const mem_category_scores[] = "category_scores";
    using type = json_member_list<
        json_bool<mem_flagged>,
        json_class<mem_categories, openai::models::ModerationResponseCategories>,
        json_class<mem_category_scores, openai::models::ModerationResponseCategoryScores>
    >;

    static inline auto to_json_data(openai::models::ModerationResponseResult const &value) {
      return std::forward_as_tuple(value.flagged, value.categories, value.category_scores);
    }
  };

  template<>
  struct json_data_contract<openai::models::ModerationResponse> {
    static constexpr char const mem_id[] = "id";
    static constexpr char const mem_model[] = "model";
    static constexpr char const mem_results[] = "results";
    using type = json_member_list<
        json_string<mem_id>,
        json_string<mem_model>,
        json_array<mem_results,
                   json_class_no_name<openai::models::ModerationResponseResult>,
                   std::vector<openai::models::ModerationResponseResult>>
    >;

    static inline auto to_json_data(openai::models::ModerationResponse const &value) {
      return std::forward_as_tuple(value.id, value.model, value.results);
    }
  };
}
