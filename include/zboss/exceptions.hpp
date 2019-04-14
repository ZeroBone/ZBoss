#ifndef ZBOSS_EXCEPTIONS_HPP
#define ZBOSS_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace zboss {

    class Exception : public std::runtime_error {

        public:

        Exception(const std::string &domain, const std::string &msg) noexcept : runtime_error("[" + domain + "] " + msg) {}

        virtual ~Exception() noexcept = default;

    };

    class InitializeException : public Exception {
        using Exception::Exception;
    };

}

#endif //ZBOSS_EXCEPTIONS_HPP