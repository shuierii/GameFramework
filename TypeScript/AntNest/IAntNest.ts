/*
 * @Author: linb
 * @Date: 2024-04-12 10:29:48
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { IInitable } from "../Interface/IInitable";
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
}