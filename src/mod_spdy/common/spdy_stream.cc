// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mod_spdy/common/spdy_stream.h"

#include "mod_spdy/common/spdy_frame_priority_queue.h"
#include "mod_spdy/common/spdy_frame_queue.h"

namespace mod_spdy {

SpdyStream::SpdyStream(spdy::SpdyStreamId stream_id,
                       spdy::SpdyPriority priority,
                       SpdyFramePriorityQueue* output_queue)
    : stream_id_(stream_id),
      priority_(priority),
      output_queue_(output_queue) {}

SpdyStream::~SpdyStream() {}

bool SpdyStream::is_aborted() const {
  return input_queue_.is_aborted();
}

void SpdyStream::Abort() {
  input_queue_.Abort();
}

void SpdyStream::PostInputFrame(spdy::SpdyFrame* frame) {
  input_queue_.Insert(frame);
}

bool SpdyStream::GetInputFrame(bool block, spdy::SpdyFrame** frame) {
  return input_queue_.Pop(block, frame);
}

void SpdyStream::SendOutputFrame(spdy::SpdyFrame* frame) {
  output_queue_->Insert(priority_, frame);
}

}  // namespace mod_spdy
