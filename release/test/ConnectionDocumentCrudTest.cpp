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
//
//  ConnectionDocumentCrudTest.cpp
//  Created by Adam Fowler on 27 Nov 2015.
//

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <string>
#include "ConnectionDocumentCrudTest.hpp"
#include "ConnectionFactory.hpp"
#include "mlclient/Connection.hpp"
#include "mlclient/Response.hpp"
#include "mlclient/DocumentContent.hpp"
#include "mlclient/NoCredentialsException.hpp"

#include <string>

#include "mlclient/logging.hpp"

using namespace mlclient;

CPPUNIT_TEST_SUITE_REGISTRATION(ConnectionDocumentCrudTest);


void ConnectionDocumentCrudTest::setUp(void) {
  LOG(DEBUG) << "ENTERING TEST SUITE ConnectionDocumentCrudTest::setUp";
  // set up connection
  ml = ConnectionFactory::getConnection();
  json = "{\"first\":\"value1\",\"second\":\"value2\"}";
  xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<doc><first>value1</first><second>value2</second></doc>";
  text = "Some very nice text document";
  pngFile = "documentation/mlclient.png";
  jsonUri = "/mlclient/tests/ConnectionDocumentCrudTest/doc.json";
  xmlUri = "/mlclient/tests/ConnectionDocumentCrudTest/doc.xml";
  textUri = "/mlclient/tests/ConnectionDocumentCrudTest/doc.txt";
  pngUri = "/mlclient/tests/ConnectionDocumentCrudTest/doc.png";
}

void ConnectionDocumentCrudTest::tearDown(void) {
  LOG(DEBUG) << "LEAVING TEST SUITE ConnectionDocumentCrudTest::tearDown";
  // delete all content
  ConnectionFactory::releaseConnection(ml);
  ml = nullptr;
}

void ConnectionDocumentCrudTest::testSaveJson(void) {
  TIMED_FUNC(testSaveJson);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testSaveJson";

  // Note not using the Json or Xml helpers as we're not testing them here
  GenericTextDocumentContent tdc;
  tdc.setMimeType(IDocumentContent::MIME_JSON);
  tdc.setContent(json);
  const Response* response = ml->saveDocumentContent(jsonUri,tdc);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 201 Created",ResponseCode::CREATED == response->getResponseCode());
  delete response;
}

void ConnectionDocumentCrudTest::testGetJson(void) {
  TIMED_FUNC(testGetJson);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testGetJson";
  const Response* response = ml->getDocument(jsonUri);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("The response is not a JSON response", ResponseType::JSON  == response->getResponseType());

  //CPPUNIT_ASSERT_MESSAGE("The JSON response content is modified compared to the original", 0 == json.compare(response->getContent()));

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 200 OK",ResponseCode::OK == response->getResponseCode());
  delete response;
}

void ConnectionDocumentCrudTest::testDeleteJson(void) {
  TIMED_FUNC(testDeleteJson);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << std::endl << " Entering testDeleteJson";
  const Response* response = ml->deleteDocument(jsonUri);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 204 No Content",ResponseCode::NO_CONTENT == response->getResponseCode());
  delete response;
}

void ConnectionDocumentCrudTest::testSaveXml(void) {
  TIMED_FUNC(testSaveXml);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testSaveXml";
  // Note not using the Json or Xml helpers as we're not testing them here
  GenericTextDocumentContent tdc;
  tdc.setMimeType("application/xml");
  tdc.setContent(xml);
  const Response* response = ml->saveDocumentContent(xmlUri,tdc);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 201 Created",ResponseCode::CREATED == response->getResponseCode());
  delete response;
}

void ConnectionDocumentCrudTest::testGetXml(void) {
  TIMED_FUNC(testGetXml);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testGetXml";
  const Response* response = ml->getDocument(xmlUri);

  ResponseType rt = response->getResponseType();
  LOG(DEBUG) << "  Response Type: " << rt;
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("The response is not a XML response", ResponseType::XML  == response->getResponseType());

  //CPPUNIT_ASSERT_MESSAGE("The XML response content is modified compared to the original", 0 == xml.compare(response->getContent()));
  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 200 OK",ResponseCode::OK == response->getResponseCode());
  delete response;
}


void ConnectionDocumentCrudTest::testDeleteXml(void) {
  TIMED_FUNC(testDeleteXml);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testDeleteXml";
  const Response* response = ml->deleteDocument(xmlUri);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 204 No Content",ResponseCode::NO_CONTENT == response->getResponseCode());
  delete response;
}


void ConnectionDocumentCrudTest::testSaveText(void) {
  TIMED_FUNC(testSaveText);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testSaveText";
  // Note not using the Json or Xml helpers as we're not testing them here
  GenericTextDocumentContent tdc;
  tdc.setMimeType("plain/text");
  tdc.setContent(text);
  const Response* response = ml->saveDocumentContent(textUri,tdc);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 201 Created",ResponseCode::CREATED == response->getResponseCode());
  delete response;
}

void ConnectionDocumentCrudTest::testGetText(void) {
  TIMED_FUNC(testGetText);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testGetText";
  const Response* response = ml->getDocument(textUri);

  ResponseType rt = response->getResponseType();
  LOG(DEBUG) << "  Response Type: " << rt;
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("The response is not a TEXT response", ResponseType::TEXT  == response->getResponseType());

  //CPPUNIT_ASSERT_MESSAGE("The TEXT response content is modified compared to the original", 0 == text.compare(response->getContent()));
  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 200 OK",ResponseCode::OK == response->getResponseCode());
  delete response;
}


void ConnectionDocumentCrudTest::testDeleteText(void) {
  TIMED_FUNC(testDeleteText);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testDeleteText";
  const Response* response = ml->deleteDocument(textUri);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 204 No Content",ResponseCode::NO_CONTENT == response->getResponseCode());
  delete response;
}


void ConnectionDocumentCrudTest::testSavePNG(void) {
  TIMED_FUNC(testSavePNG);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testSavePNG";
  // Note not using the Json or Xml helpers as we're not testing them here
  FileDocumentContent tdc(pngFile);
  tdc.setMimeType("image/png");
  const Response* response = ml->saveDocumentContent(pngUri,tdc);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 201 Created",ResponseCode::CREATED == response->getResponseCode());
  delete response;
}

void ConnectionDocumentCrudTest::testGetPNG(void) {
  TIMED_FUNC(testGetPNG);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testGetPNG";
  const Response* response = ml->getDocument(pngUri);

  ResponseType rt = response->getResponseType();
  LOG(DEBUG) << "  Response Type: " << rt;
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("The response is not a BINARY response", ResponseType::BINARY  == response->getResponseType());

  //CPPUNIT_ASSERT_MESSAGE("The TEXT response content is modified compared to the original", 0 == text.compare(response->getContent()));
  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 200 OK",ResponseCode::OK == response->getResponseCode());
  delete response;
}


void ConnectionDocumentCrudTest::testDeletePNG(void) {
  TIMED_FUNC(testDeletePNG);
  LOG(DEBUG) << " --------------------------------------------";
  LOG(DEBUG) << " Entering testDeletePNG";
  const Response* response = ml->deleteDocument(pngUri);

  LOG(DEBUG) << "  Response Type: " << response->getResponseType();
  LOG(DEBUG) << "  Response Code: " << response->getResponseCode();
  LOG(DEBUG) << "  Response Content: " << response->getContent();

  CPPUNIT_ASSERT_MESSAGE("REST API did not return HTTP 204 No Content",ResponseCode::NO_CONTENT == response->getResponseCode());
  delete response;
}
