/*
 *  Copyright 2014 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_PC_EXTERNALHMAC_H_
#define WEBRTC_PC_EXTERNALHMAC_H_

// External libsrtp HMAC auth module which implements methods defined in
// auth_type_t.
// The default auth module will be replaced only when the ENABLE_EXTERNAL_AUTH
// flag is enabled. This allows us to access to authentication keys,
// as the default auth implementation doesn't provide access and avoids
// hashing each packet twice.

// How will libsrtp select this module?
// Libsrtp defines authentication function types identified by an unsigned
// integer, e.g. SRTP_HMAC_SHA1 is 3. Using authentication ids, the
// application can plug any desired authentication modules into libsrtp.
// libsrtp also provides a mechanism to select different auth functions for
// individual streams. This can be done by setting the right value in
// the auth_type of srtp_policy_t. The application must first register auth
// functions and the corresponding authentication id using
// crypto_kernel_replace_auth_type function.

#include "webrtc/base/basictypes.h"
#ifdef HAVE_SRTP
extern "C" {
#ifdef SRTP_RELATIVE_PATH
#include "auth.h"  // NOLINT
#else
#include "third_party/libsrtp/crypto/include/auth.h"
#endif  // SRTP_RELATIVE_PATH
}
#endif  // HAVE_SRTP

#if defined(HAVE_SRTP) && !defined(SRTP_HMAC_SHA1)
// Include compatibility shims to compile against libsrtp 1.x.
// TODO(mattdr): Remove once Chromium uses libsrtp 2.

// Remember that the definition of SRTP_HMAC_SHA1 is synthetic.
#define COMPILING_AGAINST_LIBSRTP1 1

#define SRTP_HMAC_SHA1 HMAC_SHA1
#define srtp_auth_t auth_t
#endif

#if defined(HAVE_SRTP) && defined(ENABLE_EXTERNAL_AUTH)

#define EXTERNAL_HMAC_SHA1 SRTP_HMAC_SHA1 + 1
#define HMAC_KEY_LENGTH 20

// The HMAC context structure used to store authentication keys.
// The pointer to the key  will be allocated in the external_hmac_init function.
// This pointer is owned by srtp_t in a template context.
typedef struct {
  uint8_t key[HMAC_KEY_LENGTH];
  int key_length;
} ExternalHmacContext;

srtp_err_status_t external_hmac_alloc(srtp_auth_t** a,
                                      int key_len,
                                      int out_len);

srtp_err_status_t external_hmac_dealloc(srtp_auth_t* a);

srtp_err_status_t external_hmac_init(ExternalHmacContext* state,
                                     const uint8_t* key,
                                     int key_len);

srtp_err_status_t external_hmac_start(ExternalHmacContext* state);

srtp_err_status_t external_hmac_update(ExternalHmacContext* state,
                                       const uint8_t* message,
                                       int msg_octets);

srtp_err_status_t external_hmac_compute(ExternalHmacContext* state,
                                        const void* message,
                                        int msg_octets,
                                        int tag_len,
                                        uint8_t* result);

srtp_err_status_t external_crypto_init();

#endif  // defined(HAVE_SRTP) && defined(ENABLE_EXTERNAL_AUTH)
#endif  // WEBRTC_PC_EXTERNALHMAC_H_
