/*
 * @Author: linb
 * @Date: 2024-11-26 15:49:31
 * @Description: 剧情脚本
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_NodeBase } from "../Base/E_NodeBase";
import { E_IDialog } from "../Implememt/E_IDialog";
import { E_IScript } from "../Implememt/E_IScript";

export class E_Script extends E_NodeBase implements E_IScript {

    // 对话列表
    private mDialogList: Array<E_IDialog> = [];

    // 对话节点映射
    private mDialogMap: Map<string, E_IDialog> = new Map();

    protected OnInit(nodeData: object): void {

    }

    protected OnReset(): void {

    }

    protected OnRelease(): void {

    }

    /**
     * @description: 剧情上演
     * @return {*}
     */
    Play(): boolean {
        this.StartDialog();
        return true;
    }

    /**
     * @description: 设置对话节点
     * @param {Array} dialogList
     * @return {*}
     */
    SetDialogList(dialogList: Array<E_IDialog>): void {
        this.mDialogList = dialogList;
    }

    private StartDialog(): void {
        let dialog_1 = this.mDialogList[0];
        if (dialog_1 == null)
            return;

        dialog_1.Enter();
        dialog_1.Execute();
    }
}