#include "socialsdk/TournamentController.h"

#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
using namespace cc;
#else
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
#endif
namespace wrapper {
    namespace social {

        std::unique_ptr<TournamentController> TournamentController::_instance;

        TournamentController::TournamentController() {}

        TournamentController::~TournamentController() = default;

        void TournamentController::createTournament(const int initialScore,
                                                    const std::string &title,
                                                    const int endTime,
                                                    const std::string &scoreType,
                                                    const std::string &image,
                                                    const std::string &sortOrder,
                                                    const std::string &data) {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/tournaments/TournamentController",
                    "createTournament", (jint) initialScore, title, (jint) endTime, scoreType,
                    image, sortOrder, data);
        }

        void TournamentController::shareTournament(const int initialScore,
                                                   const std::string &tournamentId) {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/tournaments/TournamentController",
                    "shareTournament", (jint) initialScore, tournamentId);
        }

        void TournamentController::getTournaments() {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/tournaments/TournamentController",
                    "getTournaments");
        }

        void TournamentController::getTournament() {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/tournaments/TournamentController",
                    "getTournament");
        }

        void TournamentController::postTournamentScore(const int score,
                                                       const std::string &tournamentId) {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/tournaments/TournamentController",
                    "postTournamentScore", (jint) score, tournamentId);
        }

        extern "C" {
        JNIEXPORT void JNICALL
        Java_com_wrapper_social_tournaments_TournamentController_onTournamentCreateSuccess(
                JNIEnv *env, jobject thiz, jstring tournament_id) {
            TournamentController::getInstance()->getListener()->onTournamentCreateSuccess(
                    JniHelper::jstring2string(tournament_id));
        }

        JNIEXPORT void JNICALL
        Java_com_wrapper_social_tournaments_TournamentController_onTournamentCreatefailed(
                JNIEnv *env, jobject thiz, jstring error) {
            TournamentController::getInstance()->getListener()->onTournamentCreatefailed(
                    JniHelper::jstring2string(error));
        }

        JNIEXPORT void JNICALL
        Java_com_wrapper_social_tournaments_TournamentController_onTournamentShareSuccess(
                JNIEnv *env, jobject thiz, jstring tournament_id) {
            TournamentController::getInstance()->getListener()->onTournamentShareSuccess(
                    JniHelper::jstring2string(tournament_id));
        }

        JNIEXPORT void JNICALL
        Java_com_wrapper_social_tournaments_TournamentController_onTournamentSharefailed(
                JNIEnv *env, jobject thiz, jstring error) {
            TournamentController::getInstance()->getListener()->onTournamentSharefailed(
                    JniHelper::jstring2string(error));
        }

        JNIEXPORT void JNICALL
        Java_com_wrapper_social_tournaments_TournamentController_onPostTournamentScoreSuccess(
                JNIEnv *env, jobject thiz, jstring tournament_id) {
            TournamentController::getInstance()->getListener()->onPostTournamentScoreSuccess(
                    JniHelper::jstring2string(tournament_id));
        }

        JNIEXPORT void JNICALL
        Java_com_wrapper_social_tournaments_TournamentController_onPostTournamentScorefailed(
                JNIEnv *env, jobject thiz, jstring error) {
            TournamentController::getInstance()->getListener()->onPostTournamentScorefailed(
                    JniHelper::jstring2string(error));
        }
        JNIEXPORT void JNICALL
        Java_com_wrapper_social_tournaments_TournamentController_onTournamentsFetchComplete(
                JNIEnv *env, jobject thiz, jstring tournaments) {
            TournamentController::getInstance()->getListener()->onTournamentsFetchComplete(
                    JniHelper::jstring2string(tournaments));
        }
        JNIEXPORT void JNICALL
        Java_com_wrapper_social_tournaments_TournamentController_onTournamentFetchComplete(
                JNIEnv *env, jobject thiz, jstring tournament) {
            TournamentController::getInstance()->getListener()->onTournamentFetchComplete(
                    JniHelper::jstring2string(tournament));
        }
        }
    }
}