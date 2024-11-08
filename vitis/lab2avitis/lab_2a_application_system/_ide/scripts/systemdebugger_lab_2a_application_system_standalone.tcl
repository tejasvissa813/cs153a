# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\ranchen\Downloads\lab2avitis\lab2avitis\lab_2a_application_system\_ide\scripts\systemdebugger_lab_2a_application_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\ranchen\Downloads\lab2avitis\lab2avitis\lab_2a_application_system\_ide\scripts\systemdebugger_lab_2a_application_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
loadhw -hw C:/Users/ranchen/Downloads/lab2avitis/lab2avitis/lab_2a_hardware/export/lab_2a_hardware/hw/lab_2a_debug.xsa -regs
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow C:/Users/ranchen/Downloads/lab2avitis/lab2avitis/lab_2a_application/Debug/lab_2a_application.elf
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
con
