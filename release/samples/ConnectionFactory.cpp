//
//  ConnectionFactory.cpp
//  Scratch
//
//  Created by Adam Fowler on 27 Nov 2015.
//  Copyright (c) 2015 Adam Fowler. All rights reserved.
//

#include "MLCPlusPlus.hpp"
#include "Connection.hpp"
#include "ConnectionFactory.hpp"

using namespace mlclient;

Connection* ConnectionFactory::getConnection() {
  Connection* conn = new Connection;
  // ALTER THE BELOW FOR YOUR OWN SYSTEM DURING TESTING
  conn->configure("192.168.123.4","8122","admin","admin",false);
  return conn;
}