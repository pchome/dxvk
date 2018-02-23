#include "log.h"
#ifdef WANT_ENV
#include "../util_env.h"
#endif
namespace dxvk {

#ifdef WANT_LOGGER

  Logger::Logger(const std::string& file_name)
  : m_minLevel(getMinLogLevel()) {
    if (m_minLevel != LogLevel::None)
      m_fileStream = std::ofstream(getFileName(file_name));
  }


  Logger::~Logger() { }


  void Logger::trace(const std::string& message) {
    s_instance.log(LogLevel::Trace, message);
  }


  void Logger::debug(const std::string& message) {
    s_instance.log(LogLevel::Debug, message);
  }


  void Logger::info(const std::string& message) {
    s_instance.log(LogLevel::Info, message);
  }


  void Logger::warn(const std::string& message) {
    s_instance.log(LogLevel::Warn, message);
  }


  void Logger::err(const std::string& message) {
    s_instance.log(LogLevel::Error, message);
  }


  void Logger::log(LogLevel level, const std::string& message) {
    if (level >= m_minLevel) {
      std::lock_guard<std::mutex> lock(m_mutex);

      static std::array<const char*, 5> s_prefixes
        = {{ "trace: ", "debug: ", "info:  ", "warn:  ", "err:   " }};

      const char* prefix = s_prefixes.at(static_cast<uint32_t>(level));
      std::cerr    << prefix << message << std::endl;
      m_fileStream << prefix << message << std::endl;
    }
  }


  LogLevel Logger::getMinLogLevel() {
    const std::array<std::pair<const char*, LogLevel>, 6> logLevels = {{
      { "trace", LogLevel::Trace },
      { "debug", LogLevel::Debug },
      { "info",  LogLevel::Info  },
      { "warn",  LogLevel::Warn  },
      { "error", LogLevel::Error },
      { "none",  LogLevel::None  },
    }};
#ifdef WANT_ENV
    const std::string logLevelStr = env::getEnvVar(L"DXVK_LOG_LEVEL");
#else
    const std::string logLevelStr = "";
#endif

    for (const auto& pair : logLevels) {
      if (logLevelStr == pair.first)
        return pair.second;
    }

    return LogLevel::Info;
  }


  std::string Logger::getFileName(const std::string& base) {
#ifdef WANT_ENV
    std::string path = env::getEnvVar(L"DXVK_LOG_PATH");

    if (!path.empty() && *path.rbegin() != '/')
      path += '/';

    std::string exeName = env::getExeName();
    auto extp = exeName.find_last_of('.');

    if (extp != std::string::npos && exeName.substr(extp + 1) == "exe")
      exeName.erase(extp);

    path += exeName + "_" + base;

    return path;
#else
    return "dxvk_" + base;
#endif
  }
#endif // WANT_LOGGER
}
