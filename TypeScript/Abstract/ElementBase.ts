/*
 * @Author: linb
 * @Date: 2024-04-15 18:04:23
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IAntNest } from "../AntNest/IAntNest";
import { IElement } from "../Interface/IElement";
import { IModel } from "../Interface/IModel";
import { ISystem } from "../Interface/ISystem";
import { MainGame } from "../MainGame";

export abstract class ElementBase implements IElement {
    TriggerEvent(eventID: string, args?: any[]): void {
        this.GetAntNest().TriggerEvent(eventID, args);
    }

    RegisterEvent(listenerID: string, eventID: string, handle: (args?: any[]) => void): void {
        this.GetAntNest().RegisterEvent(listenerID, eventID, handle);
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