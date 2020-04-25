#include "ServerNetwork.h"

int main(int agrc, char **argv)
{
	ServerNetwork network(2525);
	network.Run();
	return 0;
}
