/*
 * @Author: linb
 * @Date: 2024-04-12 11:06:11
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { SystemBase } from "../Abstract/SystemBase";
import { SystemID } from "../Const/SystemID";
import { LogUtility } from "../Utility/LogUtility";

export class TestSystem extends SystemBase {
    protected GetSystemID(): number {
        return SystemID.TEST_SYSTEM;
    }

    protected OnInit(): void {
        this.Test();
        LogUtility.Log(`TestSystem init success.`);
    }

    protected OnRelease(): void {
        LogUtility.Log(`TestSystem release success.`);
    }

    private Test(): void {
        LogUtility.Error("系统测试接口----------------hello world");
    }
}