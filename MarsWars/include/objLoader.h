
#ifndef OBJLOADER_H
#define OBJLOADER_H
#include<string>

using namespace std;
class objLoader
{
    public:
        string name;
    objLoader(string name);
    ~objLoader();
    float* calculateNormal(float* coord1,float* coord2,float* coord3 );
    int Load(string filename);	// Loads the model
	void render();
	void rotater(float angle);
	void Draw();// Draws the model on the screen
	void Release();				// Release the model
	float* normals;							// Stores the normals
    float* Faces_Triangles;					// Stores the triangles
	float* vertexBuffer;					// Stores the points which make the object
	long TotalConnectedPoints;				// Stores the total number of connected verteces
	long TotalConnectedTriangles;

    protected:
    private:
};

#endif // OBJLOADER_H
