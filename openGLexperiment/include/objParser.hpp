#include <vector>
#include <string.h>
#include <fstream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

extern GLuint _textureId;
extern unsigned int bCount;
 
class material{
public:
	material(string nameI){
		this->name = nameI;
	}
	~material(){
	};
	int index;
	vector<float> ka;
	vector<float> kd;
	vector<float> ks;
	string name;
	string tpath;
private:
	material();
	//material(const material& X);
	//material & operator=(const material &rhs);
};

class parsingData{

public:
	parsingData(string input);
	~parsingData();
	vector< vector<float> > getTriangleList(void);
	
	vector< vector<float> > getvTextureList(void);
	vector< vector<float> > getvirtextList(void);
	vector< vector<float> > getnormalsList(void);
	bool hasNormals;
	bool hasTex;

	unsigned int finalTCount;
	float** glTriangle;

	unsigned int totalVirtexCount;
	float** glVirtexArray;

private:
	
	parsingData();

	//prevent calling these unintentionally
	parsingData(const parsingData& X);
	parsingData & operator=(const parsingData &rhs);

	int parseMTLLib(string& inString,vector<string>& texturesList);
	int findTexIndex(string materialName);

	int indexCount;
	fstream filestr;
	string relativePath;
	string fileString;

	//file parsing data
	vector< vector<float> > triangleList;
	

	vector< vector<float> > vTextureList;
	vector< vector<float> > virtextList;
	vector< vector<float> > normalsList;
	vector<material> matList;
};


int renderModel(parsingData*);
int dbgModel(parsingData*);
