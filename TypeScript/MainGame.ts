/*
 * @Author: linb
 * @Date: 2024-04-12 11:13:27
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { AntNestBase } from "./AntNest/AntNestBase";
import { IAntNest } from "./AntNest/IAntNest";

export class MainGame extends AntNestBase {
    private static mInstance: MainGame = null;

    // 创建游戏唯一单例管理者，框架单例
    public static get Instance(): IAntNest {
        if (this.mInstance == null) {
            this.mInstance = new MainGame();
        }

        return this.mInstance;
    }

    // 虚幻游戏单例，GameInstance
    private static mUEIntance: UE.Object;

    public static set UEInstance(instance: UE.Object) {
        this.mUEIntance = instance;
    }

    public static get UEInstance(): UE.Object {
        return this.mUEIntance;
    }
}