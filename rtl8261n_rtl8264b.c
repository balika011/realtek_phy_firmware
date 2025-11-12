#include <stdio.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <string.h>
#include <stdlib.h>

#include "phy_patch.h"

#include "conf_rtl8264b.c"
#include "conf_rtl8261n_c.c"
#include "conf_rtl8261n_c_lp.c"

static int phy_patch_rtl826x_op(struct phy_device *phydev, rtk_hwpatch_mainline_t *pPatch_data)
{
	fwrite(pPatch_data, 1, sizeof(rtk_hwpatch_mainline_t), phydev->f);
	return 0;
}

static int _phy_rtl826x_flow_r1(struct phy_device *phydev)
{
	int ret = 0;
	rt_phy_patch_db_t *pPatchDb = NULL;

	PHYPATCH_DB_GET(phydev, pPatchDb);

	// PHYReg_bit w $PHYID 0xb82 16 4 4 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xb82, 16, 4, 4, 0x1)) < 0)
		return ret;
	// PHYReg_bit w $PHYID 0xb82 16 4 4 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xb82, 16, 4, 4, 0x1)) < 0)
		return ret;

	// set patch_rdy [PHYReg_bit r $PHYID 0xb80 16 6 6] ; Wait for patch ready = 1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY_WAIT, 0xFF, 0xb80, 16, 6, 6, 1)) < 0)
		return ret;

	// PHYReg w $PHYID 0xa43 27 $0x8023
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 27, 15, 0, 0x8023)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 28 $0x3802
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 28, 15, 0, 0x3802)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 27 0xB82E
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 27, 15, 0, 0xB82E)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 28 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 28, 15, 0, 0x1)) < 0)
		return ret;

	return 0;
}

static int _phy_rtl826x_flow_r12(struct phy_device *phydev)
{
	int ret = 0;
	rt_phy_patch_db_t *pPatchDb = NULL;

	PHYPATCH_DB_GET(phydev, pPatchDb);

	// PHYReg_bit w $PHYID 0xb82 16 4 4 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xb82, 16, 4, 4, 0x1)) < 0)
		return ret;
	// PHYReg_bit w $PHYID 0xb82 16 4 4 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xb82, 16, 4, 4, 0x1)) < 0)
		return ret;

	// set patch_rdy [PHYReg_bit r $PHYID 0xb80 16 6 6] ; Wait for patch ready = 1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY_WAIT, 0xFF, 0xb80, 16, 6, 6, 1)) < 0)
		return ret;

	// PHYReg w $PHYID 0xa43 27 $0x8023
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 27, 15, 0, 0x8023)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 28 $0x3800
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 28, 15, 0, 0x3800)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 27 0xB82E
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 27, 15, 0, 0xB82E)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 28 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 28, 15, 0, 0x1)) < 0)
		return ret;

	return 0;
}

static int _phy_rtl826x_flow_r2(struct phy_device *phydev)
{
	int ret = 0;
	rt_phy_patch_db_t *pPatchDb = NULL;

	PHYPATCH_DB_GET(phydev, pPatchDb);

	// PHYReg w $PHYID 0xa43 27 0x0000
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 27, 15, 0, 0x0000)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 28 0x0000
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 28, 15, 0, 0x0000)) < 0)
		return ret;
	// PHYReg_bit w $PHYID 0xB82 23 0 0 0x0
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xB82, 23, 0, 0, 0x0)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 27 $0x8023
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 27, 15, 0, 0x8023)) < 0)
		return ret;
	// PHYReg w $PHYID 0xa43 28 0x0000
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa43, 28, 15, 0, 0x0000)) < 0)
		return ret;

	// PHYReg_bit w $PHYID 0xb82 16 4 4 0x0
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xb82, 16, 4, 4, 0x0)) < 0)
		return ret;
	// set patch_rdy [PHYReg_bit r $PHYID 0xb80 16 6 6] ; Wait for patch ready != 1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY_WAIT_NOT, 0xFF, 0xb80, 16, 6, 6, 1)) < 0)
		return ret;

	return 0;
}

