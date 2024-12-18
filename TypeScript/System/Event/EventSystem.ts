/*
 * @Author: linb
 * @Date: 2024-11-01 15:17:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { SystemBase } from "../../Abstract/SystemBase";
import { SystemID } from "../../Const/SystemID";
import { IEventSystem } from "./IEventSystem";
import { Event } from "../../Event/Index";
import { E_INode } from "../../Event/Node/Implememt/E_INode";
import { ObjectPool } from "../../Common/ObjectPool";
import { LogUtility } from "../../Utility/LogUtility";
import { IEventModel } from "../../Model/Event/IEventModel";
import { ModelID } from "../../Const/ModelID";
import { E_IRoot } from "../../Event/Node/Implememt/E_IRoot";
import { E_RootBase } from "../../Event/Node/Base/E_RootBase";
import { E_ITrigger } from "../../Event/Node/Implememt/E_ITrigger";
import { E_IPrecondition } from "../../Event/Node/Implememt/E_IPrecondition";
import { E_IInput } from "../../Event/Node/Implememt/E_IInput";
import { E_IOutput } from "../../Event/Node/Implememt/E_IOutput";
import { E_Script } from "../../Event/Node/Script/E_Script";
import { E_DialogEvent } from "../../Event/Node/Root/E_DialogEvent";
import { E_IScript } from "../../Event/Node/Implememt/E_IScript";
import { E_IDialog, E_IDialogOption } from "../../Event/Node/Implememt/E_IDialog";
import { E_Dialog } from "../../Event/Node/Dialog/E_DiaLog";

export class EventSystem extends SystemBase implements IEventSystem {

    // E_INode类映射 <节点类名，类>
    private mNodeClassMap: Map<string, new (...args: any[]) => E_INode> = new Map();

    // 对象池
    private mObjPool: ObjectPool = new ObjectPool();

    // 事件（根节点）映射
    private mEventMap: Map<number, E_IRoot> = new Map();

    protected GetSystemID(): number {
        return SystemID.EVENT_SYSTEM;
    }

    protected OnInit(): void {
        // 注册事件
        Event.BindData();

        // 初始化事件
        this.InitAllEvent();
    }

    protected OnRelease(): void {

    }

    //#region 节点接口

    /**
     * @description: 绑定节点
     * @param {new} nodeClass
     * @return {*}
     */
    BindNode(nodeClass: new (...args: any[]) => E_INode): void {
        if (nodeClass == null)
            return;

        let nodeType = nodeClass.name;
        if (this.mNodeClassMap.has(nodeType)) {
            return;
        }

        this.mNodeClassMap.set(nodeType, nodeClass);
    }


    /**
     * @description: 生成节点对象
     * @param {string} nodeType
     * @return {*}
     */
    private SpawnNode<TNode extends E_INode>(nodeType: string): TNode {
        if (!this.mNodeClassMap.has(nodeType)) {
            LogUtility.Error(`the type(${nodeType}) not binded`);

            return null;
        }

        let nodeClass = this.mNodeClassMap.get(nodeType)
        if (nodeClass == null)
            return null;

        let node = this.mObjPool.Spawn<TNode>(nodeType, nodeClass);
        if (node == null) {
            LogUtility.Error(`spawn node(${nodeType}) failed`);

            return null;
        }

        return node;
    }

    /**
     * @description: 回收节点对象
     * @param {E_INode} node
     * @return {*}
     */
    private RecycleNode(node: E_INode): boolean {
        if (node == null)
            return false;

        let nodeType = node.mType;

        return this.mObjPool.Recycle(nodeType, node);
    }

    /**
     * @description: 创建节点
     * @param {object} nodeData
     * @return {*}
     */
    private CreateNode<TNode extends E_INode>(nodeData: object, rootNode: E_IRoot, parent: E_INode): TNode {
        if (nodeData == null)
            return null;

        let type = nodeData["type"] as string;
        if (type == null) {
            LogUtility.Error(`the nodeData(${JSON.stringify(nodeData)}) type not exist`);

            return null;
        }

        let node = this.SpawnNode<TNode>(type);
        if (node == null) {
            LogUtility.Error(`the node(${type}) spawn failed`);

            return null;
        }

        // Root
        if (node instanceof E_RootBase) {
            rootNode = node;
            parent = null;

            // 触发节点列表
            let triggerList: Array<E_ITrigger> = [];
            let triggerDataList = nodeData["trigger_list"] as Array<object>;
            if (triggerDataList != null && triggerDataList.length > 0)
                triggerList = this.CreateNodeList<E_ITrigger>(triggerDataList, rootNode, node);

            node.SetTriggerList(triggerList);

            // E_DialogEvent
            if (node instanceof E_DialogEvent) {
                // 剧情脚本列表
                let scriptList: Array<E_IScript> = [];
                let scriptDataList = nodeData["script_list"] as Array<object>;
                if (scriptDataList != null && scriptDataList.length > 0)
                    scriptList = this.CreateNodeList<E_IScript>(scriptDataList, rootNode, node);

                node.SetScriptList(scriptList);
            }
        }

        // 剧情节点
        else if (node instanceof E_Script) {
            // 对话节点列表
            let dialogList: Array<E_IDialog> = [];
            let dialogDataList = nodeData["dialog_list"] as Array<object>;
            if (dialogDataList != null && dialogDataList.length > 0)
                dialogList = this.CreateNodeList<E_IDialog>(dialogDataList, rootNode, node);

            node.SetDialogList(dialogList);
        }

        // 对话节点
        else if (node instanceof E_Dialog) {
            // 对话选项列表
            let dialogOptionList: Array<E_IDialogOption> = [];
            let dialogOptionDataList = nodeData["option_list"] as Array<object>;
            if (dialogOptionDataList != null && dialogOptionDataList.length > 0)
                dialogOptionList = this.CreateOptionList(dialogOptionDataList, rootNode, node);

            node.SetDialogList(dialogOptionList);
        }



        // common
        // precondition
        let preconditionData = nodeData["precondition"] as object;
        if (preconditionData != null) {
            let precondition = this.CreateNode<E_IPrecondition>(preconditionData, rootNode, node);
            if (precondition == null)
                return;

            node.SetPrecondition(precondition);
        }

        // input_list
        let inputListData = nodeData["input_list"] as Array<object>;
        if (inputListData != null && inputListData.length > 0) {
            let inputList = this.CreateNodeList<E_IInput>(inputListData, rootNode, node);
            if (inputList == null || inputList.length <= 0)
                return;

            node.SetInputList(inputList);
        }

        // output_list
        let outputListData = nodeData["output_list"] as Array<object>;
        if (outputListData != null && outputListData.length > 0) {
            let outputList = this.CreateNodeList<E_IOutput>(outputListData, rootNode, node);
            if (outputList == null || outputList.length <= 0)
                return;

            node.SetOutputList(outputList);
        }

        // init
        node.Init(nodeData, rootNode, parent);

        return node;
    }

    /**
     * @description:  生成节点列表（如触发列表等）
     * @param {Array} nodeDataList
     * @param {E_IRoot} rootNode
     * @param {E_INode} parent
     * @return {*}
     */
    private CreateNodeList<TNode extends E_INode>(nodeDataList: Array<object>, rootNode: E_IRoot, parent: E_INode): Array<TNode> {
        if (nodeDataList == null || nodeDataList.length <= 0)
            return [];

        let nodeList: Array<TNode> = [];

        for (const nodeData of nodeDataList) {
            if (nodeData == null)
                continue;

            let node = this.CreateNode<TNode>(nodeData, rootNode, parent);
            if (node == null)
                continue;

            nodeList.push(node);
        }

        return nodeList;
    }

    /**
     * @description: 生成对话选项列表
     * @param {Array} optionDataList
     * @param {E_IRoot} rootNode
     * @param {E_INode} parent
     * @return {*}
     */
    private CreateOptionList(optionDataList: Array<object>, rootNode: E_IRoot, parent: E_INode): Array<E_IDialogOption> {
        if (optionDataList == null || optionDataList.length <= 0)
            return [];

        let optionList: Array<E_IDialogOption> = [];
        for (const optionData of optionDataList) {
            if (optionData == null)
                continue;

            let ID = optionData["option_id"];
            if (ID == null)
                continue;

            let content = optionData["option_content"];
            if (content == null)
                continue;

            let dialogOption: E_IDialogOption = { optionID: ID, optionContent: content };

            optionList.push(dialogOption);
        }

        return optionList;
    }

    //#endregion 节点接口END

    //#region 事件接口

    /**
     * @description: 执行事件
     * @param {number} eventID
     * @return {*}
     */
    ExecuteEvent(eventID: number): void {
        let event = this.GetEvent(eventID);
        if (event == null)
            return;

        // 开始事件
        let ret = event.Start();
        if (!ret) {
            LogUtility.Error(`the eventID(${eventID}) start failed`);

            return;
        }
    }

    FinishEvent(eventID: number): void {
        let event = this.GetEvent(eventID);
        if (event == null)
            return;

        event.Finish();
    }

    /**
     * @description: 初始化事件
     * @return {*}
     */
    private InitAllEvent(): void {
        // 加载所有事件
        let eventModel = this.GetModel<IEventModel>(ModelID.EVENT_MODEL);
        let eventDataMap = eventModel.GetEventDataMap();
        if (eventDataMap == null || eventDataMap.size <= 0)
            return;

        for (const [id, data] of eventDataMap) {
            if (data == null)
                continue;

            this.AddEvent(data);
        }
    }

    /**
     * @description: 添加事件
     * @param {object} eventData
     * @return {*}
     */
    private AddEvent(eventData: object): void {
        if (eventData == null)
            return;

        // 事件根节点，挂在各种触发节点、条件节点等
        let event = this.CreateNode<E_IRoot>(eventData, null, null);
        if (event == null)
            return;

        let eventID = event.GetID();
        if (this.mEventMap.has(eventID))
            return;

        this.mEventMap.set(eventID, event);
    }

    /**
     * @description: 获取事件
     * @param {number} eventID
     * @return {*}
     */
    private GetEvent(eventID: number): E_IRoot {
        if (!this.mEventMap.has(eventID))
            return null;

        let event = this.mEventMap.get(eventID);
        if (event == null)
            return null;

        return event;
    }

    //#endregion 事件接口END
}