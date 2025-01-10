/*
 * @Author: linb
 * @Date: 2025-01-10 16:42:57
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
class TB_PlayerController extends UE.TS_PlayerController {

    ReceiveBeginPlay(): void {
        // 鼠标常显示
        this.bShowMouseCursor = true;
    }
}
export default TB_PlayerController;