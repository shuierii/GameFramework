/*
 * @Author: linb
 * @Date: 2024-04-17 14:34:07
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { ModelBase } from "../../Abstract/ModelBase";
import { ModelID } from "../../Const/ModelID";
import { MainGame } from "../../MainGame";
import { LogUtility } from "../../Utility/LogUtility";
import { IPlayerModel } from "./IPlayerModel";

export class PlayerModel extends ModelBase implements IPlayerModel {

    private mPlayerTable: UE.TableData;

    protected GetModelID(): number {
        return ModelID.PLAYER_MODEL;
    }

    protected OnInit(): void {
        this.LoadPlayerTable();
    }

    protected OnRelease(): void {
        this.mPlayerTable = null;
    }

    /**
     * @description: 根据ID获取配置行数据
     * @param {number} classID
     * @return {*}
     */
    GetPlayerRow(classID: number): UE.RowData {
        if (this.mPlayerTable == null)
            return null;

        if (!this.mPlayerTable.ContainsByIKey(classID))
            return null;

        return this.mPlayerTable.GetRowByIKey(classID);
    }

    /**
     * @description: 加载玩家配置表
     * @return {*}
     */
    private LoadPlayerTable(): void {
        let fileName = "player";

        // 获取配置表文件路径
        let fileDirPath = UE.BlueprintPathsLibrary.ProjectContentDir() + "Etc/Table/" + fileName + ".csv";

        // 继承于带有初始化功能的子系统获取实例对象方式
        let tableMgr = UE.SubsystemBlueprintLibrary.GetGameInstanceSubsystem(MainGame.UEInstance, UE.TableMgr.StaticClass()) as UE.TableMgr;
        if (tableMgr == null) {
            LogUtility.Error(`get tableManager filed.`);
            return;
        }

        this.mPlayerTable = tableMgr.LoadTable(fileDirPath, fileName);
        if (this.mPlayerTable == null)
            LogUtility.Error(`load table ${fileName} filed.`);
        else
            LogUtility.Log(`玩家配置表 \n ${this.mPlayerTable.GetDesc()}`);
    }
}