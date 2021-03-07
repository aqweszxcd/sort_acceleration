































//clk = 100mhz
#include "ap_int.h"
#define longsize 65536 //size of SORCE
#define shortsize 32 //size of SORCE

int distance(ap_uint<2> INPUT1[shortsize],ap_uint<2> INPUT2[shortsize]){
int mat[shortsize][shortsize];
for(int i=0; i<shortsize; ++i){
    for(int j=0; j<shortsize; ++j){
        if(i == 0) mat[i][j] = j;
        else if(j == 0) mat[i][j] = i;
        else{
            int cost = ( INPUT1[i-1] == INPUT2[j-1] ) ? 0 : 1;
            int a = (mat[i-1][j]+1)<(mat[i][j-1]+1)?(mat[i-1][j]+1):(mat[i][j-1]+1);
			mat[i][j] = a<(mat[i-1][j-1]+cost)?a:(mat[i-1][j-1]+cost);
        }
    }
}
return mat[shortsize-1][shortsize-1];
}

void test1(
//input
ap_uint<8> INPUTLONG[longsize],
ap_uint<8> INPUTSHORT[shortsize],
//result
int OUTPUT[longsize-shortsize+1]
){
//////////////////////////////////////////////////////////ports
#pragma HLS INTERFACE s_axilite register port=INPUTLONG
#pragma HLS INTERFACE s_axilite register port=INPUTSHORT
#pragma HLS INTERFACE s_axilite register port=OUTPUT
#pragma HLS INTERFACE ap_ctrl_none port=return
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////compute cycle start//////////////////////////////////////////////////////////
ap_uint<2> INPUT1[shortsize];
ap_uint<2> INPUT2[shortsize];
for(int j=0; j<shortsize; ++j){
#pragma HLS PIPELINE
	if     (INPUTSHORT[j]==65) INPUT2[j]=0;//A 1 00
	else if(INPUTSHORT[j]==71) INPUT2[j]=1;//G 1 01
	else if(INPUTSHORT[j]==67) INPUT2[j]=2;//C 1 10
	else 					   INPUT2[j]=3;//T 1 11
}
for(int i=0; i< (longsize-shortsize+1); ++i){
#pragma HLS PIPELINE
	for(int j=0; j<shortsize; ++j){
		if     (INPUTLONG[i+j]==65) INPUT1[j]=0;//A 1 00
		else if(INPUTLONG[i+j]==71) INPUT1[j]=1;//G 1 01
		else if(INPUTLONG[i+j]==67) INPUT1[j]=2;//C 1 10
		else 						INPUT1[j]=3;//T 1 11
	}
	OUTPUT[i]=distance(INPUT1,INPUT2);
}
//////////////////////////////////////////////////////////compute cycle end//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}