static int _phy_rtl826x_flow_l1(struct phy_device *phydev)
{
	int ret = 0;
	rt_phy_patch_db_t *pPatchDb = NULL;

	PHYPATCH_DB_GET(phydev, pPatchDb);

	// PHYReg_bit w $PHYID 0xa4a 16 10 10 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa4a, 16, 10, 10, 0x1)) < 0)
		return ret;
	// PHYReg_bit w $PHYID 0xa4a 16 10 10 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa4a, 16, 10, 10, 0x1)) < 0)
		return ret;

	// set pcs_state [PHYReg_bit r $PHYID 0xa60 16 7 0] ; Wait for pcs state = 1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY_WAIT, 0xFF, 0xa60, 16, 7, 0, 1)) < 0)
		return ret;

	return 0;
}

static int _phy_rtl826x_flow_l2(struct phy_device *phydev)
{
	int ret = 0;
	rt_phy_patch_db_t *pPatchDb = NULL;

	PHYPATCH_DB_GET(phydev, pPatchDb);

	// PHYReg_bit w $PHYID 0xa4a 16 10 10 0x0
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY, 0xFF, 0xa4a, 16, 10, 10, 0x0)) < 0)
		return ret;

	// set pcs_state [PHYReg_bit r $PHYID 0xa60 16 7 0] ; Wait for pcs state != 1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHY_WAIT_NOT, 0xFF, 0xa60, 16, 7, 0, 1)) < 0)
		return ret;

	return 0;
}

static int _phy_rtl826x_flow_pi(struct phy_device *phydev)
{
	int ret = 0;
	rt_phy_patch_db_t *pPatchDb = NULL;

	PHYPATCH_DB_GET(phydev, pPatchDb);

	_phy_rtl826x_flow_l1(phydev);

	//  PP_PHYReg_bit w $PHYID 0xbf86 9 9 0x1; #SS_EN_XG = 1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 9, 9, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 8 8 0x0;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 8, 8, 0x0)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 7 7 0x1;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 7, 7, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 6 6 0x1;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 6, 6, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 5 5 0x1;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 5, 5, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 4 4 0x1;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 4, 4, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 6 6 0x0;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 6, 6, 0x0)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 9 9 0x0;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 9, 9, 0x0)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 7 7 0x0;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 7, 7, 0x0)) < 0)
		return ret;

	//   PP_PHYReg_bit w $PHYID 0xbf86 7 7 0x0;
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP_BC62, 0xFF, 0, 0, 0, 0, 0x0)) < 0)
		return ret;

	//   PP_PHYReg_bit w $PHYID 0xbc02 2 2 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbc02, 2, 2, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbc02 3 3 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbc02, 3, 3, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 6 6 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 6, 6, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 9 9 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 9, 9, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbf86 7 7 0x1
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbf86, 7, 7, 0x1)) < 0)
		return ret;
	//   PP_PHYReg_bit w $PHYID 0xbc04 9 2 0xff
	if ((ret = phy_patch_op(pPatchDb, phydev, RTK_PATCH_OP_PHYOCP, 0xFF, 31, 0xbc04, 9, 2, 0xff)) < 0)
		return ret;

	_phy_rtl826x_flow_l2(phydev);
	return 0;
}

static int phy_patch_rtl826x_flow(struct phy_device *phydev, __u8 flow_id)
{
    int ret = 0;

    switch (flow_id)
    {
        case RTK_PATCH_TYPE_FLOW(0):
            if ((ret = _phy_rtl826x_flow_r1(phydev)) < 0)
                return ret;
            break;
        case RTK_PATCH_TYPE_FLOW(6):
            if ((ret = _phy_rtl826x_flow_r12(phydev)) < 0)
                return ret;
            break;
        case RTK_PATCH_TYPE_FLOW(1):
            if ((ret = _phy_rtl826x_flow_r2(phydev)) < 0)
                return ret;
            break;

        case RTK_PATCH_TYPE_FLOW(2):
            if ((ret = _phy_rtl826x_flow_l1(phydev)) < 0)
                return ret;
            break;
        case RTK_PATCH_TYPE_FLOW(3):
            if ((ret = _phy_rtl826x_flow_l2(phydev)) < 0)
                return ret;
            break;

        case RTK_PATCH_TYPE_FLOW(4):
        	// this patch is the realtek specific one.
        	// as this is a dynamic one, it's implemented in the driver
                return ret;

        case RTK_PATCH_TYPE_FLOW(5):
            if ((ret = _phy_rtl826x_flow_pi(phydev)) < 0)
                return ret;
            break;

        default:
            return -EINVAL;
    }
    return 0;
}

int phy_patch_rtl8261n_db_init(struct phy_device *phydev, rt_phy_patch_db_t **pPhy_patchDb)
{
    int ret = 0;
    rt_phy_patch_db_t *patch_db = NULL;

	patch_db = malloc(sizeof(rt_phy_patch_db_t));
	if (!patch_db)
        return -ENOMEM;

    memset(patch_db, 0x0, sizeof(rt_phy_patch_db_t));

    patch_db->fPatch_op = phy_patch_rtl826x_op;
    patch_db->fPatch_flow = phy_patch_rtl826x_flow;

    PHYPATCH_TABLE_ASSIGN(patch_db,  0, RTK_PATCH_TYPE_FLOW(0), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  1, PHY_PATCH_TYPE_NCTL0, rtl8261n_c_nctl0_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  2, PHY_PATCH_TYPE_NCTL1, rtl8261n_c_nctl1_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  3, PHY_PATCH_TYPE_NCTL2, rtl8261n_c_nctl2_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  4, PHY_PATCH_TYPE_UC2, rtl8261n_c_uc2_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  5, PHY_PATCH_TYPE_UC, rtl8261n_c_uc_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  6, PHY_PATCH_TYPE_DATARAM, rtl8261n_c_dataram_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  7, RTK_PATCH_TYPE_FLOW(1), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  8, RTK_PATCH_TYPE_FLOW(2), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  9, PHY_PATCH_TYPE_ALGXG, rtl8261n_c_algxg_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 10, PHY_PATCH_TYPE_ALG1G, rtl8261n_c_alg_giga_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 11, PHY_PATCH_TYPE_NORMAL, rtl8261n_c_normal_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 12, PHY_PATCH_TYPE_TOP, rtl8261n_c_top_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 13, PHY_PATCH_TYPE_SDS, rtl8261n_c_sds_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 14, PHY_PATCH_TYPE_AFE, rtl8261n_c_afe_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 15, PHY_PATCH_TYPE_RTCT, rtl8261n_c_rtct_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 16, RTK_PATCH_TYPE_FLOW(3), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db, 17, RTK_PATCH_TYPE_FLOW(4), NULL);

    *pPhy_patchDb = patch_db;
    return ret;
}

