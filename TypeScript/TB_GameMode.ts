/*
 * @Author: linb
 * @Date: 2025-01-10 16:42:29
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import * as UE from "ue";
import { TestUI } from "./UI/Test/TestUI";
class TB_GameMode extends UE.TS_GameMode {

    ReceiveBeginPlay(): void {
        TestUI.ShowTestPanel();
    }
}
export default TB_GameMode;