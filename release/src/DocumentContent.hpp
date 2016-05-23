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
 */
/**
 * \file DocumentContent.hpp
 *
 * \since 8.0.0
 * \date 2016-04-25
 * \author Adam Fowler <adam.fowler@marklogic.com>
 * \brief Contains classes and enums to handle document content (not properties, permissions, uri etc.) for basic content
 * types (text,binary,json,xml) being used with MarkLogic Server
 */

#ifndef SRC_DOCUMENTCONTENT_HPP_
#define SRC_DOCUMENTCONTENT_HPP_

#include <string>
#include <iosfwd>

namespace mlclient {

/**
 * \brief This class represents the internal content of a Document. It can be XML, JSON, String or Binary (or a sub type thereof).
 *
 * This class can also be used to wrap search options and other JSON/XML based content.
 * There are only two specialisations of this class - text and binary - all more complex types are created by using
 * the \link CppRestJsonHelper \endlink and \link PugiXmlHelper \endlink to parse/create these types. E.g. a pugixml::document or web::json::value.
 *
 * \author Adam Fowler <adam.fowler@marklogic.com>
 * \since 8.0.0
 * \date 2016-04-25
 *
 * \note This is an abstract class designed for extending, and cannot be instantiated directly.
 */
class IDocumentContent {
public:
  // default constructor creation by compiler
  /**
   * The IDocumentContent constructor. Called implicitly by subclasses only.
   */
  IDocumentContent();

  /**
   * A virtual destructor, ripe for overloading. REQUIRED to allow subclassing
   */
  virtual ~IDocumentContent();

  /**
   * \brief Returns the content of this IDocumentContent as an ostream.
   *
   * This allows streaming to a HTTP request, and works for binary and string content.
   *
   * \note The stream may be read from asynchronously, so do not destroy the underlying content after returning the stream.
   *
   * \return An ostream instance wrapping the content of this Document Content instance
   */
  virtual std::ostream* getStream() const = 0;

  /**
   * \brief Returns the content of this IDocumentContent as a std::string.
   *
   * This allows streaming of a HTTP request, with data encoded as a string.
   *
   * \return A string representing this content;
   */
  virtual std::string getContent() const = 0;

  /**
   * \brief Returns the MIME type of this content.
   *
   * E.g. application/json or application/xml
   *
   * \return The string representation of the MIME type. Does not include encoding (always assume UTF-8 for MarkLogic Server)
   */
  virtual std::string getMimeType() const = 0;

  /**
   * \brief Sets the MIME type of this content.
   *
   * E.g. application/json or application/xml
   *
   * \param[in] mt The mimetype string, not including encoding, for this Document Content. Assume always UTF-8 for MarkLogic Server)
   */
  virtual void setMimeType(const std::string& mt) = 0;

  static const std::string MIME_JSON; //< The value application/json
  static const std::string MIME_XML; //< The value application/xml

};

// TODO streaming operator




/**
 * \brief An overarching interface for a Text Document
 * \since 8.0.0
 * \date 2016-05-12
 *
 * \author Adam Fowler <adam.fowler@marklogic.com>
 */
class ITextDocumentContent : public IDocumentContent {
public:
  ITextDocumentContent();
  virtual ~ITextDocumentContent();

  /**
   * \brief Sets the textual content for this document
   *
   * Assumes content string is non null
   *
   * \param[in] The string content to copy in to this object.
   */
  virtual void setContent(std::string content) = 0;

  /**
   * \brief Returns the number of characters in the content string.
   *
   * \note This number does not include C null characters - just std::string length
   *
   * \return The number of characters in the string. Does not include C null character.
   */
  virtual int getLength() const = 0;
};






// SPECIALISATION TYPES - DEFAULT IMPLEMENTATIONS


/**
 * \brief This class is a specialisation of ITextDocumentContent (and thus IDocumentContent) that holds all data in a string.
 * \since 8.0.0
 * \date 2016-05-12
 *
 * \author Adam Fowler <adam.fowler@marklogic.com>
 *
 * This class is used as the data holding class for all JSON and XML documents.
 * There are no JSON or XML specialisations (Use the JSON and XML helper classes in the \link utilities \endlink namespace
 * instead to create, modify, or introspect the JSON/XML.)
 */
class GenericTextDocumentContent : public ITextDocumentContent {
public:
  /**
   * \brief Constructs a blank text document
   *
   * The type will by default be set to JSON. Content will by default be an empty string.
   */
  GenericTextDocumentContent();

  /**
   * \brief deep copy constructor
   */
  GenericTextDocumentContent(const GenericTextDocumentContent& doc);

  /**
   * \brief deep copy constructor
   */
  GenericTextDocumentContent(const ITextDocumentContent& doc);

  /**
   * \brief Pure virtual destructor
   */
  virtual ~GenericTextDocumentContent();

  /**
   * \brief Sets the textual content for this document
   *
   * Assumes content string is non null
   *
   * \param[in] The string content to copy in to this object.
   */
  void setContent(std::string content) override;

