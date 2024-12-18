/*
 * @Author: linb
 * @Date: 2024-11-25 17:03:42
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { LogUtility } from "../../../Utility/LogUtility";
import { E_RootBase } from "../Base/E_RootBase";
import { E_IDialogEvent } from "../Implememt/E_IDialogEvent";
import { E_IScript } from "../Implememt/E_IScript";

export class E_DialogEvent extends E_RootBase implements E_IDialogEvent {

    // 剧情
    private mCurScript: E_IScript = null;

    // 剧情脚本
    private mScriptList: Array<E_IScript> = [];

    protected InitProperty(propertyData: object): void {

    }

    protected OnReset(): void {

    }

    protected OnStart(): boolean {
        // 挑选脚本
        for (const script of this.mScriptList) {
            if (script == null)
                continue;

            this.mCurScript = script;

            break;
        }

        if (this.mCurScript == null) {
            LogUtility.Error("没有找到脚本");
            return false;
        }

        // 剧情上演
        return this.mCurScript.Play();
    }

    protected OnFinish(): void {

    }

    /**
     * @description: 设置剧情脚本列表
     * @param {Array} triggerList
     * @return {*}
     */
    SetScriptList(scriptList: Array<E_IScript>): void {
        this.mScriptList = scriptList;
    }
}