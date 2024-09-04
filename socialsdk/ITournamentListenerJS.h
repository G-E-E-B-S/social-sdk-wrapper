#ifndef SOCIAL_SDK_ITOURNAMENTLISTENERJS_H
#define SOCIAL_SDK_ITOURNAMENTLISTENERJS_H
#include <string>
namespace wrapper {
    namespace social {
        class ITournamentListenerJS {
        public:
            virtual ~ITournamentListenerJS() {}
            virtual bool onTournamentCreateSuccess(const std::string& tournamentId) = 0;
            virtual bool onTournamentCreatefailed(const std::string& error) = 0;
            virtual bool onTournamentShareSuccess(const std::string& tournamentId) = 0;
            virtual bool onTournamentSharefailed(const std::string& error) = 0;
            virtual bool onPostTournamentScoreSuccess(const std::string& tournamentId) = 0;
            virtual bool onPostTournamentScorefailed(const std::string& error) = 0;
            virtual bool onTournamentsFetchComplete(const std::string& tournaments) = 0;
            virtual bool onTournamentFetchComplete(const std::string& tournament) = 0;
        };
    }
}
#endif //SOCIAL_SDK_ITOURNAMENTLISTENERJS_H