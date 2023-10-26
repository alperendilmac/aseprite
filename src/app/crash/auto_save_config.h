// Aseprite
// Copyright (C) 2019  Igara Studio S.A.
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifndef APP_CRASH_AUTO_SAVE_CONFIG_H_INCLUDED
#define APP_CRASH_AUTO_SAVE_CONFIG_H_INCLUDED
#pragma once

namespace app {
namespace crash {

  // Structure to store the configuration from Preferences instance to
  // avoid accessing to Preferences from a non-UI thread.
  struct AutoSaveConfig {
    double autoSavePeriod;
    //int keepEditedSpriteDataFor;
  };

} // namespace crash
} // namespace app

#endif
