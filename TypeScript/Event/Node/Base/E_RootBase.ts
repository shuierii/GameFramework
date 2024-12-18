/*
 * @Author: linb
 * @Date: 2024-11-25 17:00:39
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_IRoot } from "../Implememt/E_IRoot";
import { E_ITrigger } from "../Implememt/E_ITrigger";
import { E_NodeBase } from "./E_NodeBase";

export abstract class E_RootBase extends E_NodeBase implements E_IRoot {

    // 事件名称
    private mFileName: string = "";

    // 事件ID
    private mID: number = 0;

    // 简介
    private mMemo: string = "";

    // 触发器列表
    private mTriggerList: Array<E_ITrigger> = [];

    protected abstract InitProperty(propertyData: object): void;
    protected abstract OnStart(): boolean;
    protected abstract OnFinish(): void;

    //#region 父接口

    protected OnInit(nodeData: object): void {
        this.mFileName = nodeData["name"] as string;
        this.mID = nodeData["id"] as number;
        this.mMemo = nodeData["memo"] as string;

        let propertyData = nodeData["properties"];
        if (propertyData == null)
            return;

        this.InitProperty(propertyData);
    }

    protected OnRelease(): void {

    }

    //#endregion 父接口END

    GetID(): number {
        return this.mID;
    }

    GetFileName(): string {
        return this.mFileName;
    }

    GetTriggerList(): Array<E_ITrigger> {
        return this.mTriggerList;
    }

    /**
     * @description: 设置触发器列表
     * @param {Array} triggerList
     * @return {*}
     */
    SetTriggerList(triggerList: Array<E_ITrigger>): void {
        if (triggerList == null || triggerList.length <= 0)
            return;

        this.mTriggerList = triggerList;
    }

    Start(): boolean {
        return this.OnStart();
    }

    Finish(): void {
        this.OnFinish();
    }
}