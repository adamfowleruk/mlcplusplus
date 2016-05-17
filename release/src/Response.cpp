//
//  Response.cpp
//  Scratch
//
//  Created by Paul Hoehne on 5/29/14.
//  Copyright (c) 2014 Paul Hoehne. All rights reserved.
//
#include "HttpHeaders.hpp"
#include "Response.hpp"

#include <algorithm>
#include <regex> // using std::regex as of C++14

#include <cstdint>

#include "easylogging++.h"

namespace mlclient {


/*
 * Response Type operators - allows string output of code in human readable form
 */

/**
 * Adds the textual respresentation of a response type to a stream. E.g. ResponseType::BINARY
 * @param os Output Stream (E.g. std::cout)
 * @param rt Response Type const reference
 * @return
 */
std::ostream& operator << (std::ostream& os, const ResponseType& rt) {
  /*
  switch(rt) {
  case ResponseType::BINARY:
    os << "ResponseType::BINARY";
    break;
  case ResponseType::JSON:
    os << "ResponseType::JSON";
    break;
  case ResponseType::TEXT:
    os << "ResponseType::TEXT";
    break;
  case ResponseType::XML:
    os << "ResponseType::XML";
    break;
  case ResponseType::UNKNOWN:
    os << "ResponseType::UNKNOWN";
    break;
  }
  return os;
  */
  os << translate(rt);
  return os;
}

/**
 * Adds the textual respresentation of a response type to a string. E.g. ResponseType::BINARY
 * @param s String to concatenate to
 * @param rt The response type const reference
 * @return
 */
std::string& operator +(std::string& s, const ResponseType& rt) {
  /*
  switch(rt) {
  case ResponseType::BINARY:
    all.append("ResponseType::BINARY");
    break;
  case ResponseType::JSON:
    all.append("ResponseType::JSON");
    break;
  case ResponseType::TEXT:
    all.append("ResponseType::TEXT");
    break;
  case ResponseType::XML:
    all.append("ResponseType::XML");
    break;
  default:
    all.append("ResponseType::UNKNOWN");
  }*/
  s.append(translate(rt));
  return s;
}

/**
 * Adds the textual respresentation of a response type to a string (C-string char*). E.g. ResponseType::BINARY
 * @param orig the char* before this response type
 * @param rt The response type const reference
 * @return
 */
/*std::string& operator+(const char* orig,const ResponseType& rt) {
  std::ostringstream os;
  os << std::string(orig) << translate(rt);
  //std::unique_ptr<std::string> ref = std::unique_ptr<std::string>(new std::string(os.str()));
  std::string& ref = std::string(os.str());
  return ref;
}
*/

const std::string translate(const ResponseType& rt) {
  std::ostringstream os;
  os << "Unknown Response Type: "  << (int)rt;
  std::string result = os.str();
  switch(rt) {
  case ResponseType::BINARY:
    result = "ResponseType::BINARY";
    break;
  case ResponseType::JSON:
    result = "ResponseType::JSON";
    break;
  case ResponseType::TEXT:
    result = "ResponseType::TEXT";
    break;
  case ResponseType::XML:
    result = "ResponseType::XML";
    break;
  case ResponseType::UNKNOWN_TYPE:
    result = "ResponseType::UNKNOWN_TYPE";
    break;
  }
  return result;
}


/*
 * Response Code operators - allows string output of code in human readable form
 */

std::ostream& operator << (std::ostream& os, const ResponseCode& rc) {
  os << translate(rc);
  return os;
}


std::string& operator+(std::string& s,const ResponseCode& rc) {
  s.append(translate(rc));
  return s;
}
/*
std::string& operator+(const char* orig,const ResponseCode& rc) {
  std::ostringstream os;
  os << std::string(orig) << translate(rc);
  std::string& ref = os.str();
  return ref;
}*/


const std::string translate(const ResponseCode& val) {
  std::ostringstream os;
  os << "Unknown Response Code: " << (int)val;
  std::string result = os.str();
  switch (val) {
  case ResponseCode::UNKNOWN_CODE:
    result = "Unknown"; break;
  case ResponseCode::CONTINUE:
    result = "Continue"; break;
  case ResponseCode::OK:
    result = "OK"; break;
  case ResponseCode::CREATED:
    result = "Created"; break;
  case ResponseCode::ACCEPTED:
    result = "Accepted"; break;
  case ResponseCode::NO_CONTENT:
    result = "No Content or Updated (MarkLogic REST API)"; break;
  case ResponseCode::RESET_CONTENT:
    result = "Reset Content"; break;
  case ResponseCode::PARTIAL_CONTENT:
    result = "Partial Content"; break;
  case ResponseCode::MULTIPLE_CHOICES:
    result = "Multiple Choices"; break;
  case ResponseCode::MOVED_PERMANENTLY:
    result = "Moved Permanently"; break;
  case ResponseCode::FOUND:
    result = "Found"; break;
  case ResponseCode::SEE_OTHER:
    result = "See Other"; break;
  case ResponseCode::NOT_MODIFIED:
    result = "Not Modified"; break;
  case ResponseCode::USE_PROXY:
    result = "Use Proxy"; break;
  case ResponseCode::TEMPORARY_REDIRECT:
    result = "Temporary Redirect"; break;
  case ResponseCode::BAD_REQUEST:
    result = "Bad Request"; break;
  case ResponseCode::UNAUTHORIZED:
    result = "Unauthorized"; break;
  case ResponseCode::PAYMENT_REQUIRED:
    result = "Payment Required"; break;
  case ResponseCode::FORBIDDEN:
    result = "Forbidden"; break;
  case ResponseCode::NOT_FOUND:
    result = "Not Found"; break;
  case ResponseCode::METHOD_NOT_ALLOWED:
    result = "Method Not Allowed"; break;
  case ResponseCode::NOT_ACCEPTABLE:
    result = "Not Acceptable"; break;
  case ResponseCode::PROXY_AUTHENTICATION_REQUIRED:
    result = "Proxy Authentication Required; "; break;
  case ResponseCode::REQUEST_TIMEOUT:
    result = "Request Timeout"; break;
  case ResponseCode::CONFLICT:
    result = "Conflict"; break;
  case ResponseCode::GONE:
    result = "Gone"; break;
  case ResponseCode::LENGTH_REQUIRED:
    result = "Length Required"; break;
  case ResponseCode::PRECONDITION_FAILED:
    result = "Precondition Failed"; break;
  case ResponseCode::REQUEST_ENTITY_TOO_LARGE:
    result = "Request Entity Too Large"; break;
  case ResponseCode::REQUEST_URI_TOO_LONG:
    result = "Request URI Too Long"; break;
  case ResponseCode::UNSUPPORTED_MEDIA_TYPE:
    result = "Unsupported Media Type"; break;
  case ResponseCode::REQUEST_RANGE_BAD:
    result = "Request Range Not Satisfiable"; break;
  case ResponseCode::EXPECTATION_FAILED:
    result = "Expectation Failed"; break;
  case ResponseCode::INTERNAL_SERVER_ERROR:
    result = "Internal Server Error"; break;
  case ResponseCode::NOT_IMPLEMENTED:
    result = "Not Implemented"; break;
  case ResponseCode::BAD_GATEWAY:
    result = "Bad Gateway"; break;
  case ResponseCode::SERVICE_UNAVAILABLE:
    result = "Service Unavailable"; break;
  case ResponseCode::GATEWAY_TIMEOUT:
    result = "Gateway Timeout"; break;
  case ResponseCode::HTTP_VERSION_NOT_SUPPORTED:
    result = "HTTP Version Not Supported"; break;
  }
  return result;
};















const std::regex content_type_re("([a-zA-Z\\.]+)/([a-zA-Z\\.]+)");

class Response::Impl {
public:
  Impl() : responseCode(ResponseCode::UNKNOWN_CODE), responseType(ResponseType::UNKNOWN_TYPE)  {
    LOG(DEBUG) << "    Response::Impl::defaultConstructor @" << &*this;
    content = std::unique_ptr<std::string>(new std::string("")); // MUST BE INITIALISED
  };
  ~Impl() {
    ;
  };


