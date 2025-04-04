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

#include <android-base/unique_fd.h>
#include <utils/Errors.h>
#include <utils/RefBase.h>

using android::base::unique_fd;
using android::status_t;

namespace exynos5 {

class Fence
    : public android::LightRefBase<Fence> {
public:
    explicit Fence(int fenceFd);
    explicit Fence(unique_fd fenceFd);

    status_t wait(int timeout);

private:
    friend class LightRefBase<Fence>;
    virtual ~Fence() = default;

    android::base::unique_fd mFenceFd;
};

} // namespace exynos5
