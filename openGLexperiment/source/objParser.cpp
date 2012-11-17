#include "obj_parser.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <time.h>
 
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
unsigned int bCount=0;

int renderModel(parsingData* data){
	vector< vector<float> > triangles = data->getTriangleList();
	vector< vector<float> > normals = data->getnormalsList();
	vector< vector<float> >	vertices = data->getvirtextList();
	vector< vector<float> > textCoords = data->getvTextureList();
	static unsigned int startTime = time(NULL);
	
	//unsigned int currentTime = time(NULL) ;
	//unsigned int tdiff = currentTime-startTime;
	//cout << "tdiff=" << tdiff << endl;
	//static unsigned int countA = triangles.size();
	//unsigned int allowed = triangles.size() - countA;

	//countA = tdiff;

	//if(allowed > triangles.size()){
	//	countA = triangles.size();
	//}
	
	//cout << "draw " << allowed << " triangles" << endl;

	//if (allowed>=0){
	//	allowed = 0;
	//}

	//for(unsigned int i=0;i<triangles.size();i++){
	/*for(unsigned int i=0;i<data->finalTCount;i++){
		glBegin(GL_TRIANGLES);
		//format = 
		//f vertex index/ tex coord/ normal index  vertex index/ tex coord/ normal index  vertex index/ tex coord/ normal index  
		//			0			1			2			3			4			5			6			7			8
		//set the normal face
		if(data->hasTex){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glColor3f(1.0f, 1.0f, 1.0f);
		
		

		glBegin(GL_QUADS);
		if(data->hasNormals){
		//cout << normals[(int)triangles[i)[2)-1)[0)<< " " <<
		//		normals[(int)triangles[i)[2)-1)[1)<< " " <<
		//		normals[(int)triangles[i)[2)-1)[2)<< endl;
			
			glNormal3f(
				normals[(int)data->glTriangle[i][2]-1][0],
				normals[(int)data->glTriangle[i][2]-1][1],
				normals[(int)data->glTriangle[i][2]-1][2]
				);
		}
		//triangle 1
		//vertices 0, 1, 2 -- vertices[triangles[i)[0)
		
		if(data->hasTex)
			glTexCoord2f(textCoords[(int)triangles[i][0]-1][0], textCoords[(int)triangles[i][0]-1][1]);
		glVertex3f(
			data->glVirtexArray[(int)data->glTriangle[i][0]-1][0],
			data->glVirtexArray[(int)data->glTriangle[i][0]-1][1],
			data->glVirtexArray[(int)data->glTriangle[i][0]-1][2]
			);
		//triangle 2
		//vertices 3,4,5
		if(data->hasTex)
			glTexCoord2f(textCoords[(int)triangles[i][3]-1][0], textCoords[(int)triangles[i][3]-1][1]);
		glVertex3f(
			data->glVirtexArray[(int)data->glTriangle[i][3]-1][0],
			data->glVirtexArray[(int)data->glTriangle[i][3]-1][1],
			data->glVirtexArray[(int)data->glTriangle[i][3]-1][2]
			);
		//triangle 3
		//vertices 6,7,8
		if(data->hasTex)
			glTexCoord2f(textCoords[(int)triangles[i][6]-1][0], textCoords[(int)triangles[i][6]-1][1]);
		//cout << (int)triangles[i][6]-1 << endl;
		//cout << (int)triangles[i][6]-1 << endl;
		//cout << (int)triangles[i][6]-1 << endl;
		//cout << (int)triangles[i][6]-1)[0] << endl;
		//cout << (int)triangles[i][6]-1)[0] << endl;
		//cout << (int)triangles[i][6]-1)[0] << endl;
		glVertex3f(
			data->glVirtexArray[(int)data->glTriangle[i][6]-1][0],
			data->glVirtexArray[(int)data->glTriangle[i][6]-1][1],
			data->glVirtexArray[(int)data->glTriangle[i][6]-1][2]
			);
			//triangles[i)[0],triangles[i][0]
		
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	return 0;
	*/
	unsigned int upperB = triangles.size();
	if(bCount == upperB){
		bCount =0;
	}
	
	for(unsigned int i=0;i<upperB - bCount;i++){
		glBegin(GL_TRIANGLES);
		//format = 
		//f vertex index/ tex coord/ normal index  vertex index/ tex coord/ normal index  vertex index/ tex coord/ normal index  
		//			0			1			2			3			4			5			6			7			8
		//set the normal face
		if(data->hasTex){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glColor3f(1.0f, 1.0f, 1.0f);
		
		

		glBegin(GL_QUADS);
		if(data->hasNormals){
		//cout << normals.at((int)triangles.at(i).at(2)-1).at(0)<< " " <<
		//		normals.at((int)triangles.at(i).at(2)-1).at(1)<< " " <<
		//		normals.at((int)triangles.at(i).at(2)-1).at(2)<< endl;
			
			glNormal3f(
				normals.at((int)triangles.at(i).at(2)-1).at(0),
				normals.at((int)triangles.at(i).at(2)-1).at(1),
				normals.at((int)triangles.at(i).at(2)-1).at(2)
				);
		}
		//triangle 1
		//vertices 0, 1, 2 -- vertices.at(triangles.at(i).at(0)
		
		if(data->hasTex)
			glTexCoord2f(textCoords.at((int)triangles.at(i).at(0)-1).at(0), textCoords.at((int)triangles.at(i).at(0)-1).at(1));
		glVertex3f(
			vertices.at((int)triangles.at(i).at(0)-1).at(0),
			vertices.at((int)triangles.at(i).at(0)-1).at(1),
			vertices.at((int)triangles.at(i).at(0)-1).at(2)
			);
		//triangle 2
		//vertices 3,4,5
		if(data->hasTex)
			glTexCoord2f(textCoords.at((int)triangles.at(i).at(3)-1).at(0), textCoords.at((int)triangles.at(i).at(3)-1).at(1));
		glVertex3f(
			vertices.at((int)triangles.at(i).at(3)-1).at(0),
			vertices.at((int)triangles.at(i).at(3)-1).at(1),
			vertices.at((int)triangles.at(i).at(3)-1).at(2)
			);
		//triangle 3
		//vertices 6,7,8
		if(data->hasTex)
			glTexCoord2f(textCoords.at((int)triangles.at(i).at(6)-1).at(0), textCoords.at((int)triangles.at(i).at(6)-1).at(1));
		//cout << (int)triangles.at(i).at(6)-1 << endl;
		//cout << (int)triangles.at(i).at(6)-1 << endl;
		//cout << (int)triangles.at(i).at(6)-1 << endl;
		//cout << (int)triangles.at(i).at(6)-1).at(0) << endl;
		//cout << (int)triangles.at(i).at(6)-1).at(0) << endl;
		//cout << (int)triangles.at(i).at(6)-1).at(0) << endl;
		glVertex3f(
			vertices.at((int)triangles.at(i).at(6)-1).at(0),
			vertices.at((int)triangles.at(i).at(6)-1).at(1),
			vertices.at((int)triangles.at(i).at(6)-1).at(2)
			);
			//triangles.at(i).at(0),triangles.at(i).at(0)
		
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}
	
	return 0;
}

vector< vector<float> > parsingData::getTriangleList(void){
	return parsingData::triangleList;
}

vector< vector<float> > parsingData::getvTextureList(void){
	return parsingData::vTextureList;
}

vector< vector<float> > parsingData::getvirtextList(void){
	return parsingData::virtextList;
}

vector< vector<float> > parsingData::getnormalsList(void){
	return parsingData::normalsList;
}

template <class T>
//http://www.codeguru.com/forum/showthread.php?t=231054
bool from_string(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&)){
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

//http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

//http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

int castFloat(vector<string>& tokenV, vector<float>& floatsV){
	vector<string>::iterator tokenI;
	float f;
	for(tokenI = tokenV.begin();tokenI != tokenV.end(); tokenI++){
		if(from_string<float>(f,*tokenI,std::dec)){
			floatsV.push_back(f);
		} else {
			continue;
		}
	}
	if(floatsV.size() !=0)return 0;
	else return -1;
}

int parsingData::parseMTLLib(string& inString, vector<string>& texturesList){
	fstream mtlstr;
	string lineBuffer;
	mtlstr.open(inString,fstream::in | fstream::app);
	//vector<material> matList;
	if(mtlstr.good()){
		cout << "parsing " << "\"" << inString << "\"" << "... " << endl;
		material currentmtl("test");
		//static int mtlIndex = 0;
		while(getline(mtlstr,lineBuffer)){
			cout << lineBuffer << endl;
			if(lineBuffer.size() > 1){
				vector<string> ktokens;
				vector<float> fpktokens;
				split(lineBuffer, ' ', ktokens);
				castFloat(ktokens,fpktokens);
				
				if(lineBuffer.at(0) == 'K' && lineBuffer.at(1) == 'd'){
					currentmtl.kd = fpktokens;
				}
				else if(lineBuffer.at(0) == 'K' && lineBuffer.at(1) == 'a'){
					currentmtl.ka = fpktokens;
				}
				else if(lineBuffer.at(0) == 'K' && lineBuffer.at(1) == 's'){
					currentmtl.ks = fpktokens;
				}
			}
			if(lineBuffer.size() > 2){
				if(lineBuffer.at(0) == '#') continue;
				else if(lineBuffer.at(0) == 'n' && lineBuffer.at(1) == 'e' && lineBuffer.at(2) == 'w'){
					vector<string> tmpMtlName;
					split(lineBuffer,' ',tmpMtlName);
					currentmtl.name=tmpMtlName.at(1);
				}
				else if(lineBuffer.at(0) == 'm' && lineBuffer.at(1) == 'a' && lineBuffer.at(2) == 'p'){
					vector<string> tmp;
					split(lineBuffer,' ',tmp);
					if(tmp.size() > 1){
						string tmp2 = parsingData::relativePath + tmp.at(1);
						texturesList.push_back(tmp2);
						currentmtl.tpath = tmp2;
						currentmtl.index = this->indexCount;
						this->matList.push_back(currentmtl);
						this->indexCount++;
					}
					else cout << "error material filename not found"<< endl;
				}
			}
		}
	}else{
		cout << "error reading file!" << endl;
	}
	mtlstr.close();
	return 0;
}

int parsingData::findTexIndex(string materialName){
	vector<material>::iterator mit;
	for(mit = this->matList.begin(); mit != this->matList.end();mit++){
		if(mit->name == materialName){
			return mit->index;
		}
	}
	return -1;
}

parsingData::parsingData(string inString){
	this->hasNormals = false;
	this->hasTex = false;
	this->indexCount = 0;
	int currentIndex = 0;
	
	//init some arrays for testing...
	int countV = 0;
	finalTCount = 0;
	this->glTriangle = new float*[1024];
	for(unsigned int i=0;i<1024;i++){
		float *tmp = new float[9];
		for(unsigned int k=0;k<9;k++){
			tmp[k] = 0;
			countV++;
		}
		glTriangle[i] = tmp;
	}
	unsigned int currentT = 0;

	this->glVirtexArray = new float*[4096];
	for(unsigned int i=0;i<4096;i++){
		float *tmp = new float[3];
		for(unsigned int k=0;k<3;k++){
			tmp[k] = 0;
			//countV++;
		}
		glVirtexArray[i] = tmp;
	}
	this->totalVirtexCount = 0;
	/*
	for(unsigned int i=0;i<1024;i++){
		for(unsigned int k=0;k<9;k++){
			cout << glTriangle[i][k] << " " ;
		}
		cout << endl;
	}
	*/
	if(!inString.empty()){
		vector<string> tokensTemp;
		split(inString,'/',tokensTemp);
		tokensTemp.pop_back();
		string Composed;
		vector<std::string>::iterator itt;
		for(itt = tokensTemp.begin(); itt != tokensTemp.end(); itt++){
			if(itt + 1 == tokensTemp.end()){
				Composed += *itt + '/';
			}
			else{
				Composed += *itt + '/';
			}
		}
		tokensTemp.pop_back();
		this->relativePath = Composed;
	}
	this->filestr.open(inString.c_str(),fstream::in | fstream::app);
	fileString = inString;
	string lineBuffer;
	vector<string> texturesList;
	vector<string> currentTokens;
	vector<string> faceTokens;
	vector<string>::iterator currentTokensI;
	vector<float> fpTokens;
	vector<float> facefpTokens;
	if(parsingData::filestr.good()){
		cout << "parsing " << "\"" << inString << "\"" << "... " << endl;
		while(getline(filestr,lineBuffer)){
			//cout << lineBuffer ;
			if(lineBuffer.size() > 0){
				if(lineBuffer.size() < 4) cout << "short string warning" << endl;

				currentTokens.clear();
				fpTokens.clear();

				split(lineBuffer,' ',currentTokens);
				castFloat(currentTokens,fpTokens);

				if(lineBuffer.at(0) == '#'){
					//cout << "\t\tignore comment line" << endl;
				}
				else if(lineBuffer.at(0) == 'm' && lineBuffer.at(1) == 't' && lineBuffer.at(2) == 'l'){
					cout << "texture library" << endl;
					vector<string> textTokens;
					split(lineBuffer,' ',textTokens);
					parseMTLLib(this->relativePath + textTokens.at(1),texturesList);
					cout << lineBuffer;
				}else if(lineBuffer=="/r"){

				}
				else if(lineBuffer.at(0) == 'u' && lineBuffer.at(1) == 's' && lineBuffer.at(2) == 'e'){
					cout << "texture" << endl;
					vector<string> textTokens;
					split(lineBuffer,' ',textTokens);
					currentIndex = findTexIndex(textTokens.at(1));
					if(currentIndex < 0){
						cout << "ERROR texture material referenced not found!" <<endl;
						//return;
					}
					cout << lineBuffer;
				}
				else if(lineBuffer.at(0) == 'v'){
					if(lineBuffer.at(1) == 'n'){
						this->hasNormals = true;
						//cout << "\t\tvirtext normal line" << endl;
						this->normalsList.push_back(fpTokens);
					}else if(lineBuffer.at(1) == 't'){
						this->hasTex = true;
						//cout << "\t\tvirtext texture line" << endl;
						this->vTextureList.push_back(fpTokens);
					}
					else{
						//cout << "\t\tvertex line" << endl;
						
						vector< float >::iterator iT;
						unsigned int vListCount = 0;
						for(iT=fpTokens.begin();iT!=fpTokens.end();iT++){
							glVirtexArray[this->totalVirtexCount][vListCount]=*iT;
							vListCount++;
							if(vListCount==2){
								goto hereV;
							}
						}
						hereV:
						this->totalVirtexCount++;
						this->virtextList.push_back(fpTokens);
					}
				}else if(lineBuffer.at(0) == 'f'){ 
					
					faceTokens.clear();
					facefpTokens.clear();
					for(currentTokensI = currentTokens.begin(); currentTokensI != currentTokens.end(); currentTokensI++){
						if(*currentTokensI == "f") continue;
						else{
							split(*currentTokensI,'/',faceTokens);
							
						}
					}
					castFloat(faceTokens,facefpTokens);
					facefpTokens.push_back((float)currentIndex);
					vector< float >::iterator iT;
					unsigned int tListCount = 0;
					for(iT=facefpTokens.begin();iT!=facefpTokens.end();iT++){
						glTriangle[currentT][tListCount]=*iT;
						cout << *iT << " ";
						tListCount++;
						if(tListCount==8){
							goto here;
						}
					}
					here:
					currentT++;
					cout << endl;
					triangleList.push_back(facefpTokens);
					//cout << "\t\tface line" << endl;
				}else if(lineBuffer.at(0) == 'g'){
					//cout << "\t\tmodel name" << endl;
				}
				else if(lineBuffer.at(0) == 'm' && lineBuffer.at(1) == 't' && lineBuffer.at(2) == 'l'){
					//cout << "\t\ttexture file line" << endl;
				}
			}else{
				//cout << "\t\temty vector" << endl;
			}

		}
		cout << "done reading" << endl;
	}
		
	else {
		cout << "error reading file!" << endl;
	}
	cout << "printing current triangle state" << endl;
	for(unsigned int i=0;i<currentT;i++){
		for(unsigned int k=0;k<9;k++){
			cout << glTriangle[i][k] << " " ;
		}
		cout << endl;
	}
	finalTCount = currentT;
	filestr.close();
}

parsingData::parsingData(){

}

parsingData::~parsingData(){

}
