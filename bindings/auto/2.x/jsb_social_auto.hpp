#pragma once
#include "base/ccConfig.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

extern se::Object* __jsb_NativeShare_proto;
extern se::Class* __jsb_NativeShare_class;

bool js_register_NativeShare(se::Object* obj);
bool register_all_social(se::Object* obj);
SE_DECLARE_FUNC(js_social_NativeShare_createContext);
SE_DECLARE_FUNC(js_social_NativeShare_updateAsync);
SE_DECLARE_FUNC(js_social_NativeShare_shareImage);
SE_DECLARE_FUNC(js_social_NativeShare_getEntryPointData);
SE_DECLARE_FUNC(js_social_NativeShare_setListener);
SE_DECLARE_FUNC(js_social_NativeShare_switchContext);
SE_DECLARE_FUNC(js_social_NativeShare_inviteAsync);
SE_DECLARE_FUNC(js_social_NativeShare_shareLink);
SE_DECLARE_FUNC(js_social_NativeShare_chooseContext);
SE_DECLARE_FUNC(js_social_NativeShare_getListener);
SE_DECLARE_FUNC(js_social_NativeShare_init);
SE_DECLARE_FUNC(js_social_NativeShare_getInstance);
SE_DECLARE_FUNC(js_social_NativeShare_NativeShare);

extern se::Object* __jsb_TournamentController_proto;
extern se::Class* __jsb_TournamentController_class;

bool js_register_TournamentController(se::Object* obj);
bool register_all_social(se::Object* obj);
SE_DECLARE_FUNC(js_social_TournamentController_shareTournament);
SE_DECLARE_FUNC(js_social_TournamentController_getTournament);
SE_DECLARE_FUNC(js_social_TournamentController_getTournaments);
SE_DECLARE_FUNC(js_social_TournamentController_setListener);
SE_DECLARE_FUNC(js_social_TournamentController_postTournamentScore);
SE_DECLARE_FUNC(js_social_TournamentController_createTournament);
SE_DECLARE_FUNC(js_social_TournamentController_getListener);
SE_DECLARE_FUNC(js_social_TournamentController_TournamentController);

extern se::Object* __jsb_ScheduledNotification_proto;
extern se::Class* __jsb_ScheduledNotification_class;

bool js_register_ScheduledNotification(se::Object* obj);
bool register_all_social(se::Object* obj);
SE_DECLARE_FUNC(js_social_ScheduledNotification_requestAuth);
SE_DECLARE_FUNC(js_social_ScheduledNotification_show);
SE_DECLARE_FUNC(js_social_ScheduledNotification_cancelAll);
SE_DECLARE_FUNC(js_social_ScheduledNotification_cancel);
SE_DECLARE_FUNC(js_social_ScheduledNotification_requestGranted);

