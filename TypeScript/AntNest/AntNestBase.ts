/*
 * @Author: linb
 * @Date: 2024-04-12 10:29:30
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ISystem } from "../Interface/ISystem";
import { LogUtility } from "../Utility/LogUtility";
import { IAntNest } from "./IAntNest";

export abstract class AntNestBase implements IAntNest {
    // <系统ID，系统Class>
    private mSystemClassMap: Map<number, new (...args: any[]) => ISystem> = new Map();

    Init(): void {
        this.InitSystem();
    }

    Release(): void {
        this.ReleaseSystem();

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
            LogUtility.Error(`systemID_${systemID} class is null.`)
            return;
        }

        if (this.mSystemClassMap.has(systemID)) {
            LogUtility.Warn(`systemID_${systemID} is exist.`)
            return;
        }

        this.mSystemClassMap.set(systemID, systemClass);
        LogUtility.Log(`bind systemID_${systemID} success.`)
    }

    /**
     * @description: 获取系统
     * @param {number} systemID
     * @return {*}
     */
    GetSystem<TSystem extends ISystem>(systemID: number): TSystem {
        if (!this.mSystemClassMap.has(systemID)) {
            LogUtility.Error(`systemID_${systemID} is not exist.`)
            return null;
        }

        let systemClass = this.mSystemClassMap.get(systemID);
        let systemObj = new systemClass();

        return systemObj as TSystem;
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
}