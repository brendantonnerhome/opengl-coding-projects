#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP



void* thread_main(void* data);

enum listed {
    serverServer = 0,
    serverClient = 1,
    glThread = 2
    //graphicsRuntime = 1
};
enum dataSets{
    coordsCamera = 0,
    coordsWorld = 1,
    offsetCamera = 2,
    offsetWorld = 3,
};
typedef struct coordData{
    double x;
    double y;
    double z;
} coordData;

typedef struct offsetData{
    double dx;
    double dy;
    double dz;
} offsetData;

typedef struct camaraCoords_t{
    coordData coords;
    offsetData offset;
}camaraCoords_t;

typedef struct transferData{
    enum dataSets dataType;
    unsigned char* dataFields;
    unsigned int dataSize;
}transferData;

//packTransferData
//getTransferDataSize
//...

class threadListObj {
public:

threadListObj();
 ~threadListObj();

private:
    pthread_t* threadList;
    void threadInit(void);
    void threadCleanUp(void);
    static const unsigned int numPThreads =3;
};

#endif
