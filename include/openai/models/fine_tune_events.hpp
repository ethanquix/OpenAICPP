// Code auto generated from json file 'assets/json/fine_tune_events.json'

#pragma once

#include <tuple>
#include <cstdint>
#include <string>
#include <vector>
#include <daw/json/daw_json_link.h>


namespace daw::json {
	template<>
	struct json_data_contract<data_element_t> {
		static constexpr char const mem_object[] = "object";
		static constexpr char const mem_created_at[] = "created_at";
		static constexpr char const mem_level[] = "level";
		static constexpr char const mem_message[] = "message";
		 using type = json_member_list<
				json_string<mem_object>
				,json_number<mem_created_at, int64_t>
				,json_string<mem_level>
				,json_string<mem_message>
	>;

		static inline auto to_json_data( data_element_t const & value ) {
			return std::forward_as_tuple( value.object, value.created_at, value.level, value.message );
}
	};
}
namespace daw::json {
	template<>
	struct json_data_contract<ListFineTuneEvents> {
		static constexpr char const mem_object[] = "object";
		static constexpr char const mem_data[] = "data";
		 using type = json_member_list<
				json_string<mem_object>
				,json_array<mem_data, json_class_no_name<data_element_t>, std::vector<data_element_t>>
	>;

		static inline auto to_json_data( ListFineTuneEvents const & value ) {
			return std::forward_as_tuple( value.object, value.data );
}
	};
}
