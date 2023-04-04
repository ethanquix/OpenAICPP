// Code auto generated from json file 'assets/json/get_files.json'

#pragma once

#include <tuple>
#include <cstdint>
#include <string>
#include <vector>
#include <daw/json/daw_json_link.h>

namespace openai {
  namespace models {
    struct OpenAIFile {
      std::string id;
      std::string object;
      int64_t bytes;
      int64_t created_at;
      std::string filename;
      std::string purpose;
      std::string status;
    };

    struct ListFilesResponse {
      std::string object;
      std::vector<OpenAIFile> data;
    };

    struct FileDeleteResponse {
      std::string id;
      std::string object;
      bool deleted;
    };
  }
}

namespace daw::json {
  template<>
  struct json_data_contract<openai::models::OpenAIFile> {
    static constexpr char const mem_id[] = "id";
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_bytes[] = "bytes";
    static constexpr char const mem_created_at[] = "created_at";
    static constexpr char const mem_filename[] = "filename";
    static constexpr char const mem_purpose[] = "purpose";
    static constexpr char const mem_status[] = "status";
    using type = json_member_list<
        json_string<mem_id>,
        json_string<mem_object>,
        json_number<mem_bytes, int64_t>,
        json_number<mem_created_at, int64_t>,
        json_string<mem_filename>,
        json_string<mem_purpose>,
        json_string<mem_status>
    >;

    static inline auto to_json_data(openai::models::OpenAIFile const &value) {
      return std::forward_as_tuple(value.id,
                                   value.object,
                                   value.bytes,
                                   value.created_at,
                                   value.filename,
                                   value.purpose,
                                   value.status
      );
    }
  };

  template<>
  struct json_data_contract<openai::models::ListFilesResponse> {
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_data[] = "data";
    using type = json_member_list<
        json_string<mem_object>,
        json_array<mem_data, json_class_no_name<openai::models::OpenAIFile>, std::vector<openai::models::OpenAIFile>>
    >;

    static inline auto to_json_data(openai::models::ListFilesResponse const &value) {
      return std::forward_as_tuple(value.object, value.data);
    }
  };

  template<>
  struct json_data_contract<openai::models::FileDeleteResponse> {
    static constexpr char const mem_id[] = "id";
    static constexpr char const mem_object[] = "object";
    static constexpr char const mem_deleted[] = "deleted";
    using type = json_member_list<
        json_string<mem_id>, json_string<mem_object>, json_bool<mem_deleted>
    >;

    static inline auto to_json_data(openai::models::FileDeleteResponse const &value) {
      return std::forward_as_tuple(value.id, value.object, value.deleted);
    }
  };
}
