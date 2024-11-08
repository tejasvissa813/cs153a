# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\tejasvissapragada\Documents\cs153a\vitis\lab2b_vitis\lab2b_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\tejasvissapragada\Documents\cs153a\vitis\lab2b_vitis\lab2b_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {lab2b_platform}\
-hw {C:\Users\tejasvissapragada\Documents\cs153a\vivado\lab2b_vivado\design_1_wrapper.xsa}\
-proc {microblaze_0} -os {standalone} -out {C:/Users/tejasvissapragada/Documents/cs153a/vitis/lab2b_vitis}

platform write
platform generate -domains 
platform active {lab2b_platform}
bsp reload
bsp write
platform generate
platform generate
platform generate
