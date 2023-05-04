#include <iostream>
#include <vector>
#include <unistd.h> // for usleep()
#include <fcntl.h>  // for open(), close(), read(), write()
#include <termios.h>

using namespace std;
typedef unsigned char UChar;

UChar cmd[6];



int SerialPortOpen()
{
   
    int fd = open("/dev/ttyS1", O_RDWR | O_NOCTTY);
    if (fd == -1)
    {
        cout << "Failed to open serial port." << endl;
    }
    else
    {
        cout << "serial port is opened" << endl;
    }
    return fd;
}

void ConfigureSerialPort(int fd)

{
    if (fd != -1)
    {
        // configure serial port
        struct termios options;
        tcgetattr(fd, &options);
        cfsetispeed(&options, B115200);
        cfsetospeed(&options, B115200);
        options.c_cflag |= (CLOCAL | CREAD);
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
        tcsetattr(fd, TCSANOW, &options);
        cout << "configuration done" << endl;
    }
    else
    {
        cout << "Failed to configure serial port" << endl;
    }
}



int main()
{
    int fd=SerialPortOpen();
    ConfigureSerialPort(fd);
    size_t cmdLength,bytesRead ;
    cmdLength=sizeof(cmd);
     
        // cout << "after read response" << bytesRead <<endl;

        

 

    while(true)
    {
        bytesRead = read(fd, cmd, cmdLength);

        for(int i = 0;i<6;i++)
        {
            printf("%02x",cmd[i]);
        }

        if(bytesRead!=cmdLength){
            cout<<"Failed to read command."<<std::endl;
            break;
        }
        else{
            cout<<"able to read command."<<std::endl;
        }

    }


    return 0;


    


}
