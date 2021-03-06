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
 * \file ResponseHelper.hpp
 *
 * \date 2016-06-08
 * \author Adam Fowler <adam.fowler@marklogic.com>
 */

#ifndef SRC_UTILITIES_RESPONSEHELPER_HPP_
#define SRC_UTILITIES_RESPONSEHELPER_HPP_

#include <mlclient/mlclient.hpp>
#include <mlclient/Response.hpp>
#include <mlclient/ValuesResult.hpp>
#include <vector>
#include <string>

namespace mlclient {

namespace utilities {

/**
 * \class ResponseHelper
 * \author Adam Fowler <adam.fowler@marklogic.com>
 * \since 8.0.2
 * \date 2016-06-08
 *
 * \brief This class provides utility functions to ease the use of Response objects.
 *
 * \note This class has an external dependency on Microsoft's C++ cpprest API. As this API is required to use MarkLogic's C++ wrapper (this API)
 * , this does not introduce any extra dependencies.
 */
class ResponseHelper {
public:
  ResponseHelper() = delete;
  ~ResponseHelper() = delete;

  /**
   * \brief Returns whether the specified response is a MarkLogic error response
   * \note Some MarkLogic error response do NOT return a HTTP 500, so this is an important method to learn!
   *
   * \param Response The response to introspect
   * \return True if the Response is an error response
   */
  MLCLIENT_API static bool isInError(const Response& resp);

  /**
   * \brief Returns the error message of a Response in error
   * Throws an exception if the response is not in error
   *
   * \param Response The response to introspect
   * \return The string value of the top level error message, if any
   */
  MLCLIENT_API static std::string getErrorMessage(const Response& resp);

  /**
   * \brief Returns the full error trace information as a string
   * Throws an exception if the response is not in error
   * \param Response The response to introspect
   * \return The full error stack as a string, if available
   */
  MLCLIENT_API static std::string getErrorDetailAsString(const Response& resp);

  /**
   * \brief Returns a string list of suggestion values. Used with the response from POST /v1/suggest.
   *
   * Returns a blank list if the response does not contain suggestions. Throws an exception if response is in error.
   *
   * \param Response The response to introspect
   * \return A list of suggestion values
   */
  MLCLIENT_API static SearchSuggestionSet getSuggestions(const Response& resp);

  /**
   * \brief Returns a double result from the specified aggregate in the result set
   *
   * \param[in] resp The Response object
   * \param[in] aggName The aggregate name to return (a single response allows multiple to be returned)
   * \return double The double typed aggregate result
   */
  MLCLIENT_API static double getAggregateResult(const Response& resp,const std::string& aggName);

  /**
   * \brief Extracts all aggregate results and places them in the provided ValuesResult holder
   * \param[in] resp The response to parse
   * \param[inout] vr The ValuesResult object to populate
   */
  MLCLIENT_API static void getAggregateResults(const Response& resp,ValuesResult& vr);

  /**
   * \brief Extracts all complex aggregate results and places them in the provided ValuesResult holder
   *
   * \note UDFs don't just return double values, they can return multiple values, and arrays of them (multiple map:map() objects)
   *
   * \param[in] resp The response to parse
   * \param[inout] vr The ValuesResult object to populate
   */
  MLCLIENT_API static void getComplexAggregateResults(const Response& resp,ValuesResult& vr);


}; // end ResponseHelper class

} // end namespace utilities

} // end namespace mlclient

#endif
