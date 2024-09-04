#include "ShareListenerJS.h"
namespace wrapper {
    namespace social {
        bool ShareListenerJS::onShareComplete(bool status)
        {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(status));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onShareFailed(const std::string &error) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(error));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onInviteLinkFetchComplete(const std::string &payload) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(payload));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onInviteLinkFetchError(const std::string &error) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(error));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onContextChooseComplete(const std::string& contextId) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(contextId));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onContextChooseFailed(const std::string& error) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(error));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onContextCreateComplete(const std::string& contextId) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(contextId));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onContextCreateFailed(const std::string& error) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(error));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onContextSwitchComplete() {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onContextSwitchFailed(const std::string& error) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(error));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onCustomUpdateSuccess() {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
        bool ShareListenerJS::onCustomUpdateFailed(const std::string& error) {
            RUN_ON_MAIN_THREAD_BEGIN
            MAKE_V8_HAPPY

            se::ValueArray args;
            args.push_back(se::Value(error));
            invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
    }
}