  ResponseCode responseCode; /*!< The response code 200/400/404, etc */
  ResponseType  responseType; /*!< The response type text,xml,binary, etc. */
  mlclient::HttpHeaders      headers;       /*!< The response headers */
  std::unique_ptr<std::string> content;


  ///
  /// Parses the content type header to guess the content type of the
  /// response
  ///
  /// \param The raw header value (i.e. 'text/plain')
  ResponseType parseContentTypeHeader(const std::string& content) {
    TIMED_FUNC(Response_parseContentTypeHeader);
    std::smatch matches;
    enum ResponseType result = ResponseType::BINARY;
    if (std::regex_search(content, matches, content_type_re)) {
      std::string major = matches[1];
      std::string minor = matches[2];

      if (major == "application" || major == "text") {
        if (minor == "json") {
          result = ResponseType::JSON;
        } else if(minor == "html" || minor == "xml") {
          result = ResponseType::XML;
        } else if(minor == "plain") {
          result = ResponseType::TEXT;
        }
      }
    }
    return result;
  };

};



Response::Response() : mImpl(new Impl) {
  LOG(DEBUG) << "    Response::defaultConstructor @" << &*this;
  // ignore compilation warning - we know they are each set individually later, due to the nature of HTTP response interrogation code.
  //_xml = pugi::xml_document;
}

Response::~Response() {
  delete mImpl;
  mImpl = NULL;
}


void Response::setResponseCode(const ResponseCode& code) {
  mImpl->responseCode = code;
}

void Response::setResponseType(const enum ResponseType& type) {
  mImpl->responseType = type;
}
/*
void Response::SetResponseHeaders(const http_headers& headers) {
  _headers = headers;   
}*/

void Response::setResponseHeaders(const mlclient::HttpHeaders& headers) {
  mImpl->headers.clear();
  const std::string& ct = "Content-type";
  std::string value = headers.getHeader(ct);
  if ("" == value) {
    value = headers.getHeader("Content-Type");
  }
  if ("" != value) {
    mImpl->responseType = mImpl->parseContentTypeHeader(value);
  }

  for (auto& iter : headers.getHeaders()) {
    mImpl->headers.setHeader(iter.first,iter.second);
    if (iter.first == "Content-type" || iter.first == "Content-Type") {
      mImpl->responseType = mImpl->parseContentTypeHeader(iter.second);
    }
  }
}

ResponseCode Response::getResponseCode(void) const {
  return mImpl->responseCode;
}

ResponseType Response::getResponseType(void) const {
  return mImpl->responseType;
}

HttpHeaders Response::getResponseHeaders(void) const {
  return mImpl->headers;
}

/*
 * Read up to max size bytes into the response, starting at offset.
 */
size_t Response::read(void* buffer, const size_t& max_size, const size_t off) {
  return 0;
}

/*
 * Tries to read back the response as a string.  Throws ResponseTypeException
 * if the response is not a string or string based.
 */
const std::string& Response::getContent() const {
  return *(mImpl->content); // TODO check this - force copy cstor - WHY!?! const return type
}

/*
void Response::setContent(std::unique_ptr<std::string> content) {
  mImpl->content = std::move(content); // move ownership from function to object
  //std::cout << "SetContent: parameter: " << content << ", member variable: " << _content << std::endl;
}
*/

void Response::setContent(std::string* content) {
  mImpl->content = std::move(std::unique_ptr<std::string>(new std::string(*content)));
}


}
