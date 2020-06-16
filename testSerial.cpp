#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
int serialSend(int v,FILE * file)
{
	usleep(100*1000);
    fprintf(file, "%d\n",v);
	cout<<v<<endl;
	return 0;
}
int main()
{
	FILE * file = fopen("/dev/ttyACM0","w");  //Opening device file
    usleep(1000*1000);
	while(1)
		serialSend(0,file);
	fclose(file);
}