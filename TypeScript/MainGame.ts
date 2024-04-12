/*
 * @Author: linb
 * @Date: 2024-04-12 11:13:27
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { AntNestBase } from "./AntNest/AntNestBase";
import { IAntNest } from "./AntNest/IAntNest";

export class MainGame extends AntNestBase {
    private static mInstance: MainGame = null;

    // 创建游戏唯一单例管理者
    public static get Instance(): IAntNest {
        if (this.mInstance == null) {
            this.mInstance = new MainGame();
        }

        return this.mInstance;
    }
}