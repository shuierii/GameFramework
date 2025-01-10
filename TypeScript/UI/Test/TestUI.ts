/*
 * @Author: linb
 * @Date: 2025-01-10 15:31:07
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { SystemID } from "../../Const/SystemID";
import { MainGame } from "../../MainGame";
import { IUISystem } from "../../System/UI/IUISystem";
import { TestPanel } from "./TestPanel";

export module TestUI {
    export function ShowTestPanel(): void {
        MainGame.Instance.GetSystem<IUISystem>(SystemID.UI_SYSTEM).ShowPanel<TestPanel>(TestPanel, "TestPanel");
    }
}