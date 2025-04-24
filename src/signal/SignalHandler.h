//
// Created by sylar on 25-4-24.
//
#pragma once

#include <csignal>
#include <string>
#include <vector>
#include <unordered_map>
#ifndef KIDDER_SIGNALHANDLER_H
#define KIDDER_SIGNALHANDLER_H
namespace nsp_signalTime
{
    enum class ProcessRole{
        Master,
        Worker,
        Other,
    };
}

namespace nsp_signal {

    enum class HandlerMethod
    {
        HM_UNKNOWN ,
        HM_IGNORE,
        HM_ACTION,
    };
    class SignalHandler {
    public:
    static void initialize(nsp_signalTime::ProcessRole role);
    private:
        static void setupSignal(int signo, const std::string& name, HandlerMethod method);
        static void handleSignal(int signo, siginfo_t* info, void* context);
        static void handleChildStatus();
        static nsp_signalTime::ProcessRole processRole_;
        static std::unordered_map<int, std::string> signalNames_;
        SignalHandler()=delete;
    };
}
#endif //KIDDER_SIGNALHANDLER_H
//navigate