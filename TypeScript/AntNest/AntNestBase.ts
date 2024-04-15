/*
 * @Author: linb
 * @Date: 2024-04-12 10:29:30
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IModel } from "../Interface/IModel";
import { ISystem } from "../Interface/ISystem";
import { LogUtility } from "../Utility/LogUtility";
import { IAntNest } from "./IAntNest";

export abstract class AntNestBase implements IAntNest {
    // <系统ID，系统Class>
    private mSystemClassMap: Map<number, new (...args: any[]) => ISystem> = new Map();

    // <模型ID，模型Class>
    private mModelClassMap: Map<number, new (...args: any[]) => IModel> = new Map();

    // <事件，<监听者，处理回调>>
    private mEventMap: Map<string, Map<string, (args?: any[]) => void>> = new Map();

    Init(): void {
        // 先初始化数据，再初始化系统，因为系统会用到数据
        this.InitModel();
        this.InitSystem();
    }

    Release(): void {
        // 先释放系统，再释放数据，因为系统会用到数据
        this.ReleaseSystem();
        this.ReleaseModel();

        this.mSystemClassMap.clear();
    }

    /**
     * @description: 绑定系统
     * @param {number} systemID
     * @param {new} systemClass
     * @return {*}
     */
    BindSystem(systemID: number, systemClass: new (...args: any[]) => ISystem): void {
        if (systemClass == null) {
            LogUtility.Error(`systemID_${systemID} class is null.`);
            return;
        }

        if (this.mSystemClassMap.has(systemID)) {
            LogUtility.Warn(`systemID_${systemID} is exist.`);
            return;
        }

        this.mSystemClassMap.set(systemID, systemClass);
        LogUtility.Log(`bind systemID_${systemID} success.`);
    }

    /**
     * @description: 获取系统
     * @param {number} systemID
     * @return {*}
     */
    GetSystem<TSystem extends ISystem>(systemID: number): TSystem {
        if (!this.mSystemClassMap.has(systemID)) {
            LogUtility.Error(`systemID_${systemID} is not exist.`);
            return null;
        }

        let systemClass = this.mSystemClassMap.get(systemID);
        let systemObj = new systemClass();

        return systemObj as TSystem;
    }

    /**
     * @description: 绑定数据模型
     * @param {number} modelID
     * @param {new} modelClass
     * @return {*}
     */
    BindModel(modelID: number, modelClass: new (...args: any[]) => IModel): void {
        if (modelClass == null) {
            LogUtility.Error(`modelID_${modelClass} class is null.`);
            return;
        }

        if (this.mModelClassMap.has(modelID)) {
            LogUtility.Warn(`modelID_${modelID} is exist.`);
            return;
        }

        this.mModelClassMap.set(modelID, modelClass);
        LogUtility.Log(`bind modelID_${modelID} success.`);
    }

    /**
     * @description: 获取数据模型
     * @param {number} modelID
     * @return {*}
     */
    GetModel<TModel extends IModel>(modelID: number): TModel {
        if (!this.mModelClassMap.has(modelID)) {
            LogUtility.Error(`modelID_${modelID} is not exist.`);
            return null;
        }

        let modelClass = this.mModelClassMap.get(modelID);
        let modelObj = new modelClass();

        return modelObj as TModel;
    }

    /**
     * @description: 注册事件
     * @param {string} listenerID 监听者
     * @param {string} eventID 事件
     * @param {function} handle 事件回调
     * @return {*}
     */
    RegisterEvent(listenerID: string, eventID: string, handle: (args?: any[]) => void): void {
        // 没有此事件的记录
        if (!this.mEventMap.has(eventID)) {
            let map: Map<string, (args?: any[]) => void> = new Map();
            map.set(listenerID, handle);

            this.mEventMap.set(eventID, map);

            LogUtility.Log(`the listenerID_(${listenerID}) , eventId_${eventID} rigister success.`);
            return;
        }

        let listenerMap = this.mEventMap.get(eventID);
        if (listenerMap.has(listenerID)) {
            LogUtility.Warn(`the listenerID_(${listenerID}) , eventId_${eventID} has existed.`);
            return;
        }

        listenerMap.set(listenerID, handle);

        LogUtility.Log(`the listenerID_(${listenerID}) , eventId_${eventID} rigister success.`);
    }

    /**
     * @description: 触发事件
     * @param {string} eventID 事件
     * @param {any} args 携带参数
     * @return {*}
     */
    TriggerEvent(eventID: string, args?: any[]): void {
        if (!this.mEventMap.has(eventID)) {
            return;
        }

        let listenerMap = this.mEventMap.get(eventID);
        for (const callBack of listenerMap.values()) {
            if (callBack == null)
                return;

            callBack(args);
        }
    }

    /**
     * @description: 注销事件
     * @param {string} listenerID 监听者
     * @return {*}
     */
    UnregitsterEvent(listenerID: string): void {
        let listenerMap = this.mEventMap.values();
        for (const map of listenerMap) {
            if (map == null)
                continue;

            if (!map.has(listenerID))
                continue;

            map.delete(listenerID);
        }
    }

    /**
     * @description: 初始化系统
     * @return {*}
     */
    private InitSystem(): void {
        for (const systemID of this.mSystemClassMap.keys()) {
            let system = this.GetSystem(systemID);
            if (system == null)
                continue;

            system.Init();
        }
    }

    /**
     * @description: 释放系统
     * @return {*}
     */
    private ReleaseSystem(): void {
        for (const systemID of this.mSystemClassMap.keys()) {
            let system = this.GetSystem(systemID);
            if (system == null)
                continue;

            system.Release();
        }
    }

    /**
     * @description: 初始化数据模型
     * @return {*}
     */
    private InitModel(): void {
        for (const modelID of this.mModelClassMap.keys()) {
            let model = this.GetModel(modelID);
            if (model == null)
                continue;

            model.Init();
        }
    }

    /**
     * @description: 释放数据模型
     * @return {*}
     */
    private ReleaseModel(): void {
        for (const modelID of this.mModelClassMap.keys()) {
            let model = this.GetModel(modelID);
            if (model == null)
                continue;

            model.Release();
        }
    }
}