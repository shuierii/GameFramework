/*
 * @Author: linb
 * @Date: 2024-04-12 11:07:42
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { AntNestBase } from "../AntNest/AntNestBase";
import { IAntNest } from "../AntNest/IAntNest";
import { ISystem } from "../Interface/ISystem";
import { MainGame } from "../MainGame";

export abstract class SystemBase implements ISystem {
    // 具体系统必须实现的接口
    protected abstract GetSystemID(): number;
    protected abstract OnInit(): void;
    protected abstract OnRelease(): void;

    Init(): void {
        this.OnInit();
    }

    Release(): void {
        this.OnRelease();
    }

    GetSystem<TSystem extends ISystem>(systemID: number): TSystem {
        return this.GetAntNest().GetSystem<TSystem>(systemID);
    }

    private GetAntNest(): IAntNest {
        return MainGame.Instance;
    }
}