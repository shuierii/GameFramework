/*
 * @Author: linb
 * @Date: 2024-04-15 18:04:23
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IAntNest } from "../AntNest/IAntNest";
import { IEvent } from "../Const/EventID";
import { IElement } from "../Interface/IElement";
import { IModel } from "../Interface/IModel";
import { ISystem } from "../Interface/ISystem";
import { MainGame } from "../MainGame";

export abstract class ElementBase implements IElement {
    RegisterEvent<TEvent extends IEvent>(listenerID: string, eventClass: new (...args: any[]) => TEvent, handle: (arg?: TEvent) => void): void {
        this.GetAntNest().RegisterEvent(listenerID, eventClass, handle);
    }

    TriggerEvent<TEvent extends IEvent>(eventClass: new (...args: any[]) => TEvent, arg?: TEvent): void {
        this.GetAntNest().TriggerEvent(eventClass, arg);
    }

    UnregitsterEvent(listenerID: string): void {
        this.GetAntNest().UnregitsterEvent(listenerID);
    }

    SendScript(ScriptID: string, params?: any[]) {
        return this.GetAntNest().SendScript(ScriptID, params);
    }

    GetSystem<TSystem extends ISystem>(systemID: number): TSystem {
        return this.GetAntNest().GetSystem<TSystem>(systemID);
    }

    GetModel<TModel extends IModel>(modelID: number): TModel {
        return this.GetAntNest().GetModel<TModel>(modelID);
    }

    private GetAntNest(): IAntNest {
        return MainGame.Instance;
    }
}