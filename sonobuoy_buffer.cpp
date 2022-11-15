#ifndef _sonobuoy_buffer_
#define _sonobuoy_buffer_
#include "ImageConverterCheckTest.h"

sonobuoy_buffer::sonobuoy_buffer(){}
sonobuoy_buffer::~sonobuoy_buffer() {}

/*�������������̕����Ŗ��߂�*/
void sonobuoy_buffer::FillMemSnvi_src(char fillElem) {
	for (int i = 0; i < FRAMESIZE; i++) {
		snvi_src[i] = fillElem;
		}
}

/*���M�p�o�b�t�@�̒l�擾*/
char* sonobuoy_buffer:: GetBufferSnvi_src() {
	return snvi_src;
}

/*��M�p�o�b�t�@�̒l�擾*/
char* sonobuoy_buffer::GetBufferSnvi_recv() {
	return snvi_recv;
}

/*��M�p�o�b�t�@�ɒl���Z�b�g*/
void sonobuoy_buffer::SetBufferSnvi_recv(char* recvData){
	memcpy(snvi_recv_pt, recvData, recvCnt);
	printf("sonobuoy�N���X��snvi�o�b�t�@�ɃR�s�[���ꂽ���́F%s", snvi_recv);
	snvi_recv_pt += recvCnt;
}

void sonobuoy_buffer::SetRecv_Cnt(int recv_cnt) {
	recvCnt = recv_cnt;
}

void sonobuoy_buffer::CompareData() {
	bool errorFlag = true;
	for (int i = 0; i < FRAMESIZE; i++) {
		if (!(snvi_src[i] == snvi_recv[i])) {
			printf("�l�̕s��v�A�Y�����w%d�x\n", i);
			errorFlag = false;
		}
	}
	if (errorFlag == true) {
		printf("�f�[�^�`�F�b�N�ɖ��͂���܂���ł����B\n");
	}
}

#endif