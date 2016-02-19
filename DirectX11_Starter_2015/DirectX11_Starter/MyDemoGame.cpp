// ----------------------------------------------------------------------------
//  A few notes on project settings
//
//  - The project is set to use the UNICODE character set
//    - This was changed in Project Properties > Config Properties > General > Character Set
//    - This basically adds a "#define UNICODE" to the project
//
//  - The include directories were automagically correct, since the DirectX 
//    headers and libs are part of the windows SDK
//    - For instance, $(WindowsSDK_IncludePath) is set as a project include 
//      path by default.  That's where the DirectX headers are located.
//
//  - Two libraries had to be manually added to the Linker Input Dependencies
//    - d3d11.lib
//    - d3dcompiler.lib
//    - This was changed in Project Properties > Config Properties > Linker > Input > Additional Dependencies
//
//  - The Working Directory was changed to match the actual .exe's 
//    output directory, since we need to load the compiled shader files at run time
//    - This was changed in Project Properties > Config Properties > Debugging > Working Directory
//
// ----------------------------------------------------------------------------

#include "MyDemoGame.h"
#include "Vertex.h"


#include <iostream>

// For the DirectX Math library
using namespace DirectX;


#pragma region Win32 Entry Point (WinMain)
// --------------------------------------------------------
// Win32 Entry Point - Where your program starts
// --------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// Create the game object.
	MyDemoGame game(hInstance);
	
	// This is where we'll create the window, initialize DirectX, 
	// set up geometry and shaders, etc.
	if( !game.Init() )
		return 0;
	
	// All set to run the game loop
	return game.Run();
}

#pragma endregion

#pragma region Constructor / Destructor
// --------------------------------------------------------
// Base class constructor will set up all of the underlying
// fields, and then we can overwrite any that we'd like
// --------------------------------------------------------
MyDemoGame::MyDemoGame(HINSTANCE hInstance) 
	: DirectXGameCore(hInstance)
{
	// Set up a custom caption for the game window.
	// - The "L" before the string signifies a "wide character" string
	// - "Wide" characters take up more space in memory (hence the name)
	// - This allows for an extended character set (more fancy letters/symbols)
	// - Lots of Windows functions want "wide characters", so we use the "L"
	windowCaption = L"My Super Fancy GGP Game";

	// Custom window size - will be created by Init() later
	windowWidth = 1280;
	windowHeight = 720;
}

// --------------------------------------------------------
// Cleans up our DirectX stuff and any objects we need to delete
// - When you make new DX resources, you need to release them here
// - If you don't, you get a lot of scary looking messages in Visual Studio
// --------------------------------------------------------
MyDemoGame::~MyDemoGame()
{
	delete entity1;
	delete entity2;
	delete entity3;

	delete mesh1;
	delete mesh2;
	delete mesh3;


	delete render;

	// Delete our simple shaders
	delete vertexShader;
	delete pixelShader;

	delete basicMaterial;
}

#pragma endregion

#pragma region Initialization

// --------------------------------------------------------
// Initializes the base class (including the window and D3D),
// sets up our geometry and loads the shaders (among other things)
// --------------------------------------------------------
bool MyDemoGame::Init()
{
	// Call the base class's Init() method to create the window,
	// initialize DirectX, etc.
	if( !DirectXGameCore::Init() )
		return false;

	// Helper methods to create something to draw, load shaders to draw it 
	// with and set up matrices so we can see how to pass data to the GPU.
	//  - For your own projects, feel free to expand/replace these.

	render = new Render(deviceContext);

	LoadShaders(); 
	CreateGeometry();

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives we'll be using and how to interpret them
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	camera = Camera(0.0f, 0.0f, -5.0f);

	// Successfully initialized
	return true;
}


// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files
// - These simple shaders provide helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void MyDemoGame::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, deviceContext);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, deviceContext);
	pixelShader->LoadShaderFile(L"PixelShader.cso");

	basicMaterial = new Material(vertexShader, pixelShader);
}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void MyDemoGame::CreateGeometry()
{
	XMFLOAT4 red	= XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green	= XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 magenta = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	XMFLOAT4 blue	= XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex vertices[] =
	{
		{ XMFLOAT3(-0.5f, +1.0f, +0.0f), red },// 0
		{ XMFLOAT3(+0.5f, -1.0f, +0.0f), blue },// 1
		{ XMFLOAT3(-0.5f, -1.0f, +0.0f), green },// 2
		{ XMFLOAT3(+0.5f, +1.0f, 0.0f), green },// 3
	};
	int indices[] = { 0, 1, 2, 0, 3, 1 };
	mesh1 = new Mesh(vertices, 4, indices, 6, device);
	//DrawnMesh drawnMesh1 = DrawnMesh(render, mesh1);
	entity1 = new Entity();
	entity1->AddComponent(new DrawnMesh(render, mesh1, basicMaterial));

	float halfSize = 100 * 0.5f;
	float yPos = -1;
	Vertex vertices2[] =
	{
		{ XMFLOAT3(-halfSize, +yPos, +halfSize), magenta },// 0
		{ XMFLOAT3(+halfSize, +yPos, -halfSize), magenta },// 1
		{ XMFLOAT3(-halfSize, +yPos, -halfSize), magenta },// 2
		{ XMFLOAT3(+halfSize, +yPos, +halfSize), magenta },// 3
	};
	int indices2[] = { 0, 1, 2, 0, 3, 1 };
	mesh2 = new Mesh(vertices2, 4, indices2, 6, device);
	entity2 = new Entity();
	entity2->AddComponent(new DrawnMesh(render, mesh2, basicMaterial));

	Vertex vertices3[] =
	{
		{ XMFLOAT3(-1.5f, +1.0f, +0.0f), blue },// 0
		{ XMFLOAT3(+1.5f, +1.0f, 0.0f), blue },// 1
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), blue },// 2
	};
	int indices3[] = { 0, 1, 2 };
	mesh3 = new Mesh(vertices3, 3, indices3, 3, device);
	entity3 = new Entity();
	entity3->AddComponent(new DrawnMesh(render, mesh3, basicMaterial));
}

#pragma endregion

#pragma region Window Resizing

// --------------------------------------------------------
// Handles resizing DirectX "stuff" to match the (usually) new
// window size and updating our projection matrix to match
// --------------------------------------------------------
void MyDemoGame::OnResize()
{
	// Handle base-level DX resize stuff
	DirectXGameCore::OnResize();

	// Update our projection matrix since the window size changed
	camera.CreatePerspectiveProjectionMatrix(aspectRatio, 0.1f, 100.0f);
}
#pragma endregion

#pragma region Game Loop

// --------------------------------------------------------
// Update your game here - take input, move objects, etc.
// --------------------------------------------------------
float x = 0;
void MyDemoGame::UpdateScene(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	DirectX::XMFLOAT3 rot = entity1->GetTransform().GetRotation();
	float rotRate = 10.0f;
	rot.x += rotRate * deltaTime;
	rot.y += rotRate * deltaTime;
	rot.z += rotRate * deltaTime;
	entity1->GetTransform().SetRotation(rot);
	DirectX::XMFLOAT3 pos = entity2->GetTransform().GetPosition();
	pos.x += 0.2f * deltaTime;
	//entity2->GetTransform().SetPosition(pos);
	entity3->GetTransform().SetParrent(&entity2->GetTransform());

	entity1->Update();
	entity2->Update();
	entity3->Update();
	LONG deltaMouseX = curMousePos.x - prevMousePos.x;
	LONG deltaMouseY = curMousePos.y - prevMousePos.y;
	camera.Update(deltaTime, deltaMouseX, deltaMouseY);
	prevMousePos.x = curMousePos.x;
	prevMousePos.y = curMousePos.y;
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void MyDemoGame::DrawScene(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = {0.4f, 0.6f, 0.75f, 0.0f};

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of DrawScene (before drawing *anything*)
	deviceContext->ClearRenderTargetView(renderTargetView, color);
	deviceContext->ClearDepthStencilView(
		depthStencilView, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);


	// Send data to shader variables
	//  - Do this ONCE PER OBJECT you're drawing
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	//vertexShader->SetMatrix4x4("world", worldMatrix);
	//vertexShader->SetMatrix4x4("view", viewMatrix);
	//vertexShader->SetMatrix4x4("projection", projectionMatrix);
	
	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	vertexShader->SetShader(true);
	pixelShader->SetShader(true);

	render->UpdateAndRender(camera.GetViewMatrix(), camera.GetProjectionMatrix());


	// Present the buffer
	//  - Puts the image we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME
	//  - Always at the very end of the frame
	HR(swapChain->Present(0, 0));
}

#pragma endregion

#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
//
// Feel free to add code to this method
// --------------------------------------------------------
void MyDemoGame::OnMouseDown(WPARAM btnState, int x, int y)
{
	if (prevMousePos.x == 0 && prevMousePos.y == 0) {
		prevMousePos.x = curMousePos.x;
		prevMousePos.y = curMousePos.y;
	}
	// Save the previous mouse position, so we have it for the future
	curMousePos.x = x;
	curMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hMainWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
//
// Feel free to add code to this method
// --------------------------------------------------------
void MyDemoGame::OnMouseUp(WPARAM btnState, int x, int y)
{
	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
//
// Feel free to add code to this method
// --------------------------------------------------------
void MyDemoGame::OnMouseMove(WPARAM btnState, int x, int y)
{
	if (prevMousePos.x == 0 && prevMousePos.y == 0) {
		prevMousePos.x = curMousePos.x;
		prevMousePos.y = curMousePos.y;
	}
	// Save the previous mouse position, so we have it for the future
	curMousePos.x = x;
	curMousePos.y = y;
}
#pragma endregion