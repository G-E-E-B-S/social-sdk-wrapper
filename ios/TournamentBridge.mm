#include "TournamentBridge.hpp"
#include "TournamentController.h"
using namespace wrapper::social;

void onTournamentCreateSuccess(NSString* tournamentId) {
    TournamentController::getInstance()->getListener()->onTournamentCreateSuccess([tournamentId UTF8String]);
}
void onTournamentCreatefailed(NSString* error) {
    TournamentController::getInstance()->getListener()->onTournamentCreatefailed([error UTF8String]);
}
void onTournamentShareSuccess(NSString* tournamentId) {
    TournamentController::getInstance()->getListener()->onTournamentShareSuccess([tournamentId UTF8String]);
}
void onTournamentSharefailed(NSString* error) {
    TournamentController::getInstance()->getListener()->onTournamentSharefailed([error UTF8String]);
}
void onPostTournamentScoreSuccess(NSString* tournamentId) {
    TournamentController::getInstance()->getListener()->onPostTournamentScoreSuccess([tournamentId UTF8String]);
}
void onPostTournamentScorefailed(NSString* error) {
    TournamentController::getInstance()->getListener()->onPostTournamentScorefailed([error UTF8String]);
}
void onTournamentsFetchComplete(NSString* tournaments) {
    TournamentController::getInstance()->getListener()->onTournamentsFetchComplete([tournaments UTF8String]);
}
void onTournamentFetchComplete(NSString* tournament) {
    TournamentController::getInstance()->getListener()->onTournamentFetchComplete([tournament UTF8String]);
}
