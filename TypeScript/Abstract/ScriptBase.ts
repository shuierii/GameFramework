/*
 * @Author: linb
 * @Date: 2024-04-15 11:28:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IScript } from "../Interface/IScript";

export abstract class ScriptBase implements IScript {
    // 对象类型
    mType: string;

    protected abstract OnExecute(params?: any[]): any;

    Reset(): void {

    }

    Execute(params?: any[]): any {
        this.OnExecute(params);
    }
}