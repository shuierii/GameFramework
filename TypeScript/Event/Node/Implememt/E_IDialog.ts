/*
 * @Author: linb
 * @Date: 2024-11-29 10:52:42
 * @Description: 玩家选项对话
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_INode } from "./E_INode";

export interface E_IDialogOption {
    optionID: string;
    optionContent: string;
}

export interface E_IDialog extends E_INode {

    Enter(): void;

    Execute(): void;

    /**
     * @description: 设置对话选项列表
     * @param {Array} dialogOptionList
     * @return {*}
     */
    SetDialogList(dialogOptionList: Array<E_IDialogOption>): void;

    /**
     * @description: 对话选项ID列表
     * @return {*}
     */
    GetOptionIDList(): Array<string>;

    /**
     * @description: 选项内容
     * @return {*}
     */
    GetOptionTextByID(optionID: string): string;

    /**
     * @description: 说话人
     * @return {*}
     */
    GetTalker(): string;

    /**
     * @description: 说话内容
     * @return {*}
     */
    GetDialogContent(): string;
}