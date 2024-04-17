/*
 * @Author: linb
 * @Date: 2024-04-17 11:23:30
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { SystemBase } from "../../Abstract/SystemBase";
import { CommonConst } from "../../Const/CommonConst";
import { CommonEnum } from "../../Const/CommonEnum";
import { SystemID } from "../../Const/SystemID";
import { IEntityData } from "../../Data/IEntityData";
import { PlayerData } from "../../Data/PlayerData";
import { IPlayerSystem } from "./IPlayerSystem";

export class PlayerSystem extends SystemBase implements IPlayerSystem {
    protected GetSystemID(): number {
        return SystemID.PLAYER_SYSTEM;
    }

    protected OnInit(): void {

    }

    protected OnRelease(): void {

    }

    /**
     * @description: 生成数据
     * @param {string} name
     * @return {*}
     */
    GeneratePlayerData(name: string): IEntityData {
        let data = {};
        data["uid"] = "987654321";
        data["entity_type"] = CommonEnum.EntityType.PLAYER;
        data["class_id"] = CommonConst.EntityClassID.PLAYER_ID;
        data["name"] = name;

        let playerData = new PlayerData();
        playerData.Load(data);

        return playerData;
    }
}