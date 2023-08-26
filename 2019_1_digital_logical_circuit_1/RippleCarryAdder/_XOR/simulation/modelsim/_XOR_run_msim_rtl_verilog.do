transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/COMS02/Desktop/hello/hello/_XOR {C:/Users/COMS02/Desktop/hello/hello/_XOR/_XOR.v}

vlog -vlog01compat -work work +incdir+C:/Users/COMS02/Desktop/hello/hello/_XOR {C:/Users/COMS02/Desktop/hello/hello/_XOR/tb_XOR.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneiv_hssi_ver -L cycloneiv_pcie_hip_ver -L cycloneiv_ver -L rtl_work -L work -voptargs="+acc"  tb_XOR

add wave *
view structure
view signals
run -all
