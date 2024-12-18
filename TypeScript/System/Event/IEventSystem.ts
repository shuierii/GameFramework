/*
 * @Author: linb
 * @Date: 2024-11-01 15:17:19
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { E_INode } from "../../Event/Node/Implememt/E_INode";
import { ISystem } from "../../Interface/ISystem";

export interface IEventSystem extends ISystem {
    /**
     * @description: 绑定节点
     * @param {new} nodeClass
     * @return {*}
     */
    BindNode(nodeClass: new (...args: any[]) => E_INode): void;

    /**
     * @description: 执行事件
     * @param {number} eventID
     * @return {*}
     */
    ExecuteEvent(eventID: number): void;
}