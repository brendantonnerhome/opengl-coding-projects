
#include "objParser.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <sstream>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


int renderModel(parsingData* data){
	vector< vector<float> > triangles = data->getTriangleList();
	vector< vector<float> > normals = data->getnormalsList();
	vector< vector<float> >	vertices = data->getvirtextList();
	vector< vector<float> > textCoords = data->getvTextureList();

	for(unsigned int i=0;i<triangles.size();i++){
		glBegin(GL_TRIANGLES);
		//format =
		//f vertex index/ tex coord/ normal index  vertex index/ tex coord/ normal index  vertex index/ tex coord/ normal index
		//			0			1			2			3			4			5			6			7			8
		//set the normal face

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glNormal3f(
			normals.at((int)triangles.at(i).at(2)-1).at(0),
			normals.at((int)triangles.at(i).at(2)-1).at(1),
			normals.at((int)triangles.at(i).at(2)-1).at(2)
			);
		//triangle 1
		//vertices 0, 1, 2 -- vertices.at(triangles.at(i).at(0)

		glTexCoord2f(textCoords.at((int)triangles.at(i).at(0)-1).at(0), textCoords.at((int)triangles.at(i).at(0)-1).at(1));
		glVertex3f(
			vertices.at((int)triangles.at(i).at(0)-1).at(0),
			vertices.at((int)triangles.at(i).at(0)-1).at(1),
			vertices.at((int)triangles.at(i).at(0)-1).at(2)
			);
		//triangle 2
		//vertices 3,4,5
		glTexCoord2f(textCoords.at((int)triangles.at(i).at(3)-1).at(0), textCoords.at((int)triangles.at(i).at(3)-1).at(1));
		glVertex3f(
			vertices.at((int)triangles.at(i).at(3)-1).at(0),
			vertices.at((int)triangles.at(i).at(3)-1).at(1),
			vertices.at((int)triangles.at(i).at(3)-1).at(2)
			);
		//triangle 3
		//vertices 6,7,8
		glTexCoord2f(textCoords.at((int)triangles.at(i).at(6)-1).at(0), textCoords.at((int)triangles.at(i).at(6)-1).at(1));
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

//int parsingData::parseMTLLib(string& inString, vector<string>& texturesList){
 //   return 0;
//}
//using namespace std;
int parsingData::parseMTLLib(const string& inString, vector<string>& texturesList){
	fstream mtlstr;
	string lineBuffer;
	//mtlstr.open(inString,fstream::in | fstream::app);
	mtlstr.open(inString.c_str(),fstream::in | fstream::app);
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

//parsingData::parsingData(string inString){
//}


parsingData::parsingData(string inString){
	cout << inString << endl;
	this->indexCount = 0;
	int currentIndex = 0;
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
						//cout << "\t\tvirtext normal line" << endl;
						this->normalsList.push_back(fpTokens);
					}else if(lineBuffer.at(1) == 't'){
						//cout << "\t\tvirtext texture line" << endl;
						this->vTextureList.push_back(fpTokens);
					}
					else{
						//cout << "\t\tvertex line" << endl;
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

	}
	else {
		cout << "error reading file!" << endl;
	}
	filestr.close();
}

parsingData::parsingData(){

}

parsingData::~parsingData(){

}
