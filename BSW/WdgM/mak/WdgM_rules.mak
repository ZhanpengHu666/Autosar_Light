############################################################################### 
# File Name  : WdgM_rules.mak 
# Description: Rules makefile 
#-----------------------------------------------------------------------------
# COPYRIGHT
#-----------------------------------------------------------------------------
# Copyright (c) 2018 by Vector Informatik GmbH.  All rights reserved.
#-----------------------------------------------------------------------------
# REVISION HISTORY
#-----------------------------------------------------------------------------
# Date         Version  Sign Description
# ----------   -------  ---- -------------------------------------------------
# 2016/02/18   1.00.00  chl  Initial Version of migrated WdgM_rules.mak
# 2018-04-27   1.01.00  chl  Additional generated make file added
#                            New template used
#-----------------------------------------------------------------------------
# TemplateVersion = 1.01
############################################################################### 

# Component Files
CC_FILES_TO_BUILD       += WdgM\WdgM.c WdgM\WdgM_Checkpoint.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\WdgM_Cfg.c

# Include additional generated make file. File(s) will be added to GENERATED_SOURCE_FILES
include $(GENDATA_DIR)\mak\WdgM_rules_generated.mak

# Library Settings
LIBRARIES_TO_BUILD      += WdgM
WdgM_FILES              += WdgM\WdgM.c WdgM\WdgM_Checkpoint.c

