#include "bindings/auto/2.x/jsb_social_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "socialsdk/NativeShare.h"
#include "socialsdk/TournamentController.h"
#include "socialsdk/ScheduledNotification.h"

se::Object* __jsb_NativeShare_proto = nullptr;
se::Class* __jsb_NativeShare_class = nullptr;

static bool js_social_NativeShare_createContext(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_createContext : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_social_NativeShare_createContext : Error processing arguments");
        cobj->createContext(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_createContext)

static bool js_social_NativeShare_updateAsync(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_updateAsync : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        ok &= seval_to_std_string(args[2], &arg2);
        ok &= seval_to_std_string(args[3], &arg3);
        SE_PRECONDITION2(ok, false, "js_social_NativeShare_updateAsync : Error processing arguments");
        cobj->updateAsync(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_updateAsync)

static bool js_social_NativeShare_shareImage(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_shareImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        AuthMethod arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        ok &= seval_to_std_string(args[2], &arg2);
        ok &= seval_to_std_string(args[3], &arg3);
        SE_PRECONDITION2(ok, false, "js_social_NativeShare_shareImage : Error processing arguments");
        cobj->shareImage(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_shareImage)

static bool js_social_NativeShare_getEntryPointData(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_getEntryPointData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->getEntryPointData();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_getEntryPointData)

static bool js_social_NativeShare_setListener(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_setListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        IShareListenerJS* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_social_NativeShare_setListener : Error processing arguments");
        cobj->setListener(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_setListener)

static bool js_social_NativeShare_switchContext(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_switchContext : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_social_NativeShare_switchContext : Error processing arguments");
        cobj->switchContext(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_switchContext)

static bool js_social_NativeShare_inviteAsync(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_inviteAsync : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->inviteAsync();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_inviteAsync)

static bool js_social_NativeShare_shareLink(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_shareLink : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        AuthMethod arg0;
        std::string arg1;
        std::string arg2;
        ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        ok &= seval_to_std_string(args[2], &arg2);
        SE_PRECONDITION2(ok, false, "js_social_NativeShare_shareLink : Error processing arguments");
        cobj->shareLink(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_shareLink)

static bool js_social_NativeShare_chooseContext(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_chooseContext : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->chooseContext();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_chooseContext)

static bool js_social_NativeShare_getListener(se::State& s)
{
    NativeShare* cobj = (NativeShare*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_NativeShare_getListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        IShareListenerJS* result = cobj->getListener();
        ok &= native_ptr_to_seval<IShareListenerJS>((IShareListenerJS*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_social_NativeShare_getListener : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_getListener)

static bool js_social_NativeShare_init(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        NativeShare::init();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_init)

static bool js_social_NativeShare_getInstance(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        NativeShare* result = NativeShare::getInstance();
        ok &= native_ptr_to_seval<NativeShare>((NativeShare*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_social_NativeShare_getInstance : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_NativeShare_getInstance)

SE_DECLARE_FINALIZE_FUNC(js_NativeShare_finalize)

static bool js_social_NativeShare_constructor(se::State& s)
{
    NativeShare* cobj = new (std::nothrow) NativeShare();
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_social_NativeShare_constructor, __jsb_NativeShare_class, js_NativeShare_finalize)




static bool js_NativeShare_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (NativeShare)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        NativeShare* cobj = (NativeShare*)s.nativeThisObject();
        delete cobj;
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_NativeShare_finalize)

bool js_register_social_NativeShare(se::Object* obj)
{
    auto cls = se::Class::create("NativeShare", obj, nullptr, _SE(js_social_NativeShare_constructor));

    cls->defineFunction("createContext", _SE(js_social_NativeShare_createContext));
    cls->defineFunction("updateAsync", _SE(js_social_NativeShare_updateAsync));
    cls->defineFunction("shareImage", _SE(js_social_NativeShare_shareImage));
    cls->defineFunction("getEntryPointData", _SE(js_social_NativeShare_getEntryPointData));
    cls->defineFunction("setListener", _SE(js_social_NativeShare_setListener));
    cls->defineFunction("switchContext", _SE(js_social_NativeShare_switchContext));
    cls->defineFunction("inviteAsync", _SE(js_social_NativeShare_inviteAsync));
    cls->defineFunction("shareLink", _SE(js_social_NativeShare_shareLink));
    cls->defineFunction("chooseContext", _SE(js_social_NativeShare_chooseContext));
    cls->defineFunction("getListener", _SE(js_social_NativeShare_getListener));
    cls->defineStaticFunction("init", _SE(js_social_NativeShare_init));
    cls->defineStaticFunction("getInstance", _SE(js_social_NativeShare_getInstance));
    cls->defineFinalizeFunction(_SE(js_NativeShare_finalize));
    cls->install();
    JSBClassType::registerClass<NativeShare>(cls);

    __jsb_NativeShare_proto = cls->getProto();
    __jsb_NativeShare_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_TournamentController_proto = nullptr;
se::Class* __jsb_TournamentController_class = nullptr;

static bool js_social_TournamentController_shareTournament(se::State& s)
{
    TournamentController* cobj = (TournamentController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_TournamentController_shareTournament : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        int arg0 = 0;
        std::string arg1;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_social_TournamentController_shareTournament : Error processing arguments");
        cobj->shareTournament(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_social_TournamentController_shareTournament)

static bool js_social_TournamentController_getTournament(se::State& s)
{
    TournamentController* cobj = (TournamentController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_TournamentController_getTournament : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->getTournament();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_TournamentController_getTournament)

static bool js_social_TournamentController_getTournaments(se::State& s)
{
    TournamentController* cobj = (TournamentController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_TournamentController_getTournaments : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->getTournaments();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_TournamentController_getTournaments)

static bool js_social_TournamentController_setListener(se::State& s)
{
    TournamentController* cobj = (TournamentController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_TournamentController_setListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        ITournamentListenerJS* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_social_TournamentController_setListener : Error processing arguments");
        cobj->setListener(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_social_TournamentController_setListener)

static bool js_social_TournamentController_postTournamentScore(se::State& s)
{
    TournamentController* cobj = (TournamentController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_TournamentController_postTournamentScore : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        int arg0 = 0;
        std::string arg1;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_social_TournamentController_postTournamentScore : Error processing arguments");
        cobj->postTournamentScore(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_social_TournamentController_postTournamentScore)

static bool js_social_TournamentController_createTournament(se::State& s)
{
    TournamentController* cobj = (TournamentController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_TournamentController_createTournament : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 7) {
        int arg0 = 0;
        std::string arg1;
        int arg2 = 0;
        std::string arg3;
        std::string arg4;
        std::string arg5;
        std::string arg6;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        ok &= seval_to_int32(args[2], (int32_t*)&arg2);
        ok &= seval_to_std_string(args[3], &arg3);
        ok &= seval_to_std_string(args[4], &arg4);
        ok &= seval_to_std_string(args[5], &arg5);
        ok &= seval_to_std_string(args[6], &arg6);
        SE_PRECONDITION2(ok, false, "js_social_TournamentController_createTournament : Error processing arguments");
        cobj->createTournament(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 7);
    return false;
}
SE_BIND_FUNC(js_social_TournamentController_createTournament)

static bool js_social_TournamentController_getListener(se::State& s)
{
    TournamentController* cobj = (TournamentController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_social_TournamentController_getListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        ITournamentListenerJS* result = cobj->getListener();
        ok &= native_ptr_to_seval<ITournamentListenerJS>((ITournamentListenerJS*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_social_TournamentController_getListener : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_TournamentController_getListener)

SE_DECLARE_FINALIZE_FUNC(js_TournamentController_finalize)

static bool js_social_TournamentController_constructor(se::State& s)
{
    TournamentController* cobj = new (std::nothrow) TournamentController();
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_social_TournamentController_constructor, __jsb_TournamentController_class, js_TournamentController_finalize)




static bool js_TournamentController_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (TournamentController)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        TournamentController* cobj = (TournamentController*)s.nativeThisObject();
        delete cobj;
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_TournamentController_finalize)

bool js_register_social_TournamentController(se::Object* obj)
{
    auto cls = se::Class::create("TournamentController", obj, nullptr, _SE(js_social_TournamentController_constructor));

    cls->defineFunction("shareTournament", _SE(js_social_TournamentController_shareTournament));
    cls->defineFunction("getTournament", _SE(js_social_TournamentController_getTournament));
    cls->defineFunction("getTournaments", _SE(js_social_TournamentController_getTournaments));
    cls->defineFunction("setListener", _SE(js_social_TournamentController_setListener));
    cls->defineFunction("postTournamentScore", _SE(js_social_TournamentController_postTournamentScore));
    cls->defineFunction("createTournament", _SE(js_social_TournamentController_createTournament));
    cls->defineFunction("getListener", _SE(js_social_TournamentController_getListener));
    cls->defineFinalizeFunction(_SE(js_TournamentController_finalize));
    cls->install();
    JSBClassType::registerClass<TournamentController>(cls);

    __jsb_TournamentController_proto = cls->getProto();
    __jsb_TournamentController_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_ScheduledNotification_proto = nullptr;
se::Class* __jsb_ScheduledNotification_class = nullptr;

static bool js_social_ScheduledNotification_requestAuth(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        ScheduledNotification::requestAuth();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_ScheduledNotification_requestAuth)

static bool js_social_ScheduledNotification_show(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 9) {
        int arg0 = 0;
        int arg1 = 0;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        int arg5 = 0;
        int arg6 = 0;
        bool arg7;
        std::string arg8;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        ok &= seval_to_int32(args[1], (int32_t*)&arg1);
        ok &= seval_to_std_string(args[2], &arg2);
        ok &= seval_to_std_string(args[3], &arg3);
        ok &= seval_to_std_string(args[4], &arg4);
        ok &= seval_to_int32(args[5], (int32_t*)&arg5);
        ok &= seval_to_int32(args[6], (int32_t*)&arg6);
        ok &= seval_to_boolean(args[7], &arg7);
        ok &= seval_to_std_string(args[8], &arg8);
        SE_PRECONDITION2(ok, false, "js_social_ScheduledNotification_show : Error processing arguments");
        ScheduledNotification::show(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 9);
    return false;
}
SE_BIND_FUNC(js_social_ScheduledNotification_show)

static bool js_social_ScheduledNotification_cancelAll(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        ScheduledNotification::cancelAll();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_ScheduledNotification_cancelAll)

static bool js_social_ScheduledNotification_cancel(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 7) {
        int arg0 = 0;
        int arg1 = 0;
        std::string arg2;
        std::string arg3;
        int arg4 = 0;
        std::string arg5;
        std::string arg6;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        ok &= seval_to_int32(args[1], (int32_t*)&arg1);
        ok &= seval_to_std_string(args[2], &arg2);
        ok &= seval_to_std_string(args[3], &arg3);
        ok &= seval_to_int32(args[4], (int32_t*)&arg4);
        ok &= seval_to_std_string(args[5], &arg5);
        ok &= seval_to_std_string(args[6], &arg6);
        SE_PRECONDITION2(ok, false, "js_social_ScheduledNotification_cancel : Error processing arguments");
        ScheduledNotification::cancel(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 7);
    return false;
}
SE_BIND_FUNC(js_social_ScheduledNotification_cancel)

static bool js_social_ScheduledNotification_requestGranted(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = ScheduledNotification::requestGranted();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_social_ScheduledNotification_requestGranted : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_social_ScheduledNotification_requestGranted)



static bool js_ScheduledNotification_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (ScheduledNotification)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        ScheduledNotification* cobj = (ScheduledNotification*)s.nativeThisObject();
        delete cobj;
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_ScheduledNotification_finalize)

bool js_register_social_ScheduledNotification(se::Object* obj)
{
    auto cls = se::Class::create("ScheduledNotification", obj, nullptr, nullptr);

    cls->defineStaticFunction("requestAuth", _SE(js_social_ScheduledNotification_requestAuth));
    cls->defineStaticFunction("show", _SE(js_social_ScheduledNotification_show));
    cls->defineStaticFunction("cancelAll", _SE(js_social_ScheduledNotification_cancelAll));
    cls->defineStaticFunction("cancel", _SE(js_social_ScheduledNotification_cancel));
    cls->defineStaticFunction("requestGranted", _SE(js_social_ScheduledNotification_requestGranted));
    cls->defineFinalizeFunction(_SE(js_ScheduledNotification_finalize));
    cls->install();
    JSBClassType::registerClass<ScheduledNotification>(cls);

    __jsb_ScheduledNotification_proto = cls->getProto();
    __jsb_ScheduledNotification_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_social(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("social", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("social", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_social_TournamentController(ns);
    js_register_social_NativeShare(ns);
    js_register_social_ScheduledNotification(ns);
    return true;
}

