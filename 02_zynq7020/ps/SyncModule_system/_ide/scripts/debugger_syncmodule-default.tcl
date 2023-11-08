# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\wkk\Desktop\HuaWeiProject\PLCProject\02_zynq7020\ps\SyncModule_system\_ide\scripts\debugger_syncmodule-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\wkk\Desktop\HuaWeiProject\PLCProject\02_zynq7020\ps\SyncModule_system\_ide\scripts\debugger_syncmodule-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/wkk/Desktop/HuaWeiProject/PLCProject/02_zynq7020/ps/zynq7020/export/zynq7020/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/wkk/Desktop/HuaWeiProject/PLCProject/02_zynq7020/ps/SyncModule/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/wkk/Desktop/HuaWeiProject/PLCProject/02_zynq7020/ps/SyncModule/Debug/SyncModule.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
