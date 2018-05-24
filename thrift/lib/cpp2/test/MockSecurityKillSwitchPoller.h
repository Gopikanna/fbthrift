/*
 * Copyright 2016-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <gmock/gmock.h>
#include <thrift/lib/cpp2/security/SecurityKillSwitchPoller.h>

namespace apache {
namespace thrift {

class MockSecurityKillSwitchPoller : public SecurityKillSwitchPoller {
 public:
  explicit MockSecurityKillSwitchPoller(std::function<bool()> pollFunc)
      : SecurityKillSwitchPoller(false, std::chrono::seconds(1)) {
    auto yCob = [this, pollFunc]() { switchEnabled_ = pollFunc(); };
    auto condition = wangle::FilePoller::doAlwaysCond();
    poller_->addFileToTrack("no_file", yCob, nullptr, condition);
  }
  MOCK_METHOD4(
      addFileToTrack,
      void(
          const std::string&,
          wangle::FilePoller::Cob,
          wangle::FilePoller::Cob,
          wangle::FilePoller::Condition));
};
}
}
