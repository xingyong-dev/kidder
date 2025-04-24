//
// Created by sylar on 25-4-24.
//

#include <cstring>
#include "SignalHandler.h"
namespace nsp_signal{





    void SignalHandler::initialize(nsp_signalTime::ProcessRole role) {
        processRole_ = role;
        setupSignal(SIGHUP ,    "SIGHUP",   HandlerMethod::HM_ACTION);
        setupSignal(SIGINT ,    "SIGINT",   HandlerMethod::HM_ACTION);
        setupSignal(SIGTERM ,   "SIGTERM",  HandlerMethod::HM_ACTION);
        setupSignal(SIGCHLD ,   "SIGCHLD",  HandlerMethod::HM_ACTION);
        setupSignal(SIGQUIT ,   "SIGQUIT",  HandlerMethod::HM_ACTION);
        setupSignal(SIGIO,      "SIGIO",    HandlerMethod::HM_ACTION);
        setupSignal(SIGPIPE,    "SIGPIPE",  HandlerMethod::HM_IGNORE);
        setupSignal(SIGSYS ,    "SIGSYS",   HandlerMethod::HM_IGNORE);

    }

    void SignalHandler::setupSignal(int signo, const std::string &name, HandlerMethod method) {
        struct sigaction sa{};
        if(method == HandlerMethod::HM_UNKNOWN || method == HandlerMethod::HM_IGNORE)
        {
            sa.sa_handler = SIG_IGN;
        } else{
            sa.sa_sigaction = handleSignal;
            sa.sa_flags = SA_SIGINFO;
        }
        sigemptyset(&sa.sa_mask);

        if(sigaction(signo, &sa, nullptr) == -1) //注册信号处理函数
        {
            spdlog::error("sigaction({}) failed: {}", name, std::strerror(errno));

        }else{
            signalNames_[signo] = name;
            spdlog::info("Registered signal handler for {}", name);
        }
    }

    void SignalHandler::handleSignal(int signo, siginfo_t *info, void *context) {
        auto it = signalNames_.find(signo);
        std::string signame = (it != signalNames_.end()) ? it->second : "UNKNOWN";
        if(info && info->si_pid){
            spdlog::info("Received signal {} ({}), from PID {}", signo, signame, info->si_pid);
        }else {
            spdlog::info("Received signal {} ({})", signo, signame);
        }
        if (signo == SIGCHLD) {
            handleChildStatus();
        }
    }

    void SignalHandler::handleChildStatus() {
        int status;
        pid_t pid;
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
            if (WIFSIGNALED(status)) {
                spdlog::warn("Child {} terminated by signal {}", pid, WTERMSIG(status));
            } else {
                spdlog::info("Child {} exited with status {}", pid, WEXITSTATUS(status));
            }
        }
        if (pid == -1 && errno != ECHILD) {
            spdlog::error("waitpid() failed: {}", std::strerror(errno));
        }
    }


}

