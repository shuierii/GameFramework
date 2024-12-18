/*
 * @Author: linb
 * @Date: 2024-04-15 11:40:33
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ScriptBase } from "../Abstract/ScriptBase";
import { LogUtility } from "../Utility/LogUtility";
import { ScriptSet } from "./ScriptSet";

export class Script_Test {
    static CollectScript(): void {
        ScriptSet.mScriptClassMap = Object.assign(ScriptSet.mScriptClassMap, ScriptSet_Test);
    }
}

export module ScriptSet_Test {
    export class Script_test extends ScriptBase {
        protected OnExecute(params?: any[]) {
            let content = params[0] as string;

            LogUtility.Log(`触发测试脚本 ${content}`);
        }
    }
}