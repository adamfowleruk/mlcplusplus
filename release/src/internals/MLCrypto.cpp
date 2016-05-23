/* 
 * Copyright (c) MarkLogic Corporation. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * File:   MLCrypto.cpp
 * Author: phoehne
 * 
 * Created on July 7, 2014, 10:27 AM
 */

#include "MLCrypto.hpp"

#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>

namespace mlclient {

namespace internals {

MLCrypto::MLCrypto() {
}

MLCrypto::MLCrypto(const MLCrypto& orig) {
}

MLCrypto::~MLCrypto() {
}

std::string MLCrypto::md5(const std::string& raw) const {
  uint8_t buffer[16];

  MD5_CTX _context;
  MD5_Init(&_context);
  MD5_Update(&_context, raw.c_str(), raw.size());
  MD5_Final(buffer, &_context);

  return toHex(buffer, 16);
}

std::string MLCrypto::toHex(const uint8_t* bytes, const size_t& length) const {
  std::ostringstream hex_ss;
  hex_ss << std::hex;
  for (size_t i = 0; i < length; i++) { 
    hex_ss << std::setfill('0') << std::setw(2) << (int)bytes[i]; 
  }
  return hex_ss.str();
}

} // end namespace internals

} // end namespace mlclient
