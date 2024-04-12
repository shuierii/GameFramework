/*
 * @Author: linb
 * @Date: 2024-04-12 16:26:20
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IAntNest } from "../AntNest/IAntNest";
import { IModel } from "../Interface/IModel";
import { MainGame } from "../MainGame";

export abstract class ModelBase implements IModel {
    protected abstract GetModelID(): number;
    protected abstract OnInit(): void;
    protected abstract OnRelease(): void;

    Init(): void {
        this.OnInit();
    }

    Release(): void {
        this.OnRelease();
    }

    GetModel<TModel extends IModel>(modelID: number): TModel {
        return this.GetAntNest().GetModel<TModel>(modelID);
    }

    private GetAntNest(): IAntNest {
        return MainGame.Instance;
    }
}