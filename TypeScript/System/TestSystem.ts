/*
 * @Author: linb
 * @Date: 2024-04-12 11:06:11
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { SystemBase } from "../Abstract/SystemBase";
import { CommonEnum } from "../Const/CommonEnum";
import { EventID } from "../Const/EventID";
import { SystemID } from "../Const/SystemID";
import { IEntityData } from "../Data/IEntityData";
import { LogUtility } from "../Utility/LogUtility";
import { IEntitySystem } from "./Entity/IEntitySystem";

export class TestSystem extends SystemBase {
    protected GetSystemID(): number {
        return SystemID.TEST_SYSTEM;
    }

    protected OnInit(): void {
        this.Test();
        this.TestEntityFunc();
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

        let IEntityData: IEntityData = { uid: "123456789", entity_type: CommonEnum.EntityType.NPC, class_id: 1000 };
        let entitySys = this.GetSystem<IEntitySystem>(SystemID.ENTITY_SYSTEM);

        // 创建实体
        let entity = entitySys.CreateEntity(IEntityData);
        if (entity)
            LogUtility.Error(`创建实体 uid:${entity.GetUID()} entity_type:${entity.GetEntityType()} class_id:${entity.GetClassID()} success`);
    }
}