#include "TournamentController.h"
#import <social_sdk/social_sdk-Swift.h>
#import <UIKit/UIKit.h>
namespace wrapper {
    namespace social {
        namespace {
            TournamentDelegate* s_delegate = nil;
        }
        void onTournamentCreateSuccess(NSString* tournamentId) {
            
        }
        std::unique_ptr<TournamentController> TournamentController::_instance;
        TournamentController::TournamentController() {
            if (s_delegate == nil) {
                s_delegate = [[TournamentDelegate alloc] init];
            }
        }
        TournamentController::~TournamentController() = default;
        void TournamentController::createTournament(const int initialScore, const std::string& title, const int endTime, const std::string& scoreType, const std::string& imagePath, const std::string& sortOrder, const std::string& data) {
            TournamentParams* params = [[TournamentParams alloc] init];
            if (title.size()) {
                params.title = [NSString stringWithUTF8String:title.c_str()];
            }
            if (endTime) {
                params.endTime = [NSDate dateWithTimeIntervalSince1970:endTime/1000];
            }
            if (scoreType.size()) {
                params.scoreType = [NSString stringWithUTF8String:scoreType.c_str()];
            }
            if (sortOrder.size()) {
                params.sortOrder = [NSString stringWithUTF8String:sortOrder.c_str()];
            }
            if (imagePath.size()) {
                params.image = [[UIImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:imagePath.c_str()]];
            }
            if (data.size()) {
                params.paylod = [NSString stringWithUTF8String:data.c_str()];
            }
            [s_delegate createTournamentWithTournamentParams:params];
        }
        void TournamentController::shareTournament(const int initialScore, const std::string &tournamentId) {
            [s_delegate shareTournamentWithInitialScore:initialScore tournamentId:[NSString stringWithUTF8String:tournamentId.c_str()]];
        }
        void TournamentController::postTournamentScore(const int score, const std::string &tournamentId) {
            [s_delegate postTournamentScoreWithScore:score tournamentId:[NSString stringWithUTF8String:tournamentId.c_str()]];
        }
        void TournamentController::getTournaments() {
            [s_delegate fetchTournaments];
        }
        void TournamentController::getTournament() {
            getListener()->onTournamentFetchComplete("");
        }
    }
}
