#ifndef SOCIAL_SDK_TOURNAMENT_LISTENER_JS_H
#define SOCIAL_SDK_TOURNAMENT_LISTENER_JS_H

#include "include/JSListenerBase.h"
#include "socialsdk/TournamentController.h"
#include <string>
namespace wrapper {
    namespace social {
        class TournamentListenerJS
                : public ITournamentListenerJS, public wrapper::jsbhelper::JSListenerBase {
        public:
            bool onTournamentCreateSuccess(const std::string &tournamentId);

            bool onTournamentCreatefailed(const std::string &error);

            bool onTournamentShareSuccess(const std::string &tournamentId);

            bool onTournamentSharefailed(const std::string &error);

            bool onPostTournamentScoreSuccess(const std::string &tournamentId);

            bool onPostTournamentScorefailed(const std::string &error);

            bool onTournamentsFetchComplete(const std::string &tournaments);

            bool onTournamentFetchComplete(const std::string &tournament);
        };
    }
}
#endif // SOCIAL_SDK_TOURNAMENT_LISTENER_JS_H
