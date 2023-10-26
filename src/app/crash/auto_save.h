// Aseprite
// Copyright (C) 2019-2020  Igara Studio S.A.
// Copyright (C) 2001-2018  David Capello
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifndef APP_CRASH_AUTO_SAVE_H_INCLUDED
#define APP_CRASH_AUTO_SAVE_H_INCLUDED
#pragma once

#include "app/context_observer.h"
#include "app/doc_observer.h"
#include "app/docs_observer.h"
#include "app/file_system.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

namespace app {
class Context;
class Doc;
namespace crash {
  struct AutoSaveConfig;
  class Session;

  class AutoSaver {
  public:
    AutoSaver(AutoSaveConfig * config,
              Session* session,
              Context* ctx);
    ~AutoSaver();

    void stop();

    //void onAddDocument(Doc* document) override;
    //void onRemoveDocument(Doc* document) override;

  private:
    void backgroundThread();
    //bool saveDocData(Doc* doc);

    AutoSaveConfig* m_config;
    Session* m_session;
    Context* m_ctx;
    std::vector<Doc*> m_documents;
    std::vector<IFileItem*> m_fileitems;
    std::atomic<bool> m_done;

    std::mutex m_mutex;

    // Used to wakeup the backgroundThread() when we have to stop the
    // thread that saves backups (i.e. when we are closing the application).
    std::condition_variable m_wakeup;

    std::thread m_thread;
  };

} // namespace crash
} // namespace app

#endif
