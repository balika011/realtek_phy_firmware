#include <stdio.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <string.h>
#include <stdlib.h>

#include "phy_patch.h"

int phy_patch_op(rt_phy_patch_db_t *pPhy_patchDb, struct phy_device *phydev, __u8 patch_op, __u16 portmask, __u16 pagemmd, __u16 addr, __u8 msb, __u8 lsb, __u16 data)
{
    rtk_hwpatch_mainline_t op;

    op.patch_op = patch_op;
    op.portmask = portmask;
    op.pagemmd  = pagemmd;
    op.addr     = addr;
    op.msb      = msb;
    op.lsb      = lsb;
    op.data     = data;

    return pPhy_patchDb->fPatch_op(phydev, &op);
}

static int _phy_patch_process(struct phy_device *phydev, rtk_hwpatch_t *pPatch, int size)
{
	int i = 0;
	int ret = 0;
	int n;
	rtk_hwpatch_mainline_t patch;
	rt_phy_patch_db_t *pPatchDb = NULL;

	PHYPATCH_DB_GET(phydev, pPatchDb);

	if (size <= 0)
	{
		return 0;
	}
	n = size / sizeof(rtk_hwpatch_t);

	for (i = 0; i < n; i++)
	{
		patch.patch_op = pPatch[i].patch_op;
		patch.portmask = pPatch[i].portmask;
		patch.pagemmd = pPatch[i].pagemmd;
		patch.addr = pPatch[i].addr;
		patch.msb = pPatch[i].msb;
		patch.lsb = pPatch[i].lsb;
		patch.data = pPatch[i].data;

		ret = pPatchDb->fPatch_op(phydev, &patch);
		if (ret < 0)
		{
			printf("%s failed! %u[%u][0x%X][0x%X][0x%X] ret=0x%X\n", __FUNCTION__,
					   i + 1, patch.patch_op, patch.pagemmd, patch.addr, patch.data, ret);
			return ret;
		}
	}
	return 0;
}

static int phy_patch(struct phy_device *phydev)
{
	int ret = 0;
	__u32 i = 0;
	__u8 patch_type = 0;
	rt_phy_patch_db_t *pPatchDb = NULL;

	PHYPATCH_DB_GET(phydev, pPatchDb);

	if ((pPatchDb == NULL) || (pPatchDb->fPatch_op == NULL) || (pPatchDb->fPatch_flow == NULL))
	{
		return -EINVAL;
	}

	for (i = 0; i < RTK_PATCH_SEQ_MAX; i++)
	{
		patch_type = pPatchDb->table[i].patch_type;

		if (RTK_PATCH_TYPE_IS_DATA(patch_type))
		{
			ret = _phy_patch_process(phydev, pPatchDb->table[i].patch.data.conf, pPatchDb->table[i].patch.data.size);
			if (ret < 0)
			{
				printf("id:%u patch-%u failed. ret:0x%X\n", i, patch_type, ret);
				return ret;
			}
		}
		else if (RTK_PATCH_TYPE_IS_FLOW(patch_type))
		{
			ret = pPatchDb->fPatch_flow(phydev, pPatchDb->table[i].patch.flow_id);
			if (ret < 0)
			{
				printf("id:%u patch-%u failed. ret:0x%X\n", i, patch_type, ret);
				return ret;
			};
		}
		else
		{
			break;
		}
	}

	return 0;
}

void rtl8261n()
{
	printf("rtl8261n\n");
	struct phy_device *phydev = malloc(sizeof(struct phy_device));
	phydev->f = fopen("rtl8261n.bin", "wb");

	phy_patch_rtl8261n_db_init(phydev, &phydev->patch);

	phy_patch(phydev);

	fclose(phydev->f);
	free(phydev->patch);
	free(phydev);
}

// initialize chip in low power consumption mode and supported max cable length will downgrade to 50M
void rtl8261n_lp()
{
	printf("rtl8261n_lp\n");
	struct phy_device *phydev = malloc(sizeof(struct phy_device));
	phydev->f = fopen("rtl8261n_lp.bin", "wb");

	phy_patch_rtl8261n_lp_db_init(phydev, &phydev->patch);

	phy_patch(phydev);

	fclose(phydev->f);
	free(phydev->patch);
	free(phydev);
}

void rtl8264b()
{
	printf("rtl8264b\n");
	struct phy_device *phydev = malloc(sizeof(struct phy_device));
	phydev->f = fopen("rtl8264b.bin", "wb");

	phy_patch_rtl8264b_db_init(phydev, &phydev->patch);

	phy_patch(phydev);

	fclose(phydev->f);
	free(phydev->patch);
	free(phydev);
}

int main()
{
	rtl8261n();
	rtl8261n_lp();
	rtl8264b();

	return 0;
}
