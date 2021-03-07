































//clk = 100mhz
//size 16384 0.169 ms
//size 32768 0.333 ms
//size 65536 0.661 ms
//size 131072 1.316 ms (prefer)
//size 262144 2.627 ms
//size 524288 5.243 ms
#include "ap_int.h"
#define size 524288 //size of SORCE
#define core 16 //cores //112
#define contig 32 //can not change

void test(
//input
ap_uint<8> INPUT[size],
ap_uint<8> INPUT_L[core*contig],
//result
ap_uint<32> OUTPUT[core]
){
//////////////////////////////////////////////////////////ports
#pragma HLS INTERFACE s_axilite register port=INPUT
#pragma HLS INTERFACE s_axilite register port=INPUT_L
#pragma HLS INTERFACE s_axilite register port=OUTPUT
#pragma HLS INTERFACE ap_ctrl_none port=return
//////////////////////////////////////////////////////////memory
int i,j,k;//use for loop
ap_uint<2> data_input[contig+1];
ap_uint<1> data_input_en[contig+1];
ap_uint<2> data_input_tran[1];
#pragma HLS ARRAY_RESHAPE variable=data_input_tran complete dim=1
ap_uint<1> data_input_tran_en[1];
#pragma HLS ARRAY_RESHAPE variable=data_input_tran_en complete dim=1
ap_uint<2> data_input_l[core*contig];
#pragma HLS ARRAY_RESHAPE variable=data_input_l complete dim=1
ap_uint<2> data_output[core];
#pragma HLS ARRAY_RESHAPE variable=data_output complete dim=1
ap_uint<1> data_output_en[core];
#pragma HLS ARRAY_RESHAPE variable=data_output_en complete dim=1
//////////////////////////////////////////////////////////INPUT_L
for(i = 0; i < (core*contig); i++){
#pragma HLS PIPELINE rewind
	if     (INPUT[i]==65) data_input_l[i]=0;//A 1 00
	else if(INPUT[i]==71) data_input_l[i]=1;//G 1 01
	else if(INPUT[i]==67) data_input_l[i]=2;//C 1 10
	else if(INPUT[i]==84) data_input_l[i]=3;//T 1 11
	else                  data_input_l[i]=0;//space 0 00
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////compute cycle start//////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////INPUT
for(i = 0; i < size; i++){
#pragma HLS PIPELINE rewind
	//trans data from mem to reg
	if     (INPUT[i]==65) {data_input_tran_en[0]=1; data_input_tran[0]=0;}//A 1 00
	else if(INPUT[i]==71) {data_input_tran_en[0]=1; data_input_tran[0]=1;}//G 1 01
	else if(INPUT[i]==67) {data_input_tran_en[0]=1; data_input_tran[0]=2;}//C 1 10
	else if(INPUT[i]==84) {data_input_tran_en[0]=1; data_input_tran[0]=3;}//T 1 11
	else                  {data_input_tran_en[0]=0; data_input_tran[0]=0;}//space 0 00
	//pipeline for parallel
	data_input[29]=data_input[28]; data_input_en[29]=data_input_en[28];
	data_input[28]=data_input[27]; data_input_en[28]=data_input_en[27];
	data_input[27]=data_input[26]; data_input_en[27]=data_input_en[26];
	data_input[26]=data_input[25]; data_input_en[26]=data_input_en[25];
	data_input[25]=data_input[24]; data_input_en[25]=data_input_en[24];
	data_input[24]=data_input[23]; data_input_en[24]=data_input_en[23];
	data_input[23]=data_input[22]; data_input_en[23]=data_input_en[22];
	data_input[22]=data_input[21]; data_input_en[22]=data_input_en[21];
	data_input[21]=data_input[20]; data_input_en[21]=data_input_en[20];
	data_input[20]=data_input[19]; data_input_en[20]=data_input_en[19];
	data_input[19]=data_input[18]; data_input_en[19]=data_input_en[18];
	data_input[18]=data_input[17]; data_input_en[18]=data_input_en[17];
	data_input[17]=data_input[16]; data_input_en[17]=data_input_en[16];
	data_input[16]=data_input[15]; data_input_en[16]=data_input_en[15];
	data_input[15]=data_input[14]; data_input_en[15]=data_input_en[14];
	data_input[14]=data_input[13]; data_input_en[14]=data_input_en[13];
	data_input[13]=data_input[12]; data_input_en[13]=data_input_en[12];
	data_input[12]=data_input[11]; data_input_en[12]=data_input_en[11];
	data_input[11]=data_input[10]; data_input_en[11]=data_input_en[10];
	data_input[10]=data_input[9]; data_input_en[10]=data_input_en[9];
	data_input[9]=data_input[8]; data_input_en[9]=data_input_en[8];
	data_input[8]=data_input[7]; data_input_en[8]=data_input_en[7];
	data_input[7]=data_input[6]; data_input_en[7]=data_input_en[6];
	data_input[6]=data_input[5]; data_input_en[6]=data_input_en[5];
	data_input[5]=data_input[4]; data_input_en[5]=data_input_en[4];
	data_input[4]=data_input[3]; data_input_en[4]=data_input_en[3];
	data_input[3]=data_input[2]; data_input_en[3]=data_input_en[2];
	data_input[2]=data_input[1]; data_input_en[2]=data_input_en[1];
	data_input[1]=data_input[0]; data_input_en[1]=data_input_en[0];
	data_input[0]=data_input_tran[0]; data_input_en[0]=data_input_tran_en[0];
	//compute core //parallel
	for(j = 0; j < core; j++){
		if(
			((data_input_en[0]+data_input_en[1]+data_input_en[2]+data_input_en[3]+
			data_input_en[4]+data_input_en[5]+data_input_en[6]+data_input_en[7]+
			data_input_en[8]+data_input_en[9]+data_input_en[10]+data_input_en[11]+
			data_input_en[12]+data_input_en[13]+data_input_en[14]+data_input_en[15]+
			data_input_en[16]+data_input_en[17]+data_input_en[18]+data_input_en[19]+
			data_input_en[20]+data_input_en[21]+data_input_en[22]+data_input_en[23]+
			data_input_en[24]+data_input_en[25]+data_input_en[26]+data_input_en[27]+
			data_input_en[28]+data_input_en[29])==30)
			&&
			((( data_input[29] == data_input_l[(j*contig)+0] )+
			( data_input[28] == data_input_l[(j*contig)+1] )+
			( data_input[27] == data_input_l[(j*contig)+2] )+
			( data_input[26] == data_input_l[(j*contig)+3] )+
			( data_input[25] == data_input_l[(j*contig)+4] )+
			( data_input[24] == data_input_l[(j*contig)+5] )+
			( data_input[23] == data_input_l[(j*contig)+6] )+
			( data_input[22] == data_input_l[(j*contig)+7] )+
			( data_input[21] == data_input_l[(j*contig)+8] )+
			( data_input[20] == data_input_l[(j*contig)+9] )+
			( data_input[19] == data_input_l[(j*contig)+10] )+
			( data_input[18] == data_input_l[(j*contig)+11] )+
			( data_input[17] == data_input_l[(j*contig)+12] )+
			( data_input[16] == data_input_l[(j*contig)+13] )+
			( data_input[15] == data_input_l[(j*contig)+14] )+
			( data_input[14] == data_input_l[(j*contig)+15] )+
			( data_input[13] == data_input_l[(j*contig)+16] )+
			( data_input[12] == data_input_l[(j*contig)+17] )+
			( data_input[11] == data_input_l[(j*contig)+18] )+
			( data_input[10] == data_input_l[(j*contig)+19] )+
			( data_input[9] == data_input_l[(j*contig)+20] )+
			( data_input[8] == data_input_l[(j*contig)+21] )+
			( data_input[7] == data_input_l[(j*contig)+22] )+
			( data_input[6] == data_input_l[(j*contig)+23] )+
			( data_input[5] == data_input_l[(j*contig)+24] )+
			( data_input[4] == data_input_l[(j*contig)+25] )+
			( data_input[3] == data_input_l[(j*contig)+26] )+
			( data_input[2] == data_input_l[(j*contig)+27] )+
			( data_input[1] == data_input_l[(j*contig)+28] ))==29)
		)
		{ data_output_en[j]=1; data_output[j]=data_input[0];}
	}
}
//////////////////////////////////////////////////////////RESULT
for(i = 0; i < core; i++){
#pragma HLS PIPELINE rewind
	if((data_output_en[i]==1)&(data_output[i]==0))      OUTPUT[i]=65;//A 1 00
	else if((data_output_en[i]==1)&(data_output[i]==1)) OUTPUT[i]=71;//G 1 01
	else if((data_output_en[i]==1)&(data_output[i]==2)) OUTPUT[i]=67;//C 1 10
	else if((data_output_en[i]==1)&(data_output[i]==3)) OUTPUT[i]=84;//T 1 11
	else                                                OUTPUT[i]=32;//space
}
}
//////////////////////////////////////////////////////////compute cycle end//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////












