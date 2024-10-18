# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\tejasvissapragada\lab1b\lab1b_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\tejasvissapragada\lab1b\lab1b_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {lab1b_platform}\
-hw {C:\Users\tejasvissapragada\Documents\cs153a\vivado\lab1a_vivado\project_1\design_1_wrapper.xsa}\
-out {C:/Users/tejasvissapragada/lab1b}

platform write
domain create -name {standalone_microblaze_0} -display-name {standalone_microblaze_0} -os {standalone} -proc {microblaze_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {lab1b_platform}
platform generate -quick
bsp reload
bsp setdriver -ip sevenSeg_0 -driver generic -ver 3.0 3.1
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
platform generate
platform generate -domains standalone_microblaze_0 
