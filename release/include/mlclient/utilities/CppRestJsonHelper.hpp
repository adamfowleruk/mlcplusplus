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
 * \file CppRestJsonHelper.hpp
 *
 * \date 25 Apr 2016
 * \author Adam Fowler <adam.fowler@marklogic.com>
 */

#ifndef SRC_UTILITIES_CPPRESTJSONHELPER_HPP_
#define SRC_UTILITIES_CPPRESTJSONHELPER_HPP_

#include <mlclient/mlclient.hpp>
#include <mlclient/DocumentContent.hpp>
#include <mlclient/utilities/CppRestJsonDocumentContent.hpp>
#include <mlclient/Response.hpp>
#include <mlclient/SearchResult.hpp>
#include <mlclient/Permission.hpp>
// I don't mind exposing these in an optional helper class
#include <cpprest/json.h>

namespace mlclient {

/**
 * \brief A non-required utilities namespace. Be aware that classes in this namespace may have external dependencies. These are
 * documented in the class documentation.
 *
 * \since 8.0.0
 * \date 2016-04-24
 */
namespace utilities {

/**
 * \class CppRestJsonHelper
 * \author Adam Fowler <adam.fowler@marklogic.com>
 * \since 8.0.0
 * \date 2016-04-25
 *
 * \brief This class provides utility functions to handle JSON data.
 *
 * This is a non-instantiable class with static functions to handle conversion of data between raw cpprest web::json::value and IDocumentContent
 * objects.
 *
 * The fromResponse and toDocument functions are particularly useful when extracting information from a Response object.
 *
 * This class uses the CppRestJsonDocumentContent instance to directly wrap an underlying web::json::value instance.
 *
 * \note This class has an external dependency on Microsoft's C++ cpprest API. As this API is required to use MarkLogic's C++ wrapper (this API)
 * , this does not introduce any extra dependencies.
 */
class CppRestJsonHelper {
public:
  CppRestJsonHelper() = delete;
  ~CppRestJsonHelper() = delete;

  /// \name cpprestjsonhelper_documentconversion IDocumentContent conversion functions
  /// @{
  /**
   * \brief Creates a IDocumentContent instance based on a cpprest API web::json::value instance
   *
   * \note Actually returns a CppRestJsonDocumentContent instance (A subclass of TextDocumentContent)
   *
   * \param json The web::json::value to create a IDocumentContent representation of
   * \return A IDocumentContent instance wrapping the value
   */
  MLCLIENT_API static ITextDocumentContent* toDocument(web::json::value& json);

  /**
   * \brief Converts the Response directory to an ITextDocumentContent instance.
   *
   * \since 8.0.2
   * \date 2016-07-30
   *
   * \param resp The Response instance to create a web::json::value from.
   * \return A ITextDocumentContent instance representing the response
   */
  MLCLIENT_API static ITextDocumentContent* toDocument(const Response& resp);

  /**
   * \brief Creates a web::json::value from a IDocumentContent instance.
   *
   * \warning Don't call this on a CppRestJsonDocumentContent instance - use CppRestJsonDocumentContent::getJson() instead
   * \throw An InvalidFormatException if the document does not have the mime type of application/json, or if there is a parse error.
   * \param doc The IDocumentContent instance to create a web::json::value from.
   * \return A Microsoft cpprest API web::json::value instance created from the IDocumentContent.
   */
  MLCLIENT_API static const web::json::value fromDocument(const IDocumentContent& doc);

  /**
   * \brief Creates a web::json::value from a CppRestJsonDocumentContent instance.
   *
   * This is very efficient as the CppRestJsonDocumentContent effectively just wraps a web::json::value
   *
   * \param doc the CppRestJsonDocumentContent instance to extract the web::json::value from
   * \return A Microsoft cpprest API web::json::value instance extracted from the CppRestJsonDocumentContent.
   *
   * \since 8.0.2
   */
  MLCLIENT_API static const web::json::value fromDocument(const CppRestJsonDocumentContent& doc);

  /// @}

  /// \name cpprestjsonhelper_responseconversion Response conversion functions
  /// @{
  /**
   * \brief Creates a web::json::value from a Response object
   * \throw An InvalidFormatException if the document does not have the mime type of application/json, or if there is a parse error.
   * \param resp The Response instance to create a web::json::value from.
   * \return A Microsoft cpprest API web::json::value instance created from the Response.
   */
  MLCLIENT_API static web::json::value fromResponse(const Response& resp);

  /**
   * \brief Creates a web::json::value from a string object
   * \param jsonString The json String instance to create a web::json::value from.
   * \return A Microsoft cpprest API web::json::value instance created from the Response.
   */
  MLCLIENT_API static web::json::value fromString(const std::string& jsonString);

  /**
   * \brief Extracts a PermissionSet from a document metadata fetch response
   * \throw An InvalidFormatException if the document does not have the mime type of application/json, or if there is a parse error.
   * \param resp The Response instance to create a web::json::value from.
   * \return The PermissionSet extracted from the response
   *
   * \note PermissionSet is a typedef for std::vector<Permission>.
   *
   * \since 8.0.2
   */
  MLCLIENT_API static PermissionSet permissionsFromResponse(const Response& resp);

  //MLCLIENT_API static web::json::value fromSearchResult(const SearchResult& result);
  /// @}

};

} // end utilities namespace

} // end mlclient namespace

#endif /* SRC_UTILITIES_CPPRESTJSONHELPER_HPP_ */
