#include "bindings/manual/SocialJSHelper.h"
#include "bindings/manual/TournamentListenerJS.h"
#include "socialsdk/TournamentController.h"
#include "bindings/manual/ShareListenerJS.h"
#include "socialsdk/NativeShare.h"
using namespace wrapper::social;
static bool js_SocialJS_setTournamentListener(se::State& s)
{
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc == 1)
    {
        static TournamentListenerJS* tournamentListener = nullptr;
        if (!tournamentListener) {
            tournamentListener = new (std::nothrow) TournamentListenerJS();
            TournamentController::getInstance()->setListener(tournamentListener);
        }
        tournamentListener->setJSDelegate(args[0]);

        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_SocialJS_setTournamentListener)
static bool js_SocialJS_getTournamentController(se::State& s)
{
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc == 0)
    {
        static TournamentController* nativeController = TournamentController::getInstance();
        if (!nativeController) {
            TournamentController::init();
            nativeController = TournamentController::getInstance();
        }
        auto ok = native_ptr_to_seval<TournamentController>((TournamentController*)nativeController, &s.rval());
        SE_PRECONDITION2(ok, false, "js_SocialJS_getTournamentController : Error processing arguments");
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
SE_BIND_FUNC(js_SocialJS_getTournamentController)
static bool js_SocialJS_setShareListener(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc == 1)
    {
        static ShareListenerJS* shareListener = nullptr;
        if (!shareListener) {
            shareListener = new (std::nothrow) ShareListenerJS();
            NativeShare::getInstance()->setListener(shareListener);
        }
        shareListener->setJSDelegate(args[0]);

        return true;
    }

    SE_REPORT_ERROR("js_SocialJS_setShareListener: wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_SocialJS_setShareListener)
static bool js_SocialJS_getSharer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc == 0)
    {
        static NativeShare* nativeController = NativeShare::getInstance();
        if (!nativeController) {
            NativeShare::init();
            nativeController = NativeShare::getInstance();
        }
        auto ok = native_ptr_to_seval<NativeShare>((NativeShare*)nativeController, &s.rval());
        SE_PRECONDITION2(ok, false, "js_SocialJS_getSharer : Error processing arguments");
        return true;
    }

    SE_REPORT_ERROR("js_SocialJS_getSharer: wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
SE_BIND_FUNC(js_SocialJS_getSharer)

bool register_all_social_JS_helper(se::Object* obj)
{
    auto pluginValue = wrapper::jsbhelper::getPluginValue(obj, "social");
    auto plugin = pluginValue.toObject();
    plugin->defineFunction("setTournamentListener", _SE(js_SocialJS_setTournamentListener));
    plugin->defineFunction("getTournamentController", _SE(js_SocialJS_getTournamentController));
    plugin->defineFunction("setShareListener", _SE(js_SocialJS_setShareListener));
    plugin->defineFunction("getSharer", _SE(js_SocialJS_getSharer));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

