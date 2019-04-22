// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2007 - 2017 Realtek Corporation */

/* ************************************************************
 * include files
 * ************************************************************ */
#include "mp_precomp.h"
#include "phydm_precomp.h"

#if (defined(CONFIG_PATH_DIVERSITY))
void
odm_pathdiv_debug(
	void		*p_dm_void,
	u32		*const dm_value,
	u32		*_used,
	char		*output,
	u32		*_out_len
)
{
	struct PHY_DM_STRUCT		*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _ODM_PATH_DIVERSITY_			*p_dm_path_div  = &(p_dm->dm_path_div);
	u32 used = *_used;
	u32 out_len = *_out_len;

	p_dm->path_select = (dm_value[0] & 0xf);
	PHYDM_SNPRINTF((output + used, out_len - used, "Path_select = (( 0x%x ))\n", p_dm->path_select));

	/* 2 [Fix path] */
	if (p_dm->path_select != PHYDM_AUTO_PATH) {
		PHYDM_SNPRINTF((output + used, out_len - used, "Trun on path  [%s%s%s%s]\n",
				((p_dm->path_select) & 0x1) ? "A" : "",
				((p_dm->path_select) & 0x2) ? "B" : "",
				((p_dm->path_select) & 0x4) ? "C" : "",
				((p_dm->path_select) & 0x8) ? "D" : ""));

		phydm_dtp_fix_tx_path(p_dm, p_dm->path_select);
	} else
		PHYDM_SNPRINTF((output + used, out_len - used, "%s\n", "Auto path"));

	*_used = used;
	*_out_len = out_len;
}

#endif /*  #if(defined(CONFIG_PATH_DIVERSITY)) */

void
phydm_c2h_dtp_handler(
	void	*p_dm_void,
	u8   *cmd_buf,
	u8	cmd_len
)
{
#if (defined(CONFIG_PATH_DIVERSITY))
	struct PHY_DM_STRUCT		*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _ODM_PATH_DIVERSITY_		*p_dm_path_div  = &(p_dm->dm_path_div);

	u8  macid = cmd_buf[0];
	u8  target = cmd_buf[1];
	u8  nsc_1 = cmd_buf[2];
	u8  nsc_2 = cmd_buf[3];
	u8  nsc_3 = cmd_buf[4];

	PHYDM_DBG(p_dm, DBG_PATH_DIV, ("Target_candidate = (( %d ))\n", target));
	/*
	if( (nsc_1 >= nsc_2) &&  (nsc_1 >= nsc_3))
	{
		phydm_dtp_fix_tx_path(p_dm, p_dm_path_div->ant_candidate_1);
	}
	else	if( nsc_2 >= nsc_3)
	{
		phydm_dtp_fix_tx_path(p_dm, p_dm_path_div->ant_candidate_2);
	}
	else
	{
		phydm_dtp_fix_tx_path(p_dm, p_dm_path_div->ant_candidate_3);
	}
	*/
#endif
}

void
odm_path_diversity(
	void	*p_dm_void
)
{
#if (defined(CONFIG_PATH_DIVERSITY))
	struct PHY_DM_STRUCT		*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	if (!(p_dm->support_ability & ODM_BB_PATH_DIV)) {
		PHYDM_DBG(p_dm, DBG_PATH_DIV, ("Return: Not Support PathDiv\n"));
		return;
	}
#endif
}

void
phydm_path_diversity_init(
	void	*p_dm_void
)
{
#if (defined(CONFIG_PATH_DIVERSITY))
	struct PHY_DM_STRUCT		*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	/*p_dm->support_ability |= ODM_BB_PATH_DIV;*/

	if (*(p_dm->p_mp_mode) == true)
		return;

	if (!(p_dm->support_ability & ODM_BB_PATH_DIV)) {
		PHYDM_DBG(p_dm, DBG_PATH_DIV, ("Return: Not Support PathDiv\n"));
		return;
	}
#endif
}
