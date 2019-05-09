#ifndef ZBOSS_CALLBACK_HPP
#define ZBOSS_CALLBACK_HPP

#include <functional>

template<class T>
struct Callback;

template<class Ret, class... Params>
struct Callback<Ret(Params...)> {

    template<class... Args>
    static Ret callback(Args... args) {
        return func(args...);
    }

    static std::function<Ret(Params...)> func;

};

template<class Ret, class... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

#endif //ZBOSS_CALLBACK_HPP