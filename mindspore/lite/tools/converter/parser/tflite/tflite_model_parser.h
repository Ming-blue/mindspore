/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_CCSRC_TOOLS_LITE_CONVERTER_PARSER_TFLITE_MODEL_PARSER_H
#define MINDSPORE_CCSRC_TOOLS_LITE_CONVERTER_PARSER_TFLITE_MODEL_PARSER_H

#include <fcntl.h>
#include <unistd.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "securec/include/securec.h"
#include "tools/converter/model_parser.h"
#include "tools/converter/parser/tflite/tflite_node_parser_registry.h"
#include "tools/common/tensor_util.h"

#include "mindspore/lite/schema/inner/model_generated.h"

// using namespace tflite;

namespace mindspore {
namespace lite {
class TfliteModelParser : public ModelParser {
 public:
  TfliteModelParser();

  virtual ~TfliteModelParser();

  MetaGraphT *Parse(const std::string &modelFile, const std::string &weightFile);

 private:
  std::unique_ptr<tflite::ModelT> ReadTfliteModelFromFlat(const char *buf);

  void SetInputTensor(const std::unique_ptr<tflite::ModelT> &tflite_model,
                      const std::unique_ptr<tflite::SubGraphT> &tflite_subgraph, TensorCache *tensor_cache);

  void SetGraphTensorIndex(const mindspore::lite::TensorCache &tensorCache,
                           schema::MetaGraphT *subGraphDef);

  STATUS ParseOp(const std::unique_ptr<tflite::ModelT> &tflite_model,
                 const std::unique_ptr<tflite::SubGraphT> &tflite_subgraph, schema::MetaGraphT *sub_graph,
                 TensorCache *tensor_cache);

  STATUS ParseTfliteQuantParams(const std::unique_ptr<tflite::SubGraphT> &tflite_subgraph,
                                const std::unique_ptr<tflite::OperatorT> &tflite_op);

  std::string GetTfliteNodeType(const std::unique_ptr<tflite::OperatorT> &tflite_op,
                                const std::unique_ptr<tflite::ModelT> &tflite_model);

  STATUS SetAllTensors(const TensorCache &tensor_cache, schema::MetaGraphT *sub_graph);

  STATUS SetOpOutputIdx(const std::unique_ptr<tflite::SubGraphT> &tflite_subgraph,
                        const std::unique_ptr<tflite::OperatorT> &tflite_op,
                        schema::CNodeT *op,
                        TensorCache *tensorCache);

  STATUS SetOpInputIdx(const std::unique_ptr<tflite::ModelT> &tflite_model,
                       const std::unique_ptr<tflite::SubGraphT> &tflite_subgraph,
                       const std::unique_ptr<tflite::OperatorT> &tflite_op, TensorCache *tensorCache);

  std::map<std::string, schema::CNodeT *> opMap;
  std::map<const tflite::OperatorT *, schema::CNodeT *> tfliteOpMap;
};
}  // namespace lite
}  // namespace mindspore
#endif  // PREDICT_CONV
// ERTER_PARSER_TFLITE_MODEL_PARSER_H

