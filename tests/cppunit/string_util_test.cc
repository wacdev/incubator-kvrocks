/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#include "string_util.h"

#include <gtest/gtest.h>

#include <map>

TEST(StringUtil, ToLower) {
  std::map<std::string, std::string> cases{
      {"ABC", "abc"},
      {"AbC", "abc"},
      {"abc", "abc"},
  };
  for (auto iter = cases.begin(); iter != cases.end(); iter++) {
    std::string input = iter->first;
    input = util::ToLower(input);
    ASSERT_EQ(input, iter->second);
  }
}

TEST(StringUtil, Trim) {
  std::map<std::string, std::string> cases{
      {"abc", "abc"},         {"   abc    ", "abc"}, {"\t\tabc\t\t", "abc"},  {"\t\tabc\n\n", "abc"},
      {"\n\nabc\n\n", "abc"}, {" a b", "a b"},       {"a \tb\t \n", "a \tb"},
  };
  for (auto iter = cases.begin(); iter != cases.end(); iter++) {
    std::string input = iter->first;
    std::string output = util::Trim(input, " \t\n");
    ASSERT_EQ(output, iter->second);
  }
}

TEST(StringUtil, Split) {
  std::vector<std::string> expected = {"a", "b", "c", "d"};
  std::vector<std::string> array = util::Split("a,b,c,d", ",");
  ASSERT_EQ(expected, array);
  array = util::Split("a,b,,c,d,", ",");
  ASSERT_EQ(expected, array);
  array = util::Split(",a,b,c,d,", ",");
  ASSERT_EQ(expected, array);
  array = util::Split("a     b  c  d   ", " ");
  ASSERT_EQ(expected, array);
  array = util::Split("a\tb\nc\t\nd   ", " \t\n");
  ASSERT_EQ(expected, array);

  ASSERT_EQ(util::Split("a", " "), std::vector<std::string>{"a"});
  ASSERT_EQ(util::Split("a bc", " "), (std::vector<std::string>{"a", "bc"}));
  ASSERT_EQ(util::Split("a  b c def gh ", " "), (std::vector<std::string>{"a", "b", "c", "def", "gh"}));
  ASSERT_EQ(util::Split("  hello;hi,,; one ;;; two,, ", " ,;"),
            (std::vector<std::string>{"hello", "hi", "one", "two"}));
}

TEST(StringUtil, TokenizeRedisProtocol) {
  std::vector<std::string> expected = {"this", "is", "a", "test"};
  auto array = util::TokenizeRedisProtocol("*4\r\n$4\r\nthis\r\n$2\r\nis\r\n$1\r\na\r\n$4\r\ntest\r\n");
  ASSERT_EQ(expected, array);
}

TEST(StringUtil, HasPrefix) {
  ASSERT_TRUE(util::HasPrefix("has_prefix_is_true", "has_prefix"));
  ASSERT_FALSE(util::HasPrefix("has_prefix_is_false", "_has_prefix"));
  ASSERT_TRUE(util::HasPrefix("has_prefix", "has_prefix"));
  ASSERT_FALSE(util::HasPrefix("has", "has_prefix"));
}
