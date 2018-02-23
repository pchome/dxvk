#pragma once

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#ifdef WINEBUILD
#include "wine/debug.h"
#endif

namespace dxvk {

#ifdef WANT_LOGGER

  enum class LogLevel : uint32_t {
    Trace = 0,
    Debug = 1,
    Info  = 2,
    Warn  = 3,
    Error = 4,
    None  = 5,
  };

  /**
   * \brief Logger
   *
   * Logger for one DLL. Creates a text file and
   * writes all log messages to that file.
   */
  class Logger {

  public:

    Logger(const std::string& file_name);
    ~Logger();

    static void trace(const std::string& message);
    static void debug(const std::string& message);
    static void info (const std::string& message);
    static void warn (const std::string& message);
    static void err  (const std::string& message);

    static LogLevel logLevel() {
      return s_instance.m_minLevel;
    }

  private:

    static Logger s_instance;

    const LogLevel m_minLevel;

    std::mutex    m_mutex;
    std::ofstream m_fileStream;

    void log(LogLevel level, const std::string& message);

    static LogLevel getMinLogLevel();

    static std::string getFileName(
      const std::string& base);

  };

#else
#ifdef WINEBUILD

  WINE_DEFAULT_DEBUG_CHANNEL(dxvk);

  class Logger {

  public:

    Logger();
    ~Logger();

    static inline void err(const std::string& message) {
      WINE_ERR("%s\n", message.c_str());
    }

    static inline void warn(const std::string& message) {
      WINE_WARN("%s\n", message.c_str());
    }

    static inline void info(const std::string& message) {
      WINE_MESSAGE("%s\n", message.c_str());
    }

    static inline void debug(const std::string& message) {
      WINE_FIXME("%s\n", message.c_str());
    }

    static inline void trace(const std::string& message) {
      WINE_TRACE("%s\n", message.c_str());
    }

  };

#endif //WINEBUILD
#endif // WANT_LOGGER
}
