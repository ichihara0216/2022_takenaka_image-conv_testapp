#ifndef _sonobuoy_buffer_
#define _sonobuoy_buffer_
#include "ImageConverterCheckTest.h"

sonobuoy_buffer::sonobuoy_buffer(){}
sonobuoy_buffer::~sonobuoy_buffer() {}

/*メモリを引数の文字で埋める*/
void sonobuoy_buffer::FillMemSnvi_src(char fillElem) {
	for (int i = 0; i < FRAMESIZE; i++) {
		snvi_src[i] = fillElem;
		}
}

/*送信用バッファの値取得*/
char* sonobuoy_buffer:: GetBufferSnvi_src() {
	return snvi_src;
}

/*受信用バッファの値取得*/
char* sonobuoy_buffer::GetBufferSnvi_recv() {
	return snvi_recv;
}

/*受信用バッファに値をセット*/
void sonobuoy_buffer::SetBufferSnvi_recv(char* recvData){
	memcpy(snvi_recv_pt, recvData, recvCnt);
	printf("sonobuoyクラスのsnviバッファにコピーされたもの：%s", snvi_recv);
	snvi_recv_pt += recvCnt;
}

void sonobuoy_buffer::SetRecv_Cnt(int recv_cnt) {
	recvCnt = recv_cnt;
}

void sonobuoy_buffer::CompareData() {
	bool errorFlag = true;
	for (int i = 0; i < FRAMESIZE; i++) {
		if (!(snvi_src[i] == snvi_recv[i])) {
			printf("値の不一致、添え字『%d』\n", i);
			errorFlag = false;
		}
	}
	if (errorFlag == true) {
		printf("データチェックに問題はありませんでした。\n");
	}
}

#endif