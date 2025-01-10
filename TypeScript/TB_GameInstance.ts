/*
 * @Author: linb
 * @Date: 2024-04-11 17:55:33
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { ModelID } from "./Const/ModelID";
import { SystemID } from "./Const/SystemID";
import { MainGame } from "./MainGame";
import { EntityModel } from "./Model/Entity/EntityModel";
import { EventModel } from "./Model/Event/EventModel";
import { PlayerModel } from "./Model/Player/PlayerModel";
import { TestModel } from "./Model/TestModel";
import { EntitySystem } from "./System/Entity/EntitySystem";
import { EventSystem } from "./System/Event/EventSystem";
import { PlayerSystem } from "./System/Player/PlayerSystem";
import { TestEventSystem } from "./System/TestEventSystem";
import { TestSystem } from "./System/TestSystem";
import { UISystem } from "./System/UI/UISystem";
import { LogUtility } from "./Utility/LogUtility";

class TB_GameInstance extends UE.TS_GameInstance {
    /**
     * @description: 游戏实例初始化的时候调用
     * @return {*}
     */
    TSReceiveInit(): void {
        LogUtility.Log("--------------------------------TB_GameInstance init");

        MainGame.UEInstance = this;

        // 注册数据模型
        MainGame.Instance.BindModel(ModelID.ENTITY_MODEL, EntityModel);
        MainGame.Instance.BindModel(ModelID.TEST_MODEL, TestModel);
        MainGame.Instance.BindModel(ModelID.PLAYER_MODEL, PlayerModel);
        MainGame.Instance.BindModel(ModelID.EVENT_MODEL, EventModel);

        // 注册系统，需要考虑顺序，因为有初始化的加载顺序
        MainGame.Instance.BindSystem(SystemID.ENTITY_SYSTEM, EntitySystem);
        MainGame.Instance.BindSystem(SystemID.PLAYER_SYSTEM, PlayerSystem);
        MainGame.Instance.BindSystem(SystemID.EVENT_SYSTEM, EventSystem);
        MainGame.Instance.BindSystem(SystemID.UI_SYSTEM, UISystem);
        MainGame.Instance.BindSystem(SystemID.TEST_EVENT_SYSTEM, TestEventSystem);
        MainGame.Instance.BindSystem(SystemID.TEST_SYSTEM, TestSystem);

        // 初始化
        MainGame.Instance.Init();
    }

    TSReceiveShutdown(): void {
        LogUtility.Log("--------------------------------TB_GameInstance shutdown");

        // 释放
        MainGame.Instance.Release();
    }
}
export default TB_GameInstance