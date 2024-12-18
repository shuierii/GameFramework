/*
 * @Author: linb
 * @Date: 2024-10-31 18:56:14
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ElementBase } from "../../../Abstract/ElementBase";
import { GameUtility } from "../../../Utility/GameUtility";
import { LogUtility } from "../../../Utility/LogUtility";
import { E_IInput } from "../Implememt/E_IInput";
import { E_INode } from "../Implememt/E_INode";
import { E_IOutput } from "../Implememt/E_IOutput";
import { E_IPrecondition } from "../Implememt/E_IPrecondition";
import { E_IRoot } from "../Implememt/E_IRoot";

export abstract class E_NodeBase extends ElementBase implements E_INode {

    mType: string = "";

    // Cookie
    protected mCookie: string = "";

    // 根节点
    private mRootNode: E_IRoot = null;

    // 父节点
    private mParent: E_INode = null;

    // 前置条件
    private mPrecondition: E_IPrecondition = null;

    // 输入器 <字段，输入器节点>
    private mInputMap: Map<string, E_IInput> = new Map();

    // 输出器 <字段，输出器节点>
    private mOutputMap: Map<string, E_IOutput> = new Map();

    // 抽象接口
    protected abstract OnInit(nodeData: object): void;
    protected abstract OnRelease(): void;
    protected abstract OnReset(): void;

    /**
     * @description: 构造函数
     * @param {string} type 节点类名
     * @return {*}
     */
    constructor(type: string) {
        super();

        this.mType = type;
    }

    /**
     * @description: 初始化
     * @param {object} nodeData
     * @param {E_INode} rootNode
     * @param {E_INode} parent
     * @return {*}
     */
    Init(nodeData: object, rootNode: E_IRoot, parent: E_INode): void {
        // 设置根节点
        this.mRootNode = rootNode;

        // 设置父节点
        this.mParent = parent;

        // 设置cookie
        this.mCookie = GameUtility.CreateCookie("E_INode");

        this.OnInit(nodeData);
    }

    Release(): void {
        this.OnRelease();
    }

    Reset(): void {
        this.OnReset();
    }

    GetRootNode(): E_IRoot {
        return this.mRootNode;
    }

    GetParent(): E_INode {
        return this.mParent;
    }

    /**
     * @description: 设置前置条件
     * @return {*}
     */
    SetPrecondition(precondition: E_IPrecondition): void {
        if (precondition == null)
            return;

        this.mPrecondition = precondition;
    }

    /**
     * @description: 设置输入列表
     * @return {*}
     */
    SetInputList(inputList: Array<E_IInput>): void {
        if (inputList == null || inputList.length <= 0)
            return;

        for (const input of inputList) {
            if (input == null)
                continue;

            let field = input.GetField();
            if (field == null)
                continue;

            if (this.mInputMap.has(field)) {
                LogUtility.Error(`the file(${this.mRootNode.GetFileName()}) input field(${field}) exist`);

                continue;
            }

            this.mInputMap.set(field, input);
        }
    }

    /**
     * @description: 设置输出列表
     * @return {*}
     */
    SetOutputList(outputList: Array<E_IOutput>): void {
        if (outputList == null || outputList.length <= 0)
            return;

        for (const output of outputList) {
            if (output == null)
                continue;

            let field = output.GetField();
            if (field == null)
                continue;

            if (this.mOutputMap.has(field)) {
                LogUtility.Error(`the file(${this.mRootNode.GetFileName()}) output field(${field}) exist`);

                continue;
            }

            this.mOutputMap.set(field, output);
        }
    }

    /**
     * @description: 获取输入器数据
     * @param {string} field
     * @return {*}
     */
    protected GetInputData<TData extends any>(field: string): TData {
        if (!this.mInputMap.has(field)) {
            LogUtility.Error(`the node(${this.mType}) input field(${field}) not exist`);

            return null;
        }

        let input = this.mInputMap.get(field);
        if (input == null)
            return null;

        return input.Execute();
    }

    /**
     * @description: 设置输入器数据
     * @param {string} field
     * @param {TData} data
     * @return {*}
     */
    protected SetOutputData<TData extends any>(field: string, data: TData): boolean {
        if (field == null || field.length <= 0 || data == null)
            return false;

        // 输出节点不存在
        if (!this.mOutputMap.has(field)) {
            LogUtility.Error(`the node(${this.mType}) output field(${field}) not exist`);

            return false;
        }

        let output = this.mOutputMap.get(field);
        if (output == null)
            return false;

        return output.Execute();
    }
}