/*
 * @Author: linb
 * @Date: 2024-11-29 10:53:56
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_IDialog, E_IDialogOption } from "../Implememt/E_IDialog";
import { E_NodeBase } from "../Base/E_NodeBase";
import { Event_Test } from "../../../Const/EventID";

export class E_Dialog extends E_NodeBase implements E_IDialog {

    private mDialogContent: string = "";

    // 对话选项列表
    private mDialogOptionList: Array<E_IDialogOption> = [];

    private mOptionIDToDialogOptionMap: Map<string, E_IDialogOption> = new Map();

    protected OnInit(nodeData: object): void {
        this.mDialogContent = nodeData["talk_content"];
    }

    protected OnRelease(): void {

    }

    protected OnReset(): void {

    }

    Enter(): void {

    }

    Execute(): void {
        this.TriggerEvent(Event_Test.EVENT_EXECUTE_TALK, {
            dialog: this
        });
    }

    /**
     * @description: 设置对话选项列表
     * @param {Array} dialogOptionList
     * @return {*}
     */
    SetDialogList(dialogOptionList: Array<E_IDialogOption>): void {
        for (const dialogOption of dialogOptionList) {
            if (dialogOption == null)
                continue;

            this.mOptionIDToDialogOptionMap.set(dialogOption.optionID, dialogOption);
        }

        this.mDialogOptionList = dialogOptionList;
    }

    /**
     * @description: 对话选项ID列表
     * @return {*}
     */
    GetOptionIDList(): Array<string> {
        let IDList: Array<string> = [];

        for (const dialogOption of this.mDialogOptionList) {
            if (dialogOption == null)
                continue;

            IDList.push(dialogOption.optionID);
        }

        return IDList;
    }

    /**
     * @description: 选项内容
     * @return {*}
     */
    GetOptionTextByID(optionID: string): string {
        if (!this.mOptionIDToDialogOptionMap.has(optionID))
            return "";

        let dialogOption = this.mOptionIDToDialogOptionMap.get(optionID);
        if (dialogOption == null)
            return "";

        return dialogOption.optionContent;
    }

    /**
     * @description: 说话人
     * @return {*}
     */
    GetTalker(): string {
        return this.GetInputData<string>("说话人");
    }

    /**
     * @description: 说话内容
     * @return {*}
     */
    GetDialogContent(): string {
        return this.mDialogContent;
    }
}