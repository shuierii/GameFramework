import * as UE from "ue";
import { MainGame } from "../MainGame";
import { LogUtility } from "./LogUtility";

export class TickUtility {
    /**
     * @description: 注册tick
     * @param {string} listenerID
     * @param {function} callBack
     * @return {*}
     */
    static RegisterTick(listenerID: string, callBack: (delta: number) => void): boolean {
        if (listenerID == null || listenerID.length <= 0 || callBack == null)
            return false;

        let tickMgr = UE.SubsystemBlueprintLibrary.GetGameInstanceSubsystem(MainGame.UEInstance, UE.TickMgr.StaticClass()) as UE.TickMgr;
        if (tickMgr == null)
            return false;

        if (tickMgr.ContainTick(listenerID))
            return false;

        let tickDelegate = tickMgr.CreateTickDelegater();
        if (tickDelegate == null)
            return false;

        tickDelegate.OnTick.Bind(callBack);

        let ret = tickMgr.RegisterTick(listenerID, tickDelegate);
        if (!ret) {
            LogUtility.Error(`the listenerID{${listenerID}} registerTick failed`);

            return false;
        }

        return true;
    }

    /**
     * @description: 注销tick
     * @param {string} listenerID
     * @return {*}
     */
    static UnRegisterTick(listenerID: string): boolean {
        if (listenerID == null || listenerID.length <= 0)
            return false;

        let tickMgr = UE.SubsystemBlueprintLibrary.GetGameInstanceSubsystem(MainGame.UEInstance, UE.TickMgr.StaticClass()) as UE.TickMgr;
        if (tickMgr == null)
            return false;

        if (!tickMgr.ContainTick(listenerID)) {
            return false;
        }

        let ret = tickMgr.UnregisterTick(listenerID);
        if (!ret) {
            LogUtility.Error(`the listenerID(${listenerID}) unregisterTick failed`);

            return false;
        }

        return true;
    }
}