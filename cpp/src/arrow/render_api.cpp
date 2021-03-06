/*
 * Copyright (C) 2019-2020 Zilliz. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "render/render_builder.h"

#include "arrow/render_api.h"

namespace zilliz {
namespace render {

std::shared_ptr<arrow::Array> out_pic(std::pair<uint8_t*, int64_t> output) {
  auto output_length = output.second;
  auto output_data = output.first;
  auto bit_map = (uint8_t*)malloc(output_length);
  memset(bit_map, 0xff, output_length);

  auto buffer0 = std::make_shared<arrow::Buffer>(bit_map, output_length);
  auto buffer1 = std::make_shared<arrow::Buffer>(output_data, output_length);
  auto buffers = std::vector<std::shared_ptr<arrow::Buffer>>();
  buffers.emplace_back(buffer0);
  buffers.emplace_back(buffer1);

  auto data_type = arrow::uint8();
  auto array_data = arrow::ArrayData::Make(data_type, output_length, buffers);
  auto array = arrow::MakeArray(array_data);
  return array;
}

std::shared_ptr<arrow::Array> point_map(const std::shared_ptr<arrow::Array>& arr_x,
                                        const std::shared_ptr<arrow::Array>& arr_y,
                                        const std::string& conf) {
  auto x_length = arr_x->length();
  auto y_length = arr_y->length();

  auto x_type = arr_x->type_id();
  auto y_type = arr_y->type_id();

  assert(x_length == y_length);
  assert(x_type == arrow::Type::UINT32);
  assert(y_type == arrow::Type::UINT32);

  auto input_x = (uint32_t*)arr_x->data()->GetValues<uint8_t>(1);
  auto input_y = (uint32_t*)arr_y->data()->GetValues<uint8_t>(1);

  return out_pic(pointmap(input_x, input_y, x_length, conf));
}

std::shared_ptr<arrow::Array> heat_map(const std::shared_ptr<arrow::Array>& arr_x,
                                       const std::shared_ptr<arrow::Array>& arr_y,
                                       const std::shared_ptr<arrow::Array>& arr_c,
                                       const std::string& conf) {
  auto x_length = arr_x->length();
  auto y_length = arr_y->length();
  auto c_length = arr_c->length();

  auto x_type = arr_x->type_id();
  auto y_type = arr_y->type_id();
  auto c_type = arr_c->type_id();

  assert(x_length == y_length);
  assert(x_length == c_length);
  assert(x_type == arrow::Type::UINT32);
  assert(y_type == arrow::Type::UINT32);

  auto input_x = (uint32_t*)arr_x->data()->GetValues<uint8_t>(1);
  auto input_y = (uint32_t*)arr_y->data()->GetValues<uint8_t>(1);

  std::pair<uint8_t*, int64_t> output;
  switch (c_type) {
    case arrow::Type::INT8: {
      auto input_c_int8 = (int8_t*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<int8_t>(input_x, input_y, input_c_int8, x_length, conf));
    }
    case arrow::Type::INT16: {
      auto input_c_int16 = (int16_t*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<int16_t>(input_x, input_y, input_c_int16, x_length, conf));
    }
    case arrow::Type::INT32: {
      auto input_c_int32 = (int32_t*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<int32_t>(input_x, input_y, input_c_int32, x_length, conf));
    }
    case arrow::Type::INT64: {
      auto input_c_int64 = (int64_t*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(
          output = heatmap<int64_t>(input_x, input_y, input_c_int64, x_length, conf));
    }
    case arrow::Type::UINT8: {
      auto input_c_uint8 = (uint8_t*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<uint8_t>(input_x, input_y, input_c_uint8, x_length, conf));
    }
    case arrow::Type::UINT16: {
      auto input_c_uint16 = (uint16_t*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<uint16_t>(input_x, input_y, input_c_uint16, x_length, conf));
    }
    case arrow::Type::UINT32: {
      auto input_c_uint32 = (uint32_t*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<uint32_t>(input_x, input_y, input_c_uint32, x_length, conf));
    }
    case arrow::Type::UINT64: {
      auto input_c_uint64 = (uint64_t*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<uint64_t>(input_x, input_y, input_c_uint64, x_length, conf));
    }
    case arrow::Type::FLOAT: {
      auto input_c_float = (float*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<float>(input_x, input_y, input_c_float, x_length, conf));
    }
    case arrow::Type::DOUBLE: {
      auto input_c_double = (double*)arr_c->data()->GetValues<uint8_t>(1);
      return out_pic(heatmap<double>(input_x, input_y, input_c_double, x_length, conf));
    }
    default:
      // TODO: add log here
      std::cout << "type error!";
  }
  return nullptr;
}

std::shared_ptr<arrow::Array> choropleth_map(
    const std::shared_ptr<arrow::Array>& arr_wkt,
    const std::shared_ptr<arrow::Array>& arr_count, const std::string& conf) {
  auto arr_wkt_length = arr_wkt->length();
  auto arr_color_length = arr_count->length();
  auto wkt_type = arr_wkt->type_id();
  auto color_type = arr_count->type_id();

  assert(arr_wkt_length == arr_color_length);
  assert(wkt_type == arrow::Type::STRING);

  auto string_array = std::static_pointer_cast<arrow::StringArray>(arr_wkt);
  std::vector<std::string> input_wkt(arr_wkt_length);
  for (int i = 0; i < arr_wkt_length; i++) {
    input_wkt[i] = string_array->GetString(i);
  }

  switch (color_type) {
    case arrow::Type::INT8: {
      auto input_c_int8 = (int8_t*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<int8_t>(input_wkt, input_c_int8, arr_wkt_length, conf));
    }
    case arrow::Type::INT16: {
      auto input_c_int16 = (int16_t*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<int16_t>(input_wkt, input_c_int16, arr_wkt_length, conf));
    }
    case arrow::Type::INT32: {
      auto input_c_int32 = (int32_t*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<int32_t>(input_wkt, input_c_int32, arr_wkt_length, conf));
    }
    case arrow::Type::INT64: {
      auto input_c_int64 = (int64_t*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<int64_t>(input_wkt, input_c_int64, arr_wkt_length, conf));
    }
    case arrow::Type::UINT8: {
      auto input_c_uint8 = (uint8_t*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<uint8_t>(input_wkt, input_c_uint8, arr_wkt_length, conf));
    }
    case arrow::Type::UINT16: {
      auto input_c_uint16 = (uint16_t*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<uint16_t>(input_wkt, input_c_uint16, arr_wkt_length, conf));
    }
    case arrow::Type::UINT32: {
      auto input_c_uint32 = (uint32_t*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<uint32_t>(input_wkt, input_c_uint32, arr_wkt_length, conf));
    }
    case arrow::Type::UINT64: {
      auto input_c_uint64 = (uint64_t*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<uint64_t>(input_wkt, input_c_uint64, arr_wkt_length, conf));
    }
    case arrow::Type::FLOAT: {
      auto input_c_float = (float*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<float>(input_wkt, input_c_float, arr_wkt_length, conf));
    }
    case arrow::Type::DOUBLE: {
      auto input_c_double = (double*)arr_count->data()->GetValues<uint8_t>(1);
      return out_pic(
          choroplethmap<double>(input_wkt, input_c_double, arr_wkt_length, conf));
    }
    default:
      // TODO: add log here
      std::cout << "type error!";
  }
  return nullptr;
}

}  // namespace render
}  // namespace zilliz
