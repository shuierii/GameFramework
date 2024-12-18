/*
 * @Author: linb
 * @Date: 2024-04-12 16:45:21
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ModelBase } from "../Abstract/ModelBase";
import { ModelID } from "../Const/ModelID";
import { LogUtility } from "../Utility/LogUtility";

export class TestModel extends ModelBase {
    protected GetModelID(): number {
        return ModelID.TEST_MODEL;
    }

    protected OnInit(): void {
        this.Test();
        LogUtility.Log(`TestModel init success.`);
    }

    protected OnRelease(): void {
        LogUtility.Log(`TestModel release success.`);
    }

    private Test(): void {
        LogUtility.Log("数据模型测试接口----------------hello world");
    }
}