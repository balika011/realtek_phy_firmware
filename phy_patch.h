#ifndef __PHY_PATCH_H__
#define __PHY_PATCH_H__

#include <linux/types.h>

typedef enum rtk_phypatch_type_e
{
	PHY_PATCH_TYPE_NONE = 0,
	PHY_PATCH_TYPE_TOP = 1,
	PHY_PATCH_TYPE_SDS,
	PHY_PATCH_TYPE_AFE,
	PHY_PATCH_TYPE_UC,
	PHY_PATCH_TYPE_UC2,
	PHY_PATCH_TYPE_NCTL0,
	PHY_PATCH_TYPE_NCTL1,
	PHY_PATCH_TYPE_NCTL2,
	PHY_PATCH_TYPE_ALGXG,
	PHY_PATCH_TYPE_ALG1G,
	PHY_PATCH_TYPE_NORMAL,
	PHY_PATCH_TYPE_DATARAM,
	PHY_PATCH_TYPE_RTCT,
	PHY_PATCH_TYPE_END
} rtk_phypatch_type_t;

#define RTK_PATCH_TYPE_FLOW(_id) (PHY_PATCH_TYPE_END + _id)
#define RTK_PATCH_TYPE_FLOWID_MAX PHY_PATCH_TYPE_END
#define RTK_PATCH_SEQ_MAX (PHY_PATCH_TYPE_END + RTK_PATCH_TYPE_FLOWID_MAX - 1)

typedef enum rtk_phypatch_op_e
{
	RTK_PATCH_OP_PHY,
	RTK_PATCH_OP_PHY_WAIT,
	RTK_PATCH_OP_PHY_WAIT_NOT,
	RTK_PATCH_OP_PHYOCP,
	RTK_PATCH_OP_PHYOCP_BC62,
	RTK_PATCH_OP_TOP,
	RTK_PATCH_OP_TOPOCP,
	RTK_PATCH_OP_PSDS0,
	RTK_PATCH_OP_PSDS1,
	RTK_PATCH_OP_MSDS,
	RTK_PATCH_OP_MAC,
	RTK_PATCH_OP_DELAY_MS
} rtk_phypatch_op_t;

typedef enum rtk_phypatch_cmp_e
{
	RTK_PATCH_CMP_W,	/* write */
	RTK_PATCH_CMP_WC,	/* compare */
	RTK_PATCH_CMP_SWC,	/* sram compare */
	RTK_PATCH_CMP_WS	/* skip */
} rtk_phypatch_cmp_t;

typedef struct rtk_hwpatch_s
{
	__u8 patch_op;
	__u8 portmask;
	__u16 pagemmd;
	__u16 addr;
	__u8 msb;
	__u8 lsb;
	__u16 data;
	__u8 compare_op;
	__u16 sram_p;
	__u16 sram_rr;
	__u16 sram_rw;
	__u16 sram_a;
} rtk_hwpatch_t;

typedef struct rtk_hwpatch_mainline_s
{
	__u8 patch_op;
	__u8 portmask;
	__u16 pagemmd;
	__u16 addr;
	__u8 msb;
	__u8 lsb;
	__u16 data;
} __attribute__((packed)) rtk_hwpatch_mainline_t;

struct phy_device;

typedef struct rt_phy_patch_db_s
{
	/* patch operation */
	int (*fPatch_op)(struct phy_device *phydev, rtk_hwpatch_mainline_t *pPatch_data);
	int (*fPatch_flow)(struct phy_device *phydev, __u8 patch_flow);

	/* patch data */
	struct
	{
		rtk_phypatch_type_t patch_type;
		union
		{
			struct
			{
				rtk_hwpatch_t *conf;
				__u32 size;
			} data;
			__u8 flow_id;
		} patch;
	} table[RTK_PATCH_SEQ_MAX];

} rt_phy_patch_db_t;

struct phy_device
{
	FILE *f;
	rt_phy_patch_db_t *patch;
};

/*
   patch type  PHY_PATCH_TYPE_NONE => empty
   patch type: PHY_PATCH_TYPE_TOP ~ (PHY_PATCH_TYPE_END-1)  => data array
   patch type: PHY_PATCH_TYPE_END ~ (PHY_PATCH_TYPE_END + RTK_PATCH_TYPE_FLOW_MAX)  => flow
*/
#define RTK_PATCH_TYPE_IS_DATA(_patch_type)    (_patch_type > PHY_PATCH_TYPE_NONE && _patch_type < PHY_PATCH_TYPE_END)
#define RTK_PATCH_TYPE_IS_FLOW(_patch_type)    (_patch_type >= PHY_PATCH_TYPE_END && _patch_type <= (PHY_PATCH_TYPE_END + RTK_PATCH_TYPE_FLOWID_MAX))

#define PHYPATCH_DB_GET(_pPhy_device, _pPatchDb) \
    do { \
        rt_phy_patch_db_t *_pDb = (_pPhy_device)->patch; _pPatchDb = _pDb; \
    } while(0)

#define PHYPATCH_TABLE_ASSIGN(_pPatchDb, _idx, _patch_type, _para) \
    do { \
        if (RTK_PATCH_TYPE_IS_DATA(_patch_type)) { \
            _pPatchDb->table[_idx].patch_type = _patch_type; \
            _pPatchDb->table[_idx].patch.data.conf = _para; \
            _pPatchDb->table[_idx].patch.data.size = sizeof(_para); \
        } \
        else if (RTK_PATCH_TYPE_IS_FLOW(_patch_type)) { \
            _pPatchDb->table[_idx].patch_type = _patch_type; \
            _pPatchDb->table[_idx].patch.flow_id = _patch_type; \
        } \
        else { \
            _pPatchDb->table[_idx].patch_type = PHY_PATCH_TYPE_NONE; \
        } \
    } while(0)

int phy_patch_op(rt_phy_patch_db_t *pPhy_patchDb, struct phy_device *phydev, __u8 patch_op, __u16 portmask, __u16 pagemmd, __u16 addr, __u8 msb, __u8 lsb, __u16 data);

int phy_patch_rtl8261n_db_init(struct phy_device *phydev, rt_phy_patch_db_t **pPhy_patchDb);
int phy_patch_rtl8261n_lp_db_init(struct phy_device *phydev, rt_phy_patch_db_t **pPhy_patchDb);
int phy_patch_rtl8264b_db_init(struct phy_device *phydev, rt_phy_patch_db_t **pPhy_patchDb);

#endif
