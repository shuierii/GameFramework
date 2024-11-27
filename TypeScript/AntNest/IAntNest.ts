/*
 * @Author: linb
 * @Date: 2024-04-12 10:29:48
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
/*
 * @Author: linb
 * @Date: 2024-04-12 10:29:48
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { EventArgsBase, IEvent } from "../Const/EventID";
import { IInitable } from "../Interface/IInitable";
import { IModel } from "../Interface/IModel";
import { IReleasable } from "../Interface/IReleasable";
import { ISystem } from "../Interface/ISystem";

export interface IAntNest extends IInitable, IReleasable {
    /**
     * @description: 绑定系统
     * @param {number} systemID
     * @param {new} systemClass
     * @return {*}
     */
    BindSystem(systemID: number, systemClass: new (...args: any[]) => ISystem): void;

    /**
     * @description: 获取系统
     * @param {number} systemID
     * @return {*}
     */
    GetSystem<TSystem extends ISystem>(systemID: number): TSystem;

    /**
     * @description: 绑定数据模型
     * @param {number} modelID
     * @param {new} modelClass
     * @return {*}
     */
    BindModel(modelID: number, modelClass: new (...args: any[]) => IModel): void;

    /**
     * @description: 获取数据模型
     * @param {number} modelID
     * @return {*}
     */
    GetModel<TModel extends IModel>(modelID: number): TModel;

    /**
     * @description: 注册事件
     * @param {*} IEvent
     * @param {function} handle
     * @return {*}
     */
    RegisterEvent(listenerID: string, eventClass: new (...args: any[]) => IEvent, handle: (arg?: IEvent) => void): void;

    /**
     * @description: 触发事件
     * @param {new} eventClass
     * @param {any} args
     * @return {*}
     */
    TriggerEvent(eventClass: new (...args: any[]) => IEvent, arg?: IEvent): void;

    /**
     * @description: 注销事件
     * @param {string} listenerID 监听者
     * @return {*}
     */
    UnregitsterEvent(listenerID: string): void;

    /**
     * @description: 执行脚本
     * @param {string} ScriptID
     * @param {any} params
     * @return {*}
     */
    SendScript(ScriptID: string, params?: any[]): any;
}