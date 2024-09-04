
#ifndef SOCIAL_SDK_TOURNAMENT_CONTROLLER_H
#define SOCIAL_SDK_TOURNAMENT_CONTROLLER_H

#include <memory>
#include <string>
#include "socialsdk/ITournamentListenerJS.h"
namespace wrapper {
    namespace social {

        class TournamentController {
        public:
            static void init() {
                _instance.reset(new TournamentController());
            }

            static TournamentController *getInstance() {
                return _instance.get();
            }

            TournamentController();

            ~TournamentController();

            ITournamentListenerJS *getListener() {
                return _listener.get();
            };

            void setListener(ITournamentListenerJS *listener) {
                _listener.reset(listener);
            }

            void
            createTournament(const int initialScore, const std::string &title, const int endTime,
                             const std::string &scoreType, const std::string &image,
                             const std::string &sortOrder, const std::string &data);

            void shareTournament(const int initialScore, const std::string &tournamentId);

            void postTournamentScore(const int score, const std::string &tournamentId);

            void getTournament();

            void getTournaments();

        private:
            std::unique_ptr<ITournamentListenerJS> _listener;
            static std::unique_ptr<TournamentController> _instance;
        };
    }
}
#endif /* SOCIAL_SDK_TOURNAMENT_CONTROLLER_H */
