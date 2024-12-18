/*
 * @Author: linb
 * @Date: 2024-11-26 15:51:14
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_IDialog } from "./E_IDialog";
import { E_INode } from "./E_INode";

export interface E_IScript extends E_INode {
    /**
     * @description: 剧情上演
     * @return {*}
     */
    Play(): boolean;

    /**
     * @description: 设置对话节点
     * @param {Array} dialogList
     * @return {*}
     */
    SetDialogList(dialogList: Array<E_IDialog>): void;
}