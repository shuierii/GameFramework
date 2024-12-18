/*
 * @Author: linb
 * @Date: 2024-04-15 10:40:00
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { SystemBase } from "../Abstract/SystemBase";
import { Event_Test } from "../Const/EventID";
import { SystemID } from "../Const/SystemID";
import { LogUtility } from "../Utility/LogUtility";

export class TestEventSystem extends SystemBase {
    protected GetSystemID(): number {
        return SystemID.TEST_EVENT_SYSTEM;
    }

    protected OnInit(): void {
        this.RegisterEvent("TestEventSystem", Event_Test.EVENT_TEST, this.Test.bind(this));

        // 执行对话
        this.RegisterEvent("TestEventSystem", Event_Test.EVENT_EXECUTE_TALK, this.ShowDialogContent.bind(this));
    }

    protected OnRelease(): void {
        this.UnregitsterEvent("TestEventSystem");
    }

    private Test(args: Event_Test.EVENT_TEST): void {
        LogUtility.Log(`触发事件操作 ${args.content}`);

        this.TriggerEvent(Event_Test.EVENT_TRIGGER_DIALOG);
    }

    private ShowDialogContent(args: Event_Test.EVENT_EXECUTE_TALK): void {
        let dialog = args.dialog;
        if (dialog == null)
            return;

        LogUtility.Log(`===对话内容===`);

        let talker = dialog.GetTalker();
        let content = dialog.GetDialogContent();
        let optionIDList = dialog.GetOptionIDList();

        let optionText = "";
        for (const optionID of optionIDList) {
            optionText += `${optionID}:`
            let optionContent = dialog.GetOptionTextByID(optionID);
            optionText += optionContent;
            optionText += `\n`;
        }

        LogUtility.Info(`${talker}:\n${content}\n${optionText}`);

        LogUtility.Log(`===END===`);
    }
}