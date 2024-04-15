/*
 * @Author: linb
 * @Date: 2024-04-15 11:28:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IScript } from "../Interface/IScript";

export abstract class ScriptBase implements IScript {
    protected abstract OnExcute(params?: any[]): any;

    Excute(params?: any[]): any {
        this.OnExcute(params);
    }
}