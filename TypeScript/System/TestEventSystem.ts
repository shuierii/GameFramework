/*
 * @Author: linb
 * @Date: 2024-04-15 10:40:00
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { SystemBase } from "../Abstract/SystemBase";
import { EventID } from "../Const/EventID";
import { SystemID } from "../Const/SystemID";
import { LogUtility } from "../Utility/LogUtility";

export class TestEventSystem extends SystemBase {
    protected GetSystemID(): number {
        return SystemID.TEST_EVENT_SYSTEM;
    }

    protected OnInit(): void {
        this.RegisterEvent("TestEventSystem", EventID.TEST_EVENT, (args?: any[]) => { this.Test(args) });
    }

    protected OnRelease(): void {
        this.UnregitsterEvent("TestEventSystem");
    }

    private Test(args?: any[]): void {
        let content = args[0] as string;

        LogUtility.Log(`触发事件操作 ${content}`);
    }
}