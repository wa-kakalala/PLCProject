# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\wkk\Desktop\HuaWeiProject\PLCProject\02_zynq7020\ps\zynq7020\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\wkk\Desktop\HuaWeiProject\PLCProject\02_zynq7020\ps\zynq7020\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {zynq7020}\
-hw {C:\Users\wkk\Desktop\HuaWeiProject\PLCProject\02_zynq7020\pl\system_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/wkk/Desktop/HuaWeiProject/PLCProject/02_zynq7020/ps}

platform write
platform generate -domains 
platform active {zynq7020}
platform generate
platform clean
platform generate
platform clean
