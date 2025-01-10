/*
 * @Author: linb
 * @Date: 2024-11-01 15:25:35
 * @Description: 节点注册
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { SystemID } from "../Const/SystemID";
import { MainGame } from "../MainGame";
import { IEventSystem } from "../System/Event/IEventSystem";
import { E_Dialog } from "./Node/Dialog/E_DiaLog";
import { EI_GetPlayerA } from "./Node/Input/EI_GetPlayerA";
import { EI_GetPlayerB } from "./Node/Input/EI_GetPlayerB";
import { EP_Test } from "./Node/Precondition/EP_Test";
import { E_DialogEvent } from "./Node/Root/E_DialogEvent";
import { E_Script } from "./Node/Script/E_Script";
import { ET_Test } from "./Node/Trigger/ET_Test";

export module Event {
    export function BindData(): void {
        let eventSys = MainGame.Instance.GetSystem<IEventSystem>(SystemID.EVENT_SYSTEM);

        // root
        eventSys.BindNode(E_DialogEvent);

        // input
        eventSys.BindNode(EI_GetPlayerA);
        eventSys.BindNode(EI_GetPlayerB);

        // trigger
        eventSys.BindNode(ET_Test);

        // script
        eventSys.BindNode(E_Script);

        // dialog
        eventSys.BindNode(E_Dialog);

        // precondition
        eventSys.BindNode(EP_Test);
    }
}