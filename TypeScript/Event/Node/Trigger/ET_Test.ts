/*
 * @Author: linb
 * @Date: 2024-11-27 11:25:06
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { Event_Test } from "../../../Const/EventID";
import { E_TriggerBase } from "../Base/E_TriggerBase";

export class ET_Test extends E_TriggerBase {

    protected OnInitProperty(nodeData: object): void {
        this.RegisterEvent(this.mCookie, Event_Test.EVENT_TRIGGER_DIALOG, this.OnTrigger.bind(this));
    }

    protected OnReset(): void {

    }

    protected OnRelease(): void {

    }

    protected OnTrigger(args: any): void {
        this.TryExecuteEvent();
    }
}