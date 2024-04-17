/*
 * @Author: linb
 * @Date: 2024-04-12 11:06:11
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { SystemBase } from "../Abstract/SystemBase";
import { CommonConst } from "../Const/CommonConst";
import { CommonEnum } from "../Const/CommonEnum";
import { EventID } from "../Const/EventID";
import { ModelID } from "../Const/ModelID";
import { SystemID } from "../Const/SystemID";
import { IEntityData } from "../Data/IEntityData";
import { IPlayerModel } from "../Model/Player/IPlayerModel";
import { LogUtility } from "../Utility/LogUtility";
import { IEntitySystem } from "./Entity/IEntitySystem";
import { IPlayerSystem } from "./Player/IPlayerSystem";

export class TestSystem extends SystemBase {
    protected GetSystemID(): number {
        return SystemID.TEST_SYSTEM;
    }

    protected OnInit(): void {
        this.Test();
        this.TestEntityFunc();
        this.TestPlayerFunc();
        LogUtility.Log(`TestSystem init success.`);
    }

    protected OnRelease(): void {
        LogUtility.Log(`TestSystem release success.`);
    }

    private Test(): void {
        LogUtility.Error("系统测试接口----------------hello world");
        this.TriggerEvent(EventID.TEST_EVENT, ["TestSystem 触发事件 TEST_EVENT 事件"]);
        this.SendScript("test", ["TestSystem 执行 test 脚本"]);
    }

    private TestEntityFunc(): void {

        let IEntityData: IEntityData = {
            uid: "123456789", entity_type: CommonEnum.EntityType.NPC, class_id: 1000,
            Load: function (data: object): void {

            },
            ReadData: function (key: string) {

            }
        };
        let entitySys = this.GetSystem<IEntitySystem>(SystemID.ENTITY_SYSTEM);

        // 创建实体
        let entity = entitySys.CreateEntity(IEntityData);
        if (entity)
            LogUtility.Error(`创建实体 uid:${entity.GetUID()} entity_type:${entity.GetEntityType()} class_id:${entity.GetClassID()} success`);
    }

    private TestPlayerFunc(): void {
        // 读取玩家配置表
        let palyerModel = this.GetModel<IPlayerModel>(ModelID.PLAYER_MODEL);
        let row = palyerModel.GetPlayerRow(CommonConst.EntityClassID.PLAYER_ID);
        if (row == null)
            return;

        let name = row.GetDataOfString("name");
        let entitySys = this.GetSystem<IEntitySystem>(SystemID.ENTITY_SYSTEM);
        let playerSys = this.GetSystem<IPlayerSystem>(SystemID.PLAYER_SYSTEM);

        // 生成数据
        let playerData = playerSys.GeneratePlayerData(name);

        // 创建实体
        let player = entitySys.CreateEntity(playerData);
        if (player)
            LogUtility.Error(`创建玩家实体 uid:${player.GetUID()} entity_type:${player.GetEntityType()} class_id:${player.GetClassID()} name:${player.ReadData("name")} success`);
    }
}