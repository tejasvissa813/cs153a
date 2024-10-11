# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\ranchen\workspace\lab_1a\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\ranchen\workspace\lab_1a\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {lab_1a}\
-hw {C:\Users\ranchen\Downloads\project_1\project_1\design_1_wrapper.xsa}\
-proc {microblaze_0} -os {standalone} -out {C:/Users/ranchen/workspace}

platform write
platform generate -domains 
platform active {lab_1a}
bsp reload
bsp setdriver -ip sevenSeg_0 -driver generic -ver 3.0 3.1
bsp write
bsp reload
catch {bsp regenerate}
platform active {lab_1a}
bsp reload
platform generate
bsp write
platform generate -domains 
platform generate -domains standalone_domain 
platform active {lab_1a}
platform generate -domains 
