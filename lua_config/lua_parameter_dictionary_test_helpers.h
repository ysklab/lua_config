/*
 * Copyright 2016 The Lua-Config Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef LUA_CONFIG_LUA_CONFIG_LUA_PARAMETER_DICTIONARY_TEST_HELPERS_H_
#define LUA_CONFIG_LUA_CONFIG_LUA_PARAMETER_DICTIONARY_TEST_HELPERS_H_

#include <memory>
#include <string>

#include "lua_config/lua_parameter_dictionary.h"

#include "glog/logging.h"

namespace lua_config {

class DummyFileResolver : public FileResolver {
 public:
  DummyFileResolver() {}

  DummyFileResolver(const DummyFileResolver&) = delete;
  DummyFileResolver& operator=(const DummyFileResolver&) = delete;

  ~DummyFileResolver() override {}

  std::string GetFileContentOrDie(const std::string& unused_basename) override {
    LOG(FATAL) << "Not implemented";
  }

  std::string GetFullPathOrDie(const std::string& unused_basename) override {
    LOG(FATAL) << "Not implemented";
  }
};

std::unique_ptr<LuaParameterDictionary> MakeDictionary(
    const std::string& code) {
  return std::make_unique<LuaParameterDictionary>(
      code, std::make_unique<DummyFileResolver>());
}

}  // namespace cartographer

#endif //LUA_CONFIG_LUA_CONFIG_LUA_PARAMETER_DICTIONARY_TEST_HELPERS_H_
