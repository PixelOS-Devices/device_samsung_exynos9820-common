/*
 * Copyright (C) 2024 The LineageOS Project
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

#include <sync/sync.h>
#include <ui/GraphicBufferMapper.h>

using android::status_t;

extern "C" {
status_t _ZN7android19GraphicBufferMapper6unlockEPK13native_handle(void* thisptr,
                                                                   buffer_handle_t handle) {
    android::base::unique_fd outFence;
    auto* gpm = static_cast<android::GraphicBufferMapper*>(thisptr);
    status_t status = gpm->unlock(handle, &outFence);
    if (status == android::OK && outFence.get() >= 0) {
        sync_wait(outFence.get(), -1);
        outFence.reset();
    }
    return status;
}
}
