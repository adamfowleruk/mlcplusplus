//
//  ConnectionDocumentCrudTest.hpp
//  Scratch
//
//  Created by Adam Fowler on 27/Nov/2015.
//  Copyright (c) 2015 Adam Fowler. All rights reserved.
//

#include <cppunit/Test.h>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#ifndef __Scratch__ConnectionDocumentCrudTest__
#define __Scratch__ConnectionDocumentCrudTest__

class ConnectionDocumentCrudTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(ConnectionDocumentCrudTest);
    CPPUNIT_TEST(TestGet);
    CPPUNIT_TEST(TestSaveJson);
    CPPUNIT_TEST(TestSaveAllJson);
    CPPUNIT_TEST(TestDelete);
    CPPUNIT_TEST_SUITE_END();
public:
    void TestGet(void);
    void TestSaveJson(void);
    void TestSaveAllJson(void);
    void TestDelete(void);
};

#endif /* defined(__Scratch__ConnectionDocumentCrudTest__) */