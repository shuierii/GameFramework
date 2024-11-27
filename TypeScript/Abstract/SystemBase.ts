/*
 * @Author: linb
 * @Date: 2024-04-12 11:07:42
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { AntNestBase } from "../AntNest/AntNestBase";
import { IAntNest } from "../AntNest/IAntNest";
import { IEvent } from "../Const/EventID";
import { IModel } from "../Interface/IModel";
import { ISystem } from "../Interface/ISystem";
import { MainGame } from "../MainGame";

export abstract class SystemBase implements ISystem {
    // 具体系统必须实现的接口
    protected abstract GetSystemID(): number;
    protected abstract OnInit(): void;
    protected abstract OnRelease(): void;

    Init(): void {
        this.OnInit();
    }

    Release(): void {
        this.OnRelease();
    }

    GetSystem<TSystem extends ISystem>(systemID: number): TSystem {
        return this.GetAntNest().GetSystem<TSystem>(systemID);
    }

    GetModel<TModel extends IModel>(modelID: number): TModel {
        return this.GetAntNest().GetModel<TModel>(modelID);
    }

    RegisterEvent<TEvent extends IEvent>(listenerID: string, eventClass: new (...args: any[]) => TEvent, handle: (arg?: TEvent) => void): void {
        this.GetAntNest().RegisterEvent(listenerID, eventClass, handle);
    }

    TriggerEvent<TEvent extends IEvent>(eventClass: new (...args: any[]) => TEvent, arg?: TEvent): void {
        this.GetAntNest().TriggerEvent(eventClass, arg);
    }

    UnregitsterEvent(listenerID: string): void {
        this.GetAntNest().UnregitsterEvent(listenerID);
    }

    SendScript(ScriptID: string, params?: any[]): any {
        return this.GetAntNest().SendScript(ScriptID, params);
    }

    private GetAntNest(): IAntNest {
        return MainGame.Instance;
    }
}