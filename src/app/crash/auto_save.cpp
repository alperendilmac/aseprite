// Aseprite
// Copyright (C) 2018-2023  Igara Studio S.A.
// Copyright (C) 2001-2018  David Capello
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

// Uncomment if you want to test the backup process each 5 seconds.
//#define TEST_BACKUPS_WITH_A_SHORT_PERIOD

// Uncomment if you want to check that backups are correctly saved
// after being saved.
//#define TEST_BACKUP_INTEGRITY
#include <chrono>
#include <ctime> 
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/crash/auto_save.h"

#include "app/app.h"
#include "app/context.h"
#include "app/crash/log.h"
#include "app/crash/recovery_config.h"
#include "app/crash/auto_save_config.h"
#include "app/crash/session.h"
#include "app/doc.h"
#include "app/doc_access.h"
#include "app/doc_diff.h"
#include "app/pref/preferences.h"
#include "base/chrono.h"
#include "base/remove_from_container.h"
#include "base/thread.h"
#include "ui/system.h"
#include <iostream>

namespace app {

namespace crash {


namespace {

} // anonymous namespace

AutoSaver::AutoSaver(AutoSaveConfig * config,
               Session * session,
               Context* ctx)
    : m_config(config)
    , m_session(session)
    , m_ctx(ctx)
    , m_done(false)
    , m_thread ([this]{ backgroundThread(); })
{
    std::cout << "Initialized AutoSaver" << std::endl;
}

AutoSaver::~AutoSaver()
{
    std::cout << "Destroyed AutoSaver" << std::endl;
}

void AutoSaver::stop()
{
    m_done = true;
    m_wakeup.notify_one();
}

void AutoSaver::backgroundThread()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    base::this_thread::set_name("autosave");

    std::cout << "AutoSaver background task started!" << std::endl;
    std::cout << "period data: " << m_config->autoSavePeriod << std::endl; 
    int normalPeriod = int(60.0*m_config->autoSavePeriod);
    int lockedPeriod = 5;

    int waitFor = normalPeriod;

    while (!m_done) {
        m_wakeup.wait_for(lock, std::chrono::seconds(waitFor));
        auto start = std::chrono::system_clock::now();
        std::cout << "I have waited enough!!" << std::endl;
        base::Chrono chrono;
        //bool somethingLocked = false;
    }

}

} // namespace crash
} // namespace app