# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\ranchen\Documents\GitHub\cs153a\vitis\lab2avitis\lab2a_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\ranchen\Documents\GitHub\cs153a\vitis\lab2avitis\lab2a_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {lab2a_platform}\
-hw {C:\Users\ranchen\Documents\GitHub\cs153a\vivado\lab2a_vivado\lab2a.xsa}\
-proc {microblaze_0} -os {standalone} -out {C:/Users/ranchen/Documents/GitHub/cs153a/vitis/lab2avitis}

platform write
platform generate -domains 
platform active {lab2a_platform}
platform generate
