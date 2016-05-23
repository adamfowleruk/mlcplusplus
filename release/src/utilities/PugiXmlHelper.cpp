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
 * PugiXmlHelper.cpp
 *
 *  Created on: 25 Apr 2016
 *      Author: adamfowler
 */

#include "PugiXmlHelper.hpp"
#include "../DocumentContent.hpp"
#include "../Response.hpp"
#include "../InvalidFormatException.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <pugixml.hpp>

#include "../ext/easylogging++.h"

namespace mlclient {

namespace utilities {

// DocumentContent conversion
ITextDocumentContent* PugiXmlHelper::toDocument(const pugi::xml_document& dc) {
  TIMED_FUNC(PugiXmlHelper_toDocument);
  GenericTextDocumentContent* tdc = new GenericTextDocumentContent;
  std::ostringstream os;
  os << dc;
  tdc->setContent(os.str());
  tdc->setMimeType("application/xml");
  return tdc;
}
pugi::xml_document* PugiXmlHelper::fromDocument(const IDocumentContent& dc) {
  TIMED_FUNC(PugiXmlHelper_fromDocument);
  // TODO handle invalid cast exception

  std::ostringstream os;
  std::ostream* dcos(dc.getStream());
  os << dcos;
  delete dcos; // free pointer

  pugi::xml_document* doc = new pugi::xml_document;
  pugi::xml_parse_result result = doc->load_string(os.str().c_str());

  if (result) {
    return doc;
  } else {
    std::cout << "XML [" << os.str() << "] parsed with errors]\n";
    std::cout << "Error description: " << result.description() << "\n";
    std::cout << "Error offset: " << result.offset << " (error at [..." << os.str() << "]\n\n";
    throw new InvalidFormatException;
  }
}

// Response conversion
pugi::xml_document* PugiXmlHelper::fromResponse(const Response& resp) {
  TIMED_FUNC(PugiXmlHelper_fromResponse);
  if (resp.getResponseType() == ResponseType::XML) {
    pugi::xml_document* doc = new pugi::xml_document;
    pugi::xml_parse_result result = doc->load_string(resp.getContent().c_str());

    if (result) {
      return doc;
    } else {
      std::cout << "XML [" << resp.getContent() << "] parsed with errors]\n";
      std::cout << "Error description: " << result.description() << "\n";
      std::cout << "Error offset: " << result.offset << " (error at [..." << resp.getContent() << "]\n\n";
      throw new InvalidFormatException;
    }
  } else {
    throw new InvalidFormatException;
  }
}

} // end namespace utilities

} // end namespace mlclient