  /**
   * \brief Returns the content of this TextDocumentContent as an ostream.
   *
   * This allows streaming to a HTTP request of this string content.
   *
   * \note The stream may be read from asynchronously, so do not destroy the underlying content after returning the stream.
   *
   * \return An ostream instance wrapping the content of this Text Document Content instance
   */
  std::ostream* getStream() const override;

  /**
   * \brief Returns the content as a string
   *
   * \return The string representation of the content.
   */
  std::string getContent() const override;



  /**
   * \brief Returns the MIME type of this content.
   *
   * E.g. application/json or application/xml
   *
   * \return The string representation of the MIME type. Does not include encoding (always assume UTF-8 for MarkLogic Server)
   */
  std::string getMimeType() const override;

  /**
   * \brief Sets the MIME type of this content.
   *
   * E.g. application/json or application/xml
   *
   * \param[in] mt The mimetype string, not including encoding, for this Document Content. Assume always UTF-8 for MarkLogic Server)
   */
  void setMimeType(const std::string& mt) override;


  /**
   * \brief Returns the number of characters in the content string.
   *
   * \note This number does not include C null characters - just std::string length
   *
   * \return The number of characters in the string. Does not include C null character.
   */
  int getLength() const override;

private:
  class Impl;
  Impl* mImpl;
};

/**
 * \brief An enumeration for use with the BinaryDocumentContent class.
 *
 * There are many ways to encode a Binary document as a string. This enum allows them to be described.
 */
enum BinaryEncoding : int {
  HEX = 1,     //< Hexadecimal representation i.e. as characters 0-F
  BIN = 2      //< As binary, rather than encoded. Used in multi-part mime
};




/**
 * \brief This class is a specialisation of IDocumentContent that holds binary data.
 * \since 8.0.0
 *
 * This class provides additional methods to make working with binary data more convenient.
 *
 * \note There are also operators like << available for streaming support.
 *
 * \warning This class is not yet implemented by a concrete class, or supported by the C++ API. It is here for reference only.
 */
class IBinaryDocumentContent : public IDocumentContent {
public:
  /**
   * \brief Default constructor. Initialises the binary content to an empty buffer, of zero length.
   */
  IBinaryDocumentContent();

  /**
   * \brief Destructor. Will deallocate all contained buffered data
   */
  virtual ~IBinaryDocumentContent();

  /**
   * \brief Sets the content from the given string.
   *
   * Used when receiving binary content as text from MarkLogic Server. E.g. as part of a multi part mime response.
   *
   * \note Defaults to HEX encoding.
   *
   * \param[in] content The string content to copy in to the buffer.
   */
  void setContent(std::string content);

  /**
   * \brief Returns the textual representation of this content.
   *
   * Defaults to HEX encoding TODO verify this is true for ML Server multipart mime
   *
   * \return The content of this buffer encoded as a string (HEX encoding by default)
   */
  std::string& getContent(); // default to one encoding

  /**
   * \brief Returns the string representation(encoding) of the binary content, using the specified representation (HEX, BINARY, etc.)
   *
   * This is a specialist method for binary content. This allows the encoding to be specified by API calls that are aware of which
   * encoding is in use.
   *
   * \param[in] encoding The encoding to use. Defaults to HEX
   * \return The string representation of the binary content in the requested encoding.
   */
  std::string& getContent(const enum BinaryEncoding& encoding = BinaryEncoding::HEX);

  /**
   * \brief Sets the content from a raw binary buffer.
   *
   * For use with an input stream. See the << operator for this class too.
   *
   * TODO check parameters' validity, and document accordingly.
   */
  //void setContent(char* binary,int offset,int length); // TODO proper useful definition

  /**
   * \brief Returns the number of characters in the TEXTUAL encoding of this binary document. (i.e. NOT raw byte length)
   *
   * This is required in order to be compatible with API to send the data to a HTTP server.
   *
   * \return The integer length of the string encoding (not the binary buffer length) of this data.
   */
  //int getLength();



  /**
   * \brief Returns the MIME type of this content.
   *
   * E.g. application/json or application/xml
   *
   * \return The string representation of the MIME type. Does not include encoding (always assume UTF-8 for MarkLogic Server)
   */
  virtual std::string getMimeType() const override = 0;

  /**
   * \brief Sets the MIME type of this content.
   *
   * E.g. application/json or application/xml
   *
   * \param[in] mt The mimetype string, not including encoding, for this Document Content. Assume always UTF-8 for MarkLogic Server)
   */
  virtual void setMimeType(const std::string& mt) override = 0;



  /**
   * \brief Returns the content of this TextDocumentContent as an ostream.
   *
   * This allows streaming to a HTTP request of this string content.
   *
   * \note The stream may be read from asynchronously, so do not destroy the underlying content after returning the stream.
   *
   * \return An ostream instance wrapping the content of this Text Document Content instance
   */
  virtual std::ostream* getStream() const override = 0;

  /**
   * \brief Returns the content as a string
   *
   * \return The string representation of the content.
   */
  virtual std::string getContent() const override = 0;

private:
  class Impl;
  Impl* mImpl;
};


// TODO << operator for BinaryDocumentContent

} // end mlclient namespace

#endif /* SRC_DOCUMENTCONTENT_HPP_ */
