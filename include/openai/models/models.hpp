// Code auto generated from json file 'assets/json/models.json'

#pragma once

#include <tuple>
#include <cstdint>
#include <string>
#include <vector>
#include <daw/json/daw_json_link.h>

namespace openai {
  namespace models {
    struct Model {
      std::string id; // davinci, gpt-3.5-turbo, ...
      std::string object; // 'model'
      int64_t created;
      std::string owned_by;
    };

    struct ListModelsResponse {
      std::string object;
      std::vector<Model> data;
    };

    struct ModelDeleteResponse {
      std::string id;
      std::string object;
      bool deleted;
    };
  }
}

namespace daw::json {
  template<>
  struct json_data_contract<openai::models::Model> {
    static constexpr char const mem_id[] = "id";
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_created[] = "created";
    static constexpr char const mem_owned_by[] = "owned_by";
    using type = json_member_list<
        json_string<mem_id>, json_string<mem_object>, json_number<mem_created, int64_t>, json_string<mem_owned_by>
    >;

    static inline auto to_json_data(openai::models::Model const &value) {
      return std::forward_as_tuple(value.id, value.object, value.created, value.owned_by);
    }
  };

  template<>
  struct json_data_contract<openai::models::ListModelsResponse> {
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_data[] = "data";
    using type = json_member_list<
        json_string<mem_object>,
        json_array<mem_data, json_class_no_name<openai::models::Model>, std::vector<openai::models::Model>>
    >;

    static inline auto to_json_data(openai::models::ListModelsResponse const &value) {
      return std::forward_as_tuple(value.object, value.data);
    }
  };

  template<>
  struct json_data_contract<openai::models::ModelDeleteResponse> {
    static constexpr char const mem_id[] = "id";
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_deleted[] = "deleted";
    using type = json_member_list<
        json_string<mem_id>, json_string<mem_object>, json_bool<mem_deleted>
    >;

    static inline auto to_json_data(openai::models::ModelDeleteResponse const &value) {
      return std::forward_as_tuple(value.id, value.object, value.deleted);
    }
  };
}
