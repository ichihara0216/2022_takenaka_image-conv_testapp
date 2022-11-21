
/***********************************************************************
 * �C���N���[�h�t�@�C��
 ***********************************************************************/

#include<iostream>
#include<winsock2.h	>	//TCP/IP �p�� WinSock 2 Protocol-Specific Annex �h�L�������g�œ������ꂽ��`���܂܂�Ă���AIP �A�h���X�̎擾�Ɏg�p�����V�����֐��ƍ\�����܂܂�Ă���
#include<stdio.h>
#include<WS2tcpip.h>
#include<chrono>
#include<thread>
#include "ImageConverterCheckTest.h"




#define SECONDCODE
#ifdef SECONDCODE


	winSocketCl::winSocketCl() {
		wsaData = { 0 };
		sock = 0;
		wsaErr = WSAStartup(MAKEWORD(2, 0), &wsaData);
		connectErr = 0;
		ser_addr = { 0 };
	}
	winSocketCl::~winSocketCl() {
		std::cout << "�f�X�g���N�^�F" __FUNCTION__ << std::endl;
		WSACleanup();
	}


	void winSocketCl::SetServer() {
		ser_addr.sin_family = AF_INET;
		ser_addr.sin_port = htons(PORT_NUM_SERVER);
		inet_pton(AF_INET, IP_ADDR_SERVER, &ser_addr.sin_addr.S_un.S_addr);
	}

	int winSocketCl::MakeSocket() {
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			std::cout << "�\�P�b�g�쐬�G���[" << std::endl;
			perror("socket");
			return 1;
		}
		return 0;
	}

	int winSocketCl::ConnToServer() {
		if ((connectErr = connect(sock, (struct sockaddr*)&ser_addr, sizeof(ser_addr))) < 0) {
			std::cout << "�R�l�N�g���s�G���[" << std::endl;
			perror("connect");
			return 1;
		}
		return 0;
	}

	//void winSocketCl::RecvFromServer() {
	//	//char buf[1024];
	//	memset(buf, 0, sizeof(buf));
	//	int rs = recv(sock, buf, sizeof(buf), 0);
	//	std::cout << "��M����������F" << buf << std::endl << "��M�����������F" << rs << std::endl;
	//	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//}

	int winSocketCl::RecvFromServer(char* packet_pt, int packet_size) {
		int rsize;
			rsize = recv(sock	, packet_pt, packet_size, 0);

			if (rsize < 0) {
				perror("recv");
				return 0;
			}
			else {
				//std::cout << "receive : %s" << *buf_pt << std::endl;
				return rsize;
			}
		}
	

	void winSocketCl::SendToServer(char* src) {
		//char buf[1024] = { 'e', 'u', 'r', 'a' };
		std::cout << "send contents �F " << src << "\nsend size : " <<sizeof(src)<< std:: endl;
		send(sock, src, FRAMESIZE, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}



#endif

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
			sprintf_s(send_str, "%c", i);
			std::cout << send_str << std::endl;
			if (send(cl_sock, send_str, sizeof(send_str), 0) < 0) {
				perror("error : SendData");
			}
			else {
				recv(cl_sock, receive_str, sizeof(receive_str), 0);
				std::cout << send_str << std::endl;
				std::cout << "�f�[�^���M��%d/10" << i << std::endl;
			}
			//�����ő҂A���Ԃ̌v�Z
		}
	}

	/*�ʐM�I�����̃N���[���A�b�v*/
	void CleanUp() {
		closesocket(cl_sock);
		WSACleanup();
	}
};
#endif
