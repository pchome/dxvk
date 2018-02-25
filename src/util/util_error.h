#pragma once

#include <string>
#include <iostream>
#include <exception>

namespace dxvk {

  /**
   * \brief DXVK error
   *
   * A generic exception class that stores a
   * message. Exceptions should be logged.
   */
  class DxvkError {

  public:

    DxvkError() { }
    DxvkError(std::string&& message)
    : m_message(std::move(message)) {
      std::set_terminate (dxvk_terminate);
    }

    const std::string& message() const {
      return m_message;
    }

    const char * what() const {
      return m_message.c_str();
    }

    // catch terminate
    static void dxvk_terminate () {
      std::exception_ptr p = std::current_exception();

      try {
        std::rethrow_exception (p);
      } catch (DxvkError & e) {
        std::cerr << "dxvk:Uncatched exception: " << e.what() << '\n';
      }

      abort();
    }
  private:

    std::string m_message;

  };

}
