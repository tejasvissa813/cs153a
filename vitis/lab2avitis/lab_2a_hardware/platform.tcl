# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\ranchen\Downloads\lab2avitis\lab_2a_hardware\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\ranchen\Downloads\lab2avitis\lab_2a_hardware\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {lab_2a_hardware}\
-hw {C:\Users\ranchen\Downloads\cs153a-main\cs153a-main\vivado\lab2a_vivado\lab2a.xsa}\
-proc {microblaze_0} -os {standalone} -out {C:/Users/ranchen/Downloads/lab2avitis}

platform write
platform generate -domains 
platform active {lab_2a_hardware}
platform generate
platform generate
platform active {lab_2a_hardware}
platform config -updatehw {C:/Users/ranchen/Downloads/lab2a_vivado/lab2a_vivado/lab_2a_debug.xsa}
platform generate -domains 
platform active {lab_2a_hardware}
platform generate -domains 
