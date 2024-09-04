#include "TournamentListenerJS.h"
namespace wrapper {
    namespace social {
        bool TournamentListenerJS::onTournamentCreateSuccess(const std::string &tournamentId) {
            RUN_ON_MAIN_THREAD_BEGIN
                        MAKE_V8_HAPPY

                        se::ValueArray args;
                        args.push_back(se::Value(tournamentId));
                        invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }

        bool TournamentListenerJS::onTournamentCreatefailed(const std::string &error) {
            RUN_ON_MAIN_THREAD_BEGIN
                        MAKE_V8_HAPPY

                        se::ValueArray args;
                        args.push_back(se::Value(error));
                        invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }

        bool TournamentListenerJS::onTournamentShareSuccess(const std::string &tournamentId) {
            RUN_ON_MAIN_THREAD_BEGIN
                        MAKE_V8_HAPPY

                        se::ValueArray args;
                        args.push_back(se::Value(tournamentId));
                        invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }

        bool TournamentListenerJS::onTournamentSharefailed(const std::string &error) {
            RUN_ON_MAIN_THREAD_BEGIN
                        MAKE_V8_HAPPY

                        se::ValueArray args;
                        args.push_back(se::Value(error));
                        invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }

        bool TournamentListenerJS::onPostTournamentScoreSuccess(const std::string &tournamentId) {
            RUN_ON_MAIN_THREAD_BEGIN
                        MAKE_V8_HAPPY

                        se::ValueArray args;
                        args.push_back(se::Value(tournamentId));
                        invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }

        bool TournamentListenerJS::onPostTournamentScorefailed(const std::string &error) {
            RUN_ON_MAIN_THREAD_BEGIN
                        MAKE_V8_HAPPY

                        se::ValueArray args;
                        args.push_back(se::Value(error));
                        invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }

        bool TournamentListenerJS::onTournamentFetchComplete(const std::string &tournament) {
            RUN_ON_MAIN_THREAD_BEGIN
                        MAKE_V8_HAPPY

                        se::ValueArray args;
                        args.push_back(se::Value(tournament));
                        invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }

        bool TournamentListenerJS::onTournamentsFetchComplete(const std::string &tournaments) {
            RUN_ON_MAIN_THREAD_BEGIN
                        MAKE_V8_HAPPY

                        se::ValueArray args;
                        args.push_back(se::Value(tournaments));
                        invokeJSFun(funcName, args);

            RUN_ON_MAIN_THREAD_END

            //just return true, now
            return true;
        }
    }
}
