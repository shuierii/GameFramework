/*
 * @Author: linb
 * @Date: 2024-11-27 16:07:45
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_IInputBase } from "../Base/E_IInputBase";

export class EI_GetPlayerA extends E_IInputBase {

    protected InitProperty(propertyData: object): void {

    }

    protected OnRelease(): void {

    }

    protected OnExecute(): any {
        return "康康(角色A)";
    }
}