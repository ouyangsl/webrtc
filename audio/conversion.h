/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_AUDIO_CONVERSION_H_
#define WEBRTC_AUDIO_CONVERSION_H_

namespace webrtc {

// Convert fixed point number with 14 bit fractional part, to floating point.
inline float Q14ToFloat(uint16_t v) {
  return static_cast<float>(v) / (1 << 14);
}
}  // namespace webrtc

#endif  // WEBRTC_AUDIO_CONVERSION_H_
