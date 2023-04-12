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

#ifndef LUA_CONFIG__CONFIGURATION_FILE_RESOLVER_H_
#define LUA_CONFIG__CONFIGURATION_FILE_RESOLVER_H_

#include <vector>

#include "lua_config/lua_parameter_dictionary.h"

namespace lua_config {

// A 'FileResolver' reads files from disk.
// It searches the 'configuration_files_directories' in order to find the
// requested filename.
class ConfigurationFileResolver : public FileResolver {
 public:
  explicit ConfigurationFileResolver(
      const std::vector<std::string>& configuration_files_directories);

  std::string GetFullPathOrDie(const std::string& basename) override;
  std::string GetFileContentOrDie(const std::string& basename) override;

 private:
  std::vector<std::string> configuration_files_directories_;
};

}  // namespace lua_config

#endif  // LUA_CONFIG__CONFIGURATION_FILE_RESOLVER_H_
