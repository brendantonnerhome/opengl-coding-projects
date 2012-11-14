
#ifndef SOCKET_HELPER_HPP
#define SOCKET_HELPER_HPP


class bSocket
{
	public:
		bSocket();
        int bSocketClient(const char*  portNo, const char* serverIP, unsigned int pBufferLen);
        int bSocketServer(const char*  portNo, const char* serverIP, unsigned int pBufferLen);
		int getSocketNo(void);
        ~bSocket();

	protected:

	private:
        void setCommonInternals(const char*  portNo, const char* serverIP, unsigned int pBufferLe);
        int lSocket;
        unsigned int bufferLen;
        void *socketBuffer;
        bool configured;
        unsigned int socketPort;

        //explicitly not defined
        bSocket(const bSocket& toCopy);
        //explicitly not defined
        bSocket& operator=(const bSocket& toCopy);

};


#endif // SOCKET_HELPER_HPP
