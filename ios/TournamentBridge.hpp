#import <Foundation/Foundation.h>

#if defined(__cplusplus)
extern "C" {
#endif
    void onTournamentCreateSuccess(NSString* tournamentId);
    void onTournamentCreatefailed(NSString* error);
    void onTournamentShareSuccess(NSString* tournamentId);
    void onTournamentSharefailed(NSString* error);
    void onPostTournamentScoreSuccess(NSString* tournamentId);
    void onPostTournamentScorefailed(NSString* error);
    void onTournamentsFetchComplete(NSString* tournaments);
    void onTournamentFetchComplete(NSString* tournament);
#if defined(__cplusplus)
}
#endif