int phy_patch_rtl8261n_lp_db_init(struct phy_device *phydev, rt_phy_patch_db_t **pPhy_patchDb)
{
    int ret = 0;
    rt_phy_patch_db_t *patch_db = NULL;

	patch_db = malloc(sizeof(rt_phy_patch_db_t));
	if (!patch_db)
        return -ENOMEM;

    memset(patch_db, 0x0, sizeof(rt_phy_patch_db_t));

    patch_db->fPatch_op = phy_patch_rtl826x_op;
    patch_db->fPatch_flow = phy_patch_rtl826x_flow;

    PHYPATCH_TABLE_ASSIGN(patch_db,  0, RTK_PATCH_TYPE_FLOW(0), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  1, PHY_PATCH_TYPE_NCTL0, rtl8261n_lp_c_nctl0_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  2, PHY_PATCH_TYPE_NCTL1, rtl8261n_lp_c_nctl1_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  3, PHY_PATCH_TYPE_NCTL2, rtl8261n_lp_c_nctl2_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  4, PHY_PATCH_TYPE_UC2, rtl8261n_lp_c_uc2_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  5, PHY_PATCH_TYPE_UC, rtl8261n_lp_c_uc_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  6, PHY_PATCH_TYPE_DATARAM, rtl8261n_lp_c_dataram_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  7, RTK_PATCH_TYPE_FLOW(1), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  8, RTK_PATCH_TYPE_FLOW(2), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  9, PHY_PATCH_TYPE_ALGXG, rtl8261n_lp_c_algxg_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 10, PHY_PATCH_TYPE_ALG1G, rtl8261n_lp_c_alg_giga_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 11, PHY_PATCH_TYPE_NORMAL, rtl8261n_lp_c_normal_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 12, PHY_PATCH_TYPE_TOP, rtl8261n_lp_c_top_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 13, PHY_PATCH_TYPE_SDS, rtl8261n_lp_c_sds_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 14, PHY_PATCH_TYPE_AFE, rtl8261n_lp_c_afe_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 15, PHY_PATCH_TYPE_RTCT, rtl8261n_lp_c_rtct_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 16, RTK_PATCH_TYPE_FLOW(3), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db, 17, RTK_PATCH_TYPE_FLOW(4), NULL);

    *pPhy_patchDb = patch_db;
    return ret;
}

int phy_patch_rtl8264b_db_init(struct phy_device *phydev, rt_phy_patch_db_t **pPhy_patchDb)
{
    int ret = 0;
    rt_phy_patch_db_t *patch_db = NULL;

	patch_db = malloc(sizeof(rt_phy_patch_db_t));
	if (!patch_db)
        return -ENOMEM;

    memset(patch_db, 0x0, sizeof(rt_phy_patch_db_t));

    patch_db->fPatch_op = phy_patch_rtl826x_op;
    patch_db->fPatch_flow = phy_patch_rtl826x_flow;

    PHYPATCH_TABLE_ASSIGN(patch_db,  0, RTK_PATCH_TYPE_FLOW(6), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  1, PHY_PATCH_TYPE_NCTL0, rtl8264b_nctl0_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  2, PHY_PATCH_TYPE_NCTL1, rtl8264b_nctl1_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  3, PHY_PATCH_TYPE_NCTL2, rtl8264b_nctl2_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  4, PHY_PATCH_TYPE_UC2, rtl8264b_uc2_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  5, PHY_PATCH_TYPE_UC, rtl8264b_uc_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  6, PHY_PATCH_TYPE_DATARAM, rtl8264b_dataram_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db,  7, RTK_PATCH_TYPE_FLOW(1), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  8, RTK_PATCH_TYPE_FLOW(2), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db,  9, PHY_PATCH_TYPE_ALGXG, rtl8264b_algxg_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 10, PHY_PATCH_TYPE_ALG1G, rtl8264b_alg_giga_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 11, PHY_PATCH_TYPE_NORMAL, rtl8264b_normal_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 12, PHY_PATCH_TYPE_TOP, rtl8264b_top_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 13, PHY_PATCH_TYPE_SDS, rtl8264b_sds_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 14, PHY_PATCH_TYPE_AFE, rtl8264b_afe_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 15, PHY_PATCH_TYPE_RTCT, rtl8264b_rtct_conf);
    PHYPATCH_TABLE_ASSIGN(patch_db, 16, RTK_PATCH_TYPE_FLOW(3), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db, 17, RTK_PATCH_TYPE_FLOW(5), NULL);
    PHYPATCH_TABLE_ASSIGN(patch_db, 18, RTK_PATCH_TYPE_FLOW(4), NULL);

    *pPhy_patchDb = patch_db;
    return ret;
}
