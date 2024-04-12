/*
 * @Author: linb
 * @Date: 2024-04-11 17:55:33
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { SystemID } from "./Const/SystemID";
import { MainGame } from "./MainGame";
import { TestSystem } from "./System/TestSystem";
import { LogUtility } from "./Utility/LogUtility";

class TB_GameInstance extends UE.TS_GameInstance {
    /**
     * @description: 游戏实例初始化的时候调用
     * @return {*}
     */
    TSReceiveInit(): void {
        LogUtility.Log("--------------------------------TB_GameInstance init");

        // 注册系统
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