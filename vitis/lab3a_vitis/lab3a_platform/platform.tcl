# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\tejasvissapragada\Documents\cs153a\vitis\lab3a_vitis\lab3a_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\tejasvissapragada\Documents\cs153a\vitis\lab3a_vitis\lab3a_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {lab3a_platform}\
-hw {C:\Users\tejasvissapragada\Documents\cs153a\vivado\lab3b_vivado\design_1_wrapper.xsa}\
-proc {microblaze_0} -os {standalone} -out {C:/Users/tejasvissapragada/Documents/cs153a/vitis/lab3a_vitis}

platform write
platform generate -domains 
platform active {lab3a_platform}
platform generate
platform generate -domains standalone_domain 
platform active {lab3a_platform}
platform generate -domains 
