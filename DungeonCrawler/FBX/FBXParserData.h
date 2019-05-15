#pragma once
#include "Headerstruct.h"
#include <vector>

class FBXParserData 
{
private:
	//headers, maybe needed? maybe remove
	MainHeader m_mainHeader;
	MeshHeader m_meshHeader;
	BoundingBoxHeader m_boundingBoxHeader;
	Vertex m_vertexHeader;
	BoundingBoxVertex m_boundingBoxVertexHeader;

	//data
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;

public:
	void setMainHeader(MainHeader mainHeader);
	void setMeshHeader(MeshHeader meshHeader);
	void setVertexHeader(Vertex vertexHeader);

	//-----------------------------------------------------------------
	//Struct getters functions in order
	MainHeader getMainHeader()const;
	MeshHeader getMeshHeader()const;
	BoundingBoxHeader getBoundingBoxHeader()const;
	Vertex getVertexHeader()const;
	BoundingBoxVertex getBoundingBoxVertexHeader()const;

	//-----------------------------------------------------------------


	//-----------------------------------------------------------------
	//Struct setters functions in order
	//MainHeader
	void setMainHeaderVersion(char versionNr);
	void setMainHeaderDynamicMeshCount(unsigned int dynamicMeshCount);
	void setMainHeaderStaticMeshCount(unsigned int nrOfMeshes);
	void setMainHeaderBoundBoxCount(unsigned int nrOfBoundingBoxMeshes);
	void setMainHeaderMaterialCount(unsigned int nrOfBoundingBoxMeshes);


	//MeshHeader
	void setMeshHeaderNameOfMesh(std::vector<char> nameOfMeshVector);
	void setMeshHeaderVertexCountOfMesh(unsigned int vertexCount);
	void setMeshHeaderMaterialID(int materialID);
	void setMeshHeaderCollisionOfMesh(bool collision);
	void setMeshHeaderStaticMesh(bool staticMesh);

	//BoundingBoxHeader
	void setBBHeaderNameOfBoundingBoxMesh(char nameOfBoundingBox[]);
	void setBBHeaderVertexCountOfBoundingBoxMesh(unsigned int vertexCount);
	void setBBHeaderCollisionOfBoundingBoxMesh(bool collision);
	void setBBHeaderStaticBoundingBoxMesh(bool staticBoundingBoxMesh);

	//Vertex
	void setMVHeaderPositionVertexOfMesh(float positionVertex[]);
	void setMVHeaderUVOfMesh(float UV[]);
	void setMVHeaderNormalOfMesh(float normal[]);
	
	//MaterialHeader
	void setMaterialHeaderNameOfAlbedo(std::vector<char> nameOfAlbedo);
	void setMaterialHeaderNameOfNormal(std::vector<char> nameOfNormal);

	//BoundingBoxVertex
	void setBBVHeaderPositionOfBoundingBox(float position[]);
	//--------------------------------------------------------------------
};