/*
 * @Author: linb
 * @Date: 2024-10-31 19:01:25
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IRecycable } from "../../../Interface/IRecycable";
import { E_IInput } from "./E_IInput";
import { E_IOutput } from "./E_IOutput";
import { E_IPrecondition } from "./E_IPrecondition";
import { E_IRoot } from "./E_IRoot";

export interface E_INode extends IRecycable {

    GetRootNode(): E_IRoot;

    GetParent(): E_INode;

    /**
     * @description: 初始化
     * @param {object} nodeData
     * @param {E_INode} rootNode
     * @param {E_INode} parent
     * @return {*}
     */
    Init(nodeData: object, rootNode: E_INode, parent: E_INode): void;

    /**
     * @description: 设置前置条件
     * @return {*}
     */
    SetPrecondition(precondition: E_IPrecondition): void;

    /**
     * @description: 设置输入列表
     * @return {*}
     */
    SetInputList(inputList: Array<E_IInput>): void;

    /**
     * @description: 设置输出列表
     * @return {*}
     */
    SetOutputList(outputList: Array<E_IOutput>): void;
}