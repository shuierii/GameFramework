/*
 * @Author: linb
 * @Date: 2024-11-25 17:01:42
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_INode } from "./E_INode";
import { E_IScript } from "./E_IScript";
import { E_ITrigger } from "./E_ITrigger";

export interface E_IRoot extends E_INode {

    GetID(): number;

    GetFileName(): string;

    Start(): boolean;

    Finish(): void;

    /**
     * @description: 设置触发器列表
     * @param {Array} triggerList
     * @return {*}
     */
    SetTriggerList(triggerList: Array<E_ITrigger>): void;
}