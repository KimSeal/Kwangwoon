`timescale 1ns/100ps//choose time scale
module tb_XOR;//test two input-XOR
	reg tb_a, tb_b;
	wire tb_y0, tb_y1;
	
	_XOR U0_XOR(tb_a, tb_b, tb_y0);//result of XOR
	
	initial begin
	tb_a=0; tb_b=0;//result = 0
	#10;	tb_a=0;tb_b=1;//result = 1
	#10;	tb_a=1;tb_b=0;//result = 1
	#10;	tb_a=1;tb_b=1;//result = 0
	#10;
	end//finish test
endmodule
