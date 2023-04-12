#include "lua_config/lua_parameter_dictionary.h"
#include "lua_config/configuration_file_resolver.h"
#include <memory>

#include "gtest/gtest.h"

const char* PROJECT_DIR = "/home/ysk/src/lua_config";

namespace lua_config {
namespace {

std::unique_ptr<LuaParameterDictionary> MakeDictionary(const std::string &file) {
  std::vector<std::string> dirs = {std::string(PROJECT_DIR) + "/data"};
  std::unique_ptr<FileResolver> file_resolver =
      std::make_unique<ConfigurationFileResolver>(dirs);

  std::string code = file_resolver->GetFileContentOrDie(file);
  return LuaParameterDictionary::NonReferenceCounted(
      code, std::move(file_resolver));
}

TEST(LuaParameterDictionaryTest, GetSimple) {
  auto dict = MakeDictionary("conf1.lua");
  ASSERT_EQ(dict->GetInt("hour"), 10);
  ASSERT_EQ(dict->GetString("name"), std::string("tom"));
  ASSERT_EQ(dict->GetInt("min"), 20);
  ASSERT_DOUBLE_EQ(dict->GetDouble("score"), 99.9);
}

TEST(LuaParameterDictionaryTest, Include) {
  auto dict = MakeDictionary("conf2.lua");
  ASSERT_EQ(dict->GetInt("hour"), 70);
  ASSERT_EQ(dict->GetDictionary("spec")->GetInt("time"), 10);
}

}
}