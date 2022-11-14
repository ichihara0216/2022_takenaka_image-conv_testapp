/***********************************************************************/
/*  システム名  :ImageConverterCheckTest                                          */
/*  FILE  　　    :ImageConverterCheckTest.cpp                                   */
/*  DATE        :Tue,Nov,2022　　　　　 　　                                                 */
/*  DESCRIPTION :                                                                              */
/*                                                                                                          */
/*  Author      : ichihara                                                                        */
/*                                                                                                          */
/***********************************************************************/

#include <iostream>
#include "win_client.h"
#include <conio.h>

int main()
{
	int err = 0;
	winSocketCl* winCl = new winSocketCl();

	winCl->SetServer();
	if (err) {
		int errCode = WSAGetLastError();
		std::cout << errCode << std::endl;
		return 0;
	}
	else {
		std::cout << "setserver:ok" << std::endl;
	}

	winCl->MakeSocket();
	if (err) {
		int errCode = WSAGetLastError();
		std::cout << errCode << std::endl;
	}
	else {
		std::cout << "makeserver:ok" << std::endl;
	}

	err = winCl->ConnToServer();
	if (err) {
		int errCode =WSAGetLastError();
		std::cout << errCode << std::endl;
	}
	else {
		std::cout << "connect:ok" << std::endl;
	}

	do {
		printf("send start\n");
		winCl->SendToServer();
		printf("send fin\n\n");
		printf("recv start\n");
		winCl->RecvFromServer();
		printf("recv fin\n\n");
	} while (!_kbhit());

	delete winCl;
	return 0;
}
