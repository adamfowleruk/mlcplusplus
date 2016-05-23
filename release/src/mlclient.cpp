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
 * \file MLCPlusPlus.cpp
 * \author Adam Fowler <adam.fowler@marklogic.com>
 * \date 2014-06-04
 */

#include "ext/mlclient.hpp"

#ifndef ELPP_PERFORMANCE_MICROSECONDS
#define ELPP_PERFORMANCE_MICROSECONDS 1
#endif

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

namespace mlclient {
int runOnce() {
    LOG(INFO) << "Registering logger [mlclient]";
    el::Loggers::getLogger("mlclient");

    el::Configurations defaultConf;
    defaultConf.setToDefault();
    // Values are always std::string
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime %level %fbase:%line %msg");
    // default logger uses default configurations
    el::Loggers::reconfigureLogger("default", defaultConf);

    el::Configurations performanceConf;
    performanceConf.setToDefault();
    performanceConf.set(el::Level::Info, el::ConfigurationType::Format, "%msg");
    performanceConf.set(el::Level::Info,el::ConfigurationType::Filename,"../performance.log"); /// TODO make output file include version number of this upcoming release
    el::Loggers::reconfigureLogger("performance", performanceConf);
    el::Loggers::addFlag(el::LoggingFlag::FixedTimeFormat); // ensures performance numbers are always quoted as seconds, never formatted

    return 0;
}

int runOnceHelper = runOnce();


} // end namespace mlclient
