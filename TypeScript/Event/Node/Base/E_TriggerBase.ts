/*
 * @Author: linb
 * @Date: 2024-10-31 19:07:35
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { SystemID } from "../../../Const/SystemID";
import { IEventSystem } from "../../../System/Event/IEventSystem";
import { E_ITrigger } from "../Implememt/E_ITrigger";
import { E_NodeBase } from "./E_NodeBase";

export abstract class E_TriggerBase extends E_NodeBase implements E_ITrigger {

    // 初始化节点携带属性
    protected abstract OnInitProperty(nodeData: object): void;
    protected abstract OnTrigger(args: any): void;

    protected OnInit(nodeData: object): void {
        this.OnInitProperty(nodeData);
    }

    protected TryExecuteEvent(): boolean {
        // 前置条件判断

        let eventSys = this.GetSystem<IEventSystem>(SystemID.EVENT_SYSTEM);

        let event = this.GetRootNode();
        if (event == null)
            return false;

        let eventID = event.GetID();

        // 开始执行
        eventSys.ExecuteEvent(eventID);

        return true;
    }
}