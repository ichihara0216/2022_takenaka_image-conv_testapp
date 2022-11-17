#ifndef _ImageConverterCheckTest_
#define _ImageConverterCheckTest_
/***********************************************************************
 * �C���N���[�h�t�@�C��
 ***********************************************************************/

#include<iostream>
#include<string>
#include<winsock2.h	>	//TCP/IP �p�� WinSock 2 Protocol-Specific Annex �h�L�������g�œ������ꂽ��`���܂܂�Ă���AIP �A�h���X�̎擾�Ɏg�p�����V�����֐��ƍ\�����܂܂�Ă���
#include<WS2tcpip.h>

#define FRAMESIZE 250000
#define PACKETSIZE 1300
 /*�T�[�o�[���}�N��*/
#define PORT_NUM_SERVER 1237
#define IP_ADDR_SERVER "169.254.116.138"

using namespace std;

class winSocketCl{
private:
	SOCKET sock;
	int connectErr;	//�R�l�N�g���̃G���[�ϐ�
	struct sockaddr_in ser_addr;

protected:

public:
	winSocketCl();
	~winSocketCl();


	void SetServer();			/*�T�[�o�[���̐ݒ�*/	
	int MakeSocket();		/*�\�P�b�g�쐬*/
	void ConnToServer();	/*�R�l�N�g*/
	int RecvFromServer(char* packet_pt, int packet_size);	/*��M*/
	void SendToServer(char* src);		/*���M*/
};

#ifdef FIRSTCODE
class WinClient {
private:
	int cl_sock;				//�\�P�b�g
	struct sockaddr_in dst_addr; //�ڑ�����̍\����

protected:
	int err;

public:
	WinClient() {
		err = 0;
		/*�\�P�b�g�ڑ���i�T�[�o�[�j�̐ݒ�*/
		cl_sock = 0;
		dst_addr.sin_family = AF_INET;
		dst_addr.sin_port = ::htons(1234);//�ʐM�|�[�g�ԍ�(port�ԍ��ݒ�)
		dst_addr.sin_addr.s_addr = INADDR_ANY;
		//inet_addr("127.0.0.1");//�h�b�g�t���A�h���X��K�؂ɕϊ�
	}
	~WinClient() 
	{
		std::cout << __FUNCTION__ << std::endl;
		CleanUp();
	}
	
	/*�\�P�b�g�쐬*/
	int MakeSocket() {
		if (cl_sock = socket(AF_INET, SOCK_STREAM, 0) < 0) {
			perror("error : MakeSocket");
			return 1;
		}
		return 0;
	}
	
	/*�T�[�o�[�ڑ�*/
	int ConnectSocket() {//�G���[���Ȃ񂩕Ԃ��H
		err = connect(cl_sock, (struct sockaddr*)&dst_addr, sizeof(struct sockaddr_in));
		//�ڑ����s���̃G���[����
		if (err < 0) {
			perror("error : ConnectSocket");
			return 1;
		}
		return 0;
	}
	
	/*�f�[�^���M*/
	void SendData() {
		char send_str[10] = { 0 };
		char receive_str[10] = { 0 };
		for (int i = 0; i < 10; i++) {
			sprintf_s(send_str, "%c", i );
			std::cout << send_str << std::endl;
			if (send(cl_sock, send_str, sizeof(send_str), 0) < 0) {
				perror("error : SendData");
			}
			else {
				recv(cl_sock, receive_str, sizeof(receive_str), 0);
				std::cout << send_str << std::endl;
				std::cout << "�f�[�^���M��%d/10" << i <<std::endl;
			}
			//�����ő҂A���Ԃ̌v�Z
		}
	}
	
	/*�ʐM�I�����̃N���[���A�b�v*/
	void CleanUp(){
		closesocket(cl_sock);
		WSACleanup();
	}
};
#endif


class sonobuoy_buffer {
private:
	char snvi_src[250000] = { 0 };		/*���M�p250000byte*/
	char snvi_recv[250000] = { 0 };	/*Linux����̕ԑ��󂯎��o�b�t�@*/
	int  recvCnt = 0;            //�󂯎�����o�C�g��
	char* snvi_recv_pt = snvi_recv;
protected:

public:
	sonobuoy_buffer();
	~sonobuoy_buffer();

	void FillMemSnvi_src();   			/*���M�p�o�b�t�@�ɒl���Z�b�g*/
	char* GetBufferSnvi_src();								/*���M�p�o�b�t�@�擾*/
	void SetBufferSnvi_recv(char* recvData);		/*��M�p�o�b�t�@�ɒl���Z�b�g*/
	void SetRecv_Cnt(int recv_cnt);						/*��M�����T�C�Y���Z�b�g*/
	void CompareData();										/*���M�f�[�^�Ǝ�M�f�[�^�̔�r*/
	char* GetBufferSnvi_recv();
};
#endif