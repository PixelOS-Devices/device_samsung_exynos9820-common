/*
 * Copyright (C) 2025 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Fence.h"

#define ATRACE_TAG ATRACE_TAG_GRAPHICS

// We would eliminate the non-conforming zero-length array, but we can't since
// this is effectively included from the Linux kernel
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wzero-length-array"
#include <sync/sync.h>
#pragma clang diagnostic pop

#include <sys/types.h>
#include <unistd.h>
#include <utils/Trace.h>

using android::NO_ERROR;

namespace exynos5 {

Fence::Fence(int fenceFd) :
    mFenceFd(fenceFd) {
}

Fence::Fence(unique_fd fenceFd) :
    mFenceFd(std::move(fenceFd)) {
}

status_t Fence::wait(int timeout) {
    ATRACE_CALL();
    if (mFenceFd == -1) {
        return NO_ERROR;
    }
    int err = sync_wait(mFenceFd, timeout);

    close(mFenceFd.release());

    return err < 0 ? -errno : status_t(NO_ERROR);
}

} // namespace exynos5
