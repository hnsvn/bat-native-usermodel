/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef DEPS_BAT_USERMODEL_SRC_STATIC_VALUES_H_
#define DEPS_BAT_USERMODEL_SRC_STATIC_VALUES_H_

namespace usermodel {

static const int kMinimumWordsToClassify = 20;
static const int kMaximumWordsToClassify = 1234;
static const int kMaximumHtmlLengthToClassify = 1024 * 1024;
static const int kMaxSubLen = 6; 
static const int kNumBuckets = 10000;

}  // namespace usermodel

#endif  // DEPS_BAT_USERMODEL_SRC_STATIC_VALUES_H_
