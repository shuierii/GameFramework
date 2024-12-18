/*
 * @Author: linb
 * @Date: 2024-04-15 17:38:42
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IComponent } from "../Interface/IComponent";

export abstract class ComponentBase implements IComponent {
    // 对象类型
    mType: string;

    protected abstract OnInit(): void;
    protected abstract OnRelease(): void;
    protected abstract OnReset(): void;

    Init(): void {
        this.OnInit()
    }

    Release(): void {
        this.OnRelease();
    }

    Reset(): void {
        this.OnReset();
    }
}