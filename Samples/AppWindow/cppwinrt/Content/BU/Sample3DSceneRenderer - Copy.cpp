#include "pch.h"
#include "Sample3DSceneRenderer.h"

#include "..\Common\DirectXHelper.h"

using namespace ecoin;

using namespace DirectX;
using namespace Windows::Foundation;

float g_StampProvider = 0.0f;
float g_StampSize = 1.0f;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_COMloadingComplete(false),
	m_degreesPerSecond(45),
	m_indexCount(0),
	m_tracking(false),
	m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

#if 0
	std::shared_ptr<classTarget> f_Target = new classTarget();
	f_Target->acGen_Humanoid();
	f_Target->acSaveCloud("Human Factor1");
#endif
#if 0
	std::shared_ptr<classTarget> f_Target2 = new classTarget();
	f_Target2->acGen_Vehicle_Ground();
	f_Target2->acSaveCloud("Vehicle Ground1");
#endif

	//g_Target = std::make_shared<classTarget_Ecom>();
	//g_Target->acLoad_from_TargetID(1);

	g_Target_1 = NULL;
	g_Target_2 = NULL;
	g_Target_3 = NULL;
	g_Target_4 = NULL;
	g_Target_5 = NULL;
	g_Target_6 = NULL;
	g_Target_7 = NULL;
	g_Target_8 = NULL;
	g_Target_9 = NULL;
	g_Target_10 = NULL;
}

// Initializes view parameters when the window size changes.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if(aspectRatio < 1.0f)
		{
		fovAngleY *= 2.0f;
		}

	// Note that the OrientationTransform3D matrix is post-multiplied here
	// in order to correctly orient the scene to match the display orientation.
	// This post-multiplication step is required for any draw calls that are
	// made to the swap chain render target. For draw calls to other targets,
	// this transform should not be applied.

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	Cube::g_projection = perspectiveMatrix * orientationMatrix;

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	XMStoreFloat4x4(
		&m_QCGconstantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	XMStoreFloat4x4(
		&m_COMconstantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	// Eye is at (0,0.7,1.5), looking at point (0,-0.1,0) with the up-vector along the y-axis.
	XMVECTORF32 eye = { 0.0f, -1.4f, 5.555f, 0.0f };
	XMVECTORF32 at = { 0.0f, -1.4f, 0.0f, 0.0f };
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	eye.v.m128_f32[0] += g_QcomManager->m_current_X;
	eye.v.m128_f32[1] += g_QcomManager->m_current_Y;

	at.v.m128_f32[0] += g_QcomManager->m_current_X;
	at.v.m128_f32[1] += g_QcomManager->m_current_Y;

	XMStoreFloat4x4(&m_QCGconstantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	XMMATRIX f_MatrixVW = XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up));

	Cube::g_view = f_MatrixVW;

#ifdef ARM_ARCH
	Cube::g_eye = Cube::BiVector(eye.v.n128_f32[0], eye.v.n128_f32[1], eye.v.n128_f32[2], eye.v.n128_f32[3]);
	Cube::g_at = Cube::BiVector(at.v.n128_f32[0], at.v.n128_f32[1], at.v.n128_f32[2], at.v.n128_f32[3]);
#else
	Cube::g_eye = Cube::BiVector(eye.v.m128_f32[0], eye.v.m128_f32[1], eye.v.m128_f32[2], eye.v.m128_f32[3]);
	Cube::g_at = Cube::BiVector(at.v.m128_f32[0], at.v.m128_f32[1], at.v.m128_f32[2], at.v.m128_f32[3]);
#endif

#if 0
	printf("VIEW MATRIX 4x4\n");
	printf("%f %f %f %f\n", f_view.r[0].m128_f32[0], f_view.r[0].m128_f32[1], f_view.r[0].m128_f32[2], f_view.r[0].m128_f32[3]);
	printf("%f %f %f %f\n", f_view.r[1].m128_f32[0], f_view.r[1].m128_f32[1], f_view.r[1].m128_f32[2], f_view.r[1].m128_f32[3]);
	printf("%f %f %f %f\n", f_view.r[2].m128_f32[0], f_view.r[2].m128_f32[1], f_view.r[2].m128_f32[2], f_view.r[2].m128_f32[3]);
	printf("%f %f %f %f\n", f_view.r[3].m128_f32[0], f_view.r[3].m128_f32[1], f_view.r[3].m128_f32[2], f_view.r[3].m128_f32[3]);
	printf("PROJECTION MATRIX 4x4\n");
	printf("%f %f %f %f\n", f_proj.r[0].m128_f32[0], f_proj.r[0].m128_f32[1], f_proj.r[0].m128_f32[2], f_proj.r[0].m128_f32[3]);
	printf("%f %f %f %f\n", f_proj.r[1].m128_f32[0], f_proj.r[1].m128_f32[1], f_proj.r[1].m128_f32[2], f_proj.r[1].m128_f32[3]);
	printf("%f %f %f %f\n", f_proj.r[2].m128_f32[0], f_proj.r[2].m128_f32[1], f_proj.r[2].m128_f32[2], f_proj.r[2].m128_f32[3]);
	printf("%f %f %f %f\n", f_proj.r[3].m128_f32[0], f_proj.r[3].m128_f32[1], f_proj.r[3].m128_f32[2], f_proj.r[3].m128_f32[3]);
#endif
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// Convert degrees to radians, then convert seconds to rotation angle
		float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

		Rotate(radians);
	}
}

// Rotate the 3D cube model a set amount of radians.
void Sample3DSceneRenderer::Rotate(float radians)
{
#if 0
	if(g_VisualMiningMode == OK_MODE_VIEW)
		{
		std::shared_ptr<Cube::CubeHESH> f_Hesh = Cube::g_HESH[g_SelectedHeshID];

		g_RADX = f_Hesh->m_RotateX;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADX)));
		g_RADY = f_Hesh->m_RotateY;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADY)));
		g_RADZ = f_Hesh->m_RotateZ;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADZ)));

		g_MatrixTP = XMMatrixTranspose(XMMatrixRotationY(g_RADZ));

#if 0
		int f_J = 5;
		int f_K = 5;
#endif
		}
	else
		{
		// Prepare to pass the updated model matrix to the shader
		g_RADX = ((float)Cube::randomFac() / 32767) * ((float)Cube::randomFac() / 32767) * 10;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADX)));
		g_RADY = ((float)Cube::randomFac() / 32767) * ((float)Cube::randomFac() / 32767) * 10;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADY)));
		g_RADZ = ((float)Cube::randomFac() / 32767) * ((float)Cube::randomFac() / 32767) * 10;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADZ)));
		}
#else
	if(g_VisualMiningMode == OK_MODE_VIEW)
		{
		g_RADX = 0;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADX)));
		g_RADY = 0;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADY)));
		g_RADZ = 0;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADZ)));

		g_RADX = 0;
		XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADX)));
		g_RADY = 0;
		XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADY)));
		g_RADZ = 0;
		XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADZ)));

		g_MatrixTP = XMMatrixTranspose(XMMatrixRotationY(g_RADZ));
		}
	else
		{
		// Prepare to pass the updated model matrix to the shader
		g_RADX = 0;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADX)));
		g_RADY = 0;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADY)));
		g_RADZ = 0;
		XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADZ)));

		g_RADX = 0;
		XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADX)));
		g_RADY = 0;
		XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADY)));
		g_RADZ = 0;
		XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADZ)));
		}

	XMStoreFloat4x4(&m_COMconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(g_RADZ)));
#endif

#if 0
	g_MatrixTP = XMMatrixTranspose(XMMatrixRotationY(g_RADZ));

	printf("MODEL MATRIX 4x4\n");
	printf("%f %f %f %f\n", g_MatrixTP.r[0].m128_f32[0], g_MatrixTP.r[0].m128_f32[1], g_MatrixTP.r[0].m128_f32[2], g_MatrixTP.r[0].m128_f32[3]);
	printf("%f %f %f %f\n", g_MatrixTP.r[1].m128_f32[0], g_MatrixTP.r[1].m128_f32[1], g_MatrixTP.r[1].m128_f32[2], g_MatrixTP.r[1].m128_f32[3]);
	printf("%f %f %f %f\n", g_MatrixTP.r[2].m128_f32[0], g_MatrixTP.r[2].m128_f32[1], g_MatrixTP.r[2].m128_f32[2], g_MatrixTP.r[2].m128_f32[3]);
	printf("%f %f %f %f\n", g_MatrixTP.r[3].m128_f32[0], g_MatrixTP.r[3].m128_f32[1], g_MatrixTP.r[3].m128_f32[2], g_MatrixTP.r[3].m128_f32[3]);

	for(;;)
	{ }
#endif
}

void Sample3DSceneRenderer::StartTracking()
{
	m_tracking = true;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void Sample3DSceneRenderer::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
		float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
		Rotate(radians);
	}
}

void Sample3DSceneRenderer::StopTracking()
{
	m_tracking = false;
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render(int f_Index)
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if(!m_loadingComplete)
		{
		return;
		}

	if(f_Index >= g_TargetedHesh->vec_Bicycle.size())
		{
		return;
		}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0,
		0
		);

	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;

	context->IASetVertexBuffers(
		0,
		1,
		g_TargetedHesh->vec_Bicycle[f_Index]->m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		g_TargetedHesh->vec_Bicycle[f_Index]->m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
		);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_inputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// Attach our pixel shader.
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	// Draw the objects.
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render_Qcom(void)
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if(!m_loadingComplete)
		{
		return;
		}

	XMVECTORF32 eye = { 0.0f, -1.4f, 5.555f, 0.0f };
	XMVECTORF32 at = { 0.0f, -1.4f, 0.0f, 0.0f };
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	//XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	float f_Div = 5.0f;

	eye.v.m128_f32[0] += g_QcomManager->m_current_X / f_Div;
	eye.v.m128_f32[1] += g_QcomManager->m_current_Y / f_Div;

	at.v.m128_f32[0] += g_QcomManager->m_current_X / f_Div;
	at.v.m128_f32[1] += g_QcomManager->m_current_Y / f_Div;

	XMStoreFloat4x4(&m_QCGconstantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_QCGconstantBuffer.Get(),
		0,
		NULL,
		&m_QCGconstantBufferData,
		0,
		0,
		0
		);

	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;

	context->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
		);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_QCGinputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(
		m_QCGvertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_QCGconstantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// Attach our pixel shader.
	context->PSSetShader(
		m_QCGpixelShader.Get(),
		nullptr,
		0
		);

	// Draw the objects.
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render_COM(float f_X, float f_Y)
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if(!m_COMloadingComplete)
		{
		return;
		}

	XMVECTORF32 eye = { 0.0f, -1.4f, 5.555f, 0.0f };
	XMVECTORF32 at = { 0.0f, -1.4f, 0.0f, 0.0f };
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	//XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	float f_Div = 5.0f;

	eye.v.m128_f32[0] += (g_QcomManager->m_current_X / f_Div) + f_X;
	eye.v.m128_f32[1] += (g_QcomManager->m_current_Y / f_Div) + f_Y;

	at.v.m128_f32[0] += (g_QcomManager->m_current_X / f_Div) + f_X;
	at.v.m128_f32[1] += (g_QcomManager->m_current_Y / f_Div) + f_Y;

	XMStoreFloat4x4(&m_COMconstantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	auto context = m_deviceResources->GetD3DDeviceContext();

	D3D11_BLEND_DESC blendDesc;
	ID3D11BlendState* blendState;

	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; //0x0f;

	// set blending
	m_deviceResources->GetD3DDevice()->CreateBlendState(&blendDesc, &blendState);

	float blendFactor[4] = { 1,1,1, 1 };
	context->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_COMconstantBuffer.Get(),
		0,
		NULL,
		&m_COMconstantBufferData,
		0,
		0,
		0
		);

	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;

	context->IASetVertexBuffers(
		0,
		1,
		m_COMvertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_COMindexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
		);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_COMinputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(
		m_COMvertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_COMconstantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// Attach our pixel shader.
	context->PSSetShader(
		m_COMpixelShader.Get(),
		nullptr,
		0
		);

#pragma message("m_indexcount is the same temporarily most likely")

	// Draw the objects.
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

void Sample3DSceneRenderer::CreateDeviceDependentResources(void)
{
	if(g_VisualMiningMode == OK_MODE_MINE)
		{
		// Load shaders asynchronously.
		auto loadVSTask = DX::ReadDataAsync(L"SampleVertexShader.cso");
		auto loadPSTask = DX::ReadDataAsync(L"SamplePixelShader.cso");

		// After the vertex shader file is loaded, create the shader and input layout.
		auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData)
			{
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateVertexShader(
					&fileData[0],
					fileData.size(),
					nullptr,
					&m_vertexShader
					)
				);

			static const D3D11_INPUT_ELEMENT_DESC vertexDesc [] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};

			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateInputLayout(
					vertexDesc,
					ARRAYSIZE(vertexDesc),
					&fileData[0],
					fileData.size(),
					&m_inputLayout
					)
				);
			});

		// After the pixel shader file is loaded, create the shader and constant buffer.
		auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData)
			{
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreatePixelShader(
					&fileData[0],
					fileData.size(),
					nullptr,
					&m_pixelShader
					)
				);

			CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					&m_constantBuffer
					)
				);
			});

		// Load shaders asynchronously.
		auto loadQCGVSTask = DX::ReadDataAsync(L"QcomGridVertexShader.cso");
		auto loadQCGPSTask = DX::ReadDataAsync(L"QcomGridPixelShader.cso");

		// After the vertex shader file is loaded, create the shader and input layout.
		auto createQCGVSTask = loadQCGVSTask.then([this](const std::vector<byte>& fileData)
			{
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateVertexShader(
					&fileData[0],
					fileData.size(),
					nullptr,
					&m_QCGvertexShader
					)
				);

			static const D3D11_INPUT_ELEMENT_DESC vertexDesc [] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};

			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateInputLayout(
					vertexDesc,
					ARRAYSIZE(vertexDesc),
					&fileData[0],
					fileData.size(),
					&m_QCGinputLayout
					)
				);
			});

		// After the pixel shader file is loaded, create the shader and constant buffer.
		auto createQCGPSTask = loadQCGPSTask.then([this](const std::vector<byte>& fileData)
			{
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreatePixelShader(
					&fileData[0],
					fileData.size(),
					nullptr,
					&m_QCGpixelShader
					)
				);

			CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					&m_QCGconstantBuffer
					)
				);
			});

		// Load shaders asynchronously.
		auto loadCOMVSTask = DX::ReadDataAsync(L"comVertexShader.cso");
		auto loadCOMPSTask = DX::ReadDataAsync(L"comPixelShader.cso");

		// After the vertex shader file is loaded, create the shader and input layout.
		auto createCOMVSTask = loadCOMVSTask.then([this](const std::vector<byte>& fileData)
			{
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateVertexShader(
					&fileData[0],
					fileData.size(),
					nullptr,
					&m_COMvertexShader
					)
				);

			static const D3D11_INPUT_ELEMENT_DESC vertexDesc [] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};

			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateInputLayout(
					vertexDesc,
					ARRAYSIZE(vertexDesc),
					&fileData[0],
					fileData.size(),
					&m_COMinputLayout
					)
				);
			});

		// After the pixel shader file is loaded, create the shader and constant buffer.
		auto createCOMPSTask = loadCOMPSTask.then([this](const std::vector<byte>& fileData)
			{
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreatePixelShader(
					&fileData[0],
					fileData.size(),
					nullptr,
					&m_COMpixelShader
					)
				);

			CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					&m_COMconstantBuffer
					)
				);
			});

		// Once both shaders are loaded, create the mesh.
		auto createCubeTask = (createPSTask && createVSTask && createQCGPSTask && createQCGVSTask).then([this] ()
			{
			float f_XScale = 25.0f;
			float f_YScale = 25.0f;

			// Load mesh vertices. Each vertex has a position and a color.
			static const VertexPositionColor cubeVertices[] = 
				{
				{XMFLOAT3(-0.5f * f_XScale, -0.5f * f_YScale, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
				{XMFLOAT3(-0.5f * f_XScale, -0.5f * f_YScale,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
				{XMFLOAT3(-0.5f * f_XScale,  0.5f * f_YScale, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
				{XMFLOAT3(-0.5f * f_XScale,  0.5f * f_YScale,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
				{XMFLOAT3( 0.5f * f_XScale, -0.5f * f_YScale, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
				{XMFLOAT3( 0.5f * f_XScale, -0.5f * f_YScale,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
				{XMFLOAT3( 0.5f * f_XScale,  0.5f * f_YScale, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
				{XMFLOAT3( 0.5f * f_XScale,  0.5f * f_YScale,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
				};

			D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
			vertexBufferData.pSysMem = cubeVertices;
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&vertexBufferDesc,
					&vertexBufferData,
					&m_vertexBuffer
					)
				);

			// Load mesh indices. Each trio of indices represents
			// a triangle to be rendered on the screen.
			// For example: 0,2,1 means that the vertices with indexes
			// 0, 2 and 1 from the vertex buffer compose the 
			// first triangle of this mesh.
			static const unsigned short cubeIndices [] =
				{
				0,2,1, // -x
				1,2,3,

				4,5,6, // +x
				5,7,6,

				0,1,5, // -y
				0,5,4,

				2,6,7, // +y
				2,7,3,

				0,4,6, // -z
				0,6,2,

				1,3,7, // +z
				1,7,5,
				};

			m_indexCount = ARRAYSIZE(cubeIndices);

			D3D11_SUBRESOURCE_DATA indexBufferData = {0};
			indexBufferData.pSysMem = cubeIndices;
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&indexBufferDesc,
					&indexBufferData,
					&m_indexBuffer
					)
				);
			});

		// Once both shaders are loaded, create the mesh.
		auto createComTask = (createCOMPSTask && createCOMVSTask && createCOMPSTask && createCOMVSTask).then([this] ()
			{
			float f_XScale = 1.0f / 1.0f;
			float f_YScale = 1.0f / 1.0f;

			// Load mesh vertices. Each vertex has a position and a color.
			static const VertexPositionColor cubeVertices[] = 
				{
				{XMFLOAT3(-0.5f * f_XScale, -0.5f * f_YScale, -0.6f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
				{XMFLOAT3(-0.5f * f_XScale, -0.5f * f_YScale,  0.6f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
				{XMFLOAT3(-0.5f * f_XScale,  0.5f * f_YScale, -0.6f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
				{XMFLOAT3(-0.5f * f_XScale,  0.5f * f_YScale,  0.6f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
				{XMFLOAT3( 0.5f * f_XScale, -0.5f * f_YScale, -0.6f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
				{XMFLOAT3( 0.5f * f_XScale, -0.5f * f_YScale,  0.6f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
				{XMFLOAT3( 0.5f * f_XScale,  0.5f * f_YScale, -0.6f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
				{XMFLOAT3( 0.5f * f_XScale,  0.5f * f_YScale,  0.6f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
				};

			D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
			vertexBufferData.pSysMem = cubeVertices;
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&vertexBufferDesc,
					&vertexBufferData,
					&m_COMvertexBuffer
					)
				);

			// Load mesh indices. Each trio of indices represents
			// a triangle to be rendered on the screen.
			// For example: 0,2,1 means that the vertices with indexes
			// 0, 2 and 1 from the vertex buffer compose the 
			// first triangle of this mesh.
			static const unsigned short cubeIndices [] =
				{
				0,2,1, // -x
				1,2,3,

				4,5,6, // +x
				5,7,6,

				0,1,5, // -y
				0,5,4,

				2,6,7, // +y
				2,7,3,

				0,4,6, // -z
				0,6,2,

				1,3,7, // +z
				1,7,5,
				};

			m_indexCount = ARRAYSIZE(cubeIndices);

			D3D11_SUBRESOURCE_DATA indexBufferData = {0};
			indexBufferData.pSysMem = cubeIndices;
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&indexBufferDesc,
					&indexBufferData,
					&m_COMindexBuffer
					)
				);
			});

		createComTask.then([this]()
			{
			m_COMloadingComplete = true;
			});

		// Once the cube is loaded, the object is ready to be rendered.
		createCubeTask.then([this] ()
			{
			for(int f_XY = 0; f_XY < g_ADMAX; f_XY++)
				{
				Cube::g_RandomSeed.x += 15.234124;
				Cube::g_RandomSeed.y += 13.1234;
				Cube::g_RandomSeed.z += 14.32487;

				Cube::CubeKEY* f_KEY = new Cube::CubeKEY();
				std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared<Cube::CubeBicycle>();

				f_KEY->m_Link = f_Bicycle;

				// Load mesh vertices. Each vertex has a position and a color.
				Cube::BiRand f_BiRand;
				Cube::BiVector f_Vector1(-0.5f);
				f_Vector1.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				Cube::BiVector f_Vector2(-0.5f, -0.5f, 0.5f);
				f_Vector2.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				Cube::BiVector f_Vector3(-0.5f, 0.5f, -0.5f);
				f_Vector3.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				Cube::BiVector f_Vector4(-0.5f, 0.5f, 0.5f);
				f_Vector4.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				Cube::BiVector f_Vector5(0.5f, -0.5f, -0.5f);
				f_Vector5.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				Cube::BiVector f_Vector6(0.5f, -0.5f, 0.5f);
				f_Vector6.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				Cube::BiVector f_Vector7(0.5f, 0.5f, -0.5f);
				f_Vector7.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				Cube::BiVector f_Vector8(0.5f, 0.5f, 0.5f);
				f_Vector8.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

				Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 13.5), ((Cube::random() - 0.5) * 13.5), ((Cube::random() - 0.5) * 13.5)));

				f_Vector1.acRun_visualminer();
				f_Vector2.acRun_visualminer();
				f_Vector3.acRun_visualminer();
				f_Vector4.acRun_visualminer();
				f_Vector5.acRun_visualminer();
				f_Vector6.acRun_visualminer();
				f_Vector7.acRun_visualminer();
				f_Vector8.acRun_visualminer();

				f_KEY->m_Link->vec_Vertex.push_back(f_Vector1);
				f_KEY->m_Link->vec_Vertex.push_back(f_Vector2);
				f_KEY->m_Link->vec_Vertex.push_back(f_Vector3);
				f_KEY->m_Link->vec_Vertex.push_back(f_Vector4);
				f_KEY->m_Link->vec_Vertex.push_back(f_Vector5);
				f_KEY->m_Link->vec_Vertex.push_back(f_Vector6);
				f_KEY->m_Link->vec_Vertex.push_back(f_Vector7);
				f_KEY->m_Link->vec_Vertex.push_back(f_Vector8);

				Cube::BiVector f_Color1(Cube::random(), Cube::random(), Cube::random());
				Cube::BiVector f_Color2(Cube::random(), Cube::random(), Cube::random());
				Cube::BiVector f_Color3(Cube::random(), Cube::random(), Cube::random());
				Cube::BiVector f_Color4(Cube::random(), Cube::random(), Cube::random());
				Cube::BiVector f_Color5(Cube::random(), Cube::random(), Cube::random());
				Cube::BiVector f_Color6(Cube::random(), Cube::random(), Cube::random());
				Cube::BiVector f_Color7(Cube::random(), Cube::random(), Cube::random());
				Cube::BiVector f_Color8(Cube::random(), Cube::random(), Cube::random());

				f_KEY->m_Link->vec_Color.push_back(f_Color1);
				f_KEY->m_Link->vec_Color.push_back(f_Color2);
				f_KEY->m_Link->vec_Color.push_back(f_Color3);
				f_KEY->m_Link->vec_Color.push_back(f_Color4);
				f_KEY->m_Link->vec_Color.push_back(f_Color5);
				f_KEY->m_Link->vec_Color.push_back(f_Color6);
				f_KEY->m_Link->vec_Color.push_back(f_Color7);
				f_KEY->m_Link->vec_Color.push_back(f_Color8);

				static const VertexPositionColor cubeVertices[] =
					{
					{ XMFLOAT3(f_Vector1.m_X, f_Vector1.m_Y, f_Vector1.m_Z), XMFLOAT3(f_Color1.m_X, f_Color1.m_Y, f_Color1.m_Z) },
					{ XMFLOAT3(f_Vector2.m_X, f_Vector2.m_Y, f_Vector2.m_Z), XMFLOAT3(f_Color2.m_X, f_Color2.m_Y, f_Color2.m_Z) },
					{ XMFLOAT3(f_Vector3.m_X, f_Vector3.m_Y, f_Vector3.m_Z), XMFLOAT3(f_Color3.m_X, f_Color3.m_Y, f_Color3.m_Z) },
					{ XMFLOAT3(f_Vector4.m_X, f_Vector4.m_Y, f_Vector4.m_Z), XMFLOAT3(f_Color4.m_X, f_Color4.m_Y, f_Color4.m_Z) },
					{ XMFLOAT3(f_Vector5.m_X, f_Vector5.m_Y, f_Vector5.m_Z), XMFLOAT3(f_Color5.m_X, f_Color5.m_Y, f_Color5.m_Z) },
					{ XMFLOAT3(f_Vector6.m_X, f_Vector6.m_Y, f_Vector6.m_Z), XMFLOAT3(f_Color6.m_X, f_Color6.m_Y, f_Color6.m_Z) },
					{ XMFLOAT3(f_Vector7.m_X, f_Vector7.m_Y, f_Vector7.m_Z), XMFLOAT3(f_Color7.m_X, f_Color7.m_Y, f_Color7.m_Z) },
					{ XMFLOAT3(f_Vector8.m_X, f_Vector8.m_Y, f_Vector8.m_Z), XMFLOAT3(f_Color8.m_X, f_Color8.m_Y, f_Color8.m_Z) },
					};

				D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
				vertexBufferData.pSysMem = cubeVertices;
				vertexBufferData.SysMemPitch = 0;
				vertexBufferData.SysMemSlicePitch = 0;
				CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
				DX::ThrowIfFailed(
					m_deviceResources->GetD3DDevice()->CreateBuffer(
						&vertexBufferDesc,
						&vertexBufferData,
						&f_KEY->m_Link->m_vertexBuffer
						)
					);

				static const unsigned short cubeIndices[] =
					{
					0,2,1, // -x
					1,2,3,

					4,5,6, // +x
					5,7,6,

					0,1,5, // -y
					0,5,4,

					2,6,7, // +y
					2,7,3,

					0,4,6, // -z
					0,6,2,

					1,3,7, // +z
					1,7,5,
					};

				f_KEY->m_Link->m_indexCount = ARRAYSIZE(cubeIndices);

				D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
				indexBufferData.pSysMem = cubeIndices;
				indexBufferData.SysMemPitch = 0;
				indexBufferData.SysMemSlicePitch = 0;
				CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
				DX::ThrowIfFailed(
					m_deviceResources->GetD3DDevice()->CreateBuffer(
						&indexBufferDesc,
						&indexBufferData,
						&f_KEY->m_Link->m_indexBuffer
						)
					);

				Cube::g_BicycleContainer[0].vec_Key.push_back(f_KEY);
				}

			m_loadingComplete = true;
			});
		}
}

struct VertexBufferType
{
	XMFLOAT3 vertex[16];
};

void Sample3DSceneRenderer::acGen_Hesha(void)
{
#if 0
	Cube::g_Count_Muti.ac_Fire();
	Cube::g_Other_Muti.ac_Fire();
	Cube::g_Share_Muti.ac_Fire();
#endif

	bool f_SAVE = false;

	if((g_StampProvider >= g_StampSize) || 1)
		{
		g_StampProvider = 0.0f;

		g_StampSize *= 2.0f;

		if(g_StampSize > 4000000)
			{
			g_StampSize = 1.0f;
			}

		std::shared_ptr<Cube::CubeHASH_originstring> f_Hash = std::make_shared<Cube::CubeHASH_originstring>();

		std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared<Cube::CubeHESH>();

		   /////////////
		  /////////////
		 // getWork
		//
#if 0
		g_Schedular[0]->getWork(ESL_PATTERN_LAST);

		g_Contract->prepWork();
#endif

		for(int f_Int = 0; f_Int < g_ADMAX; f_Int++)
			{
			std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>(); // Cube::g_BicycleContainer[0].vec_Key[f_Int];

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			Cube::BiVector f_Vector1(-0.5f);
			f_Vector1.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector2(-0.5f, -0.5f, 0.5f);
			f_Vector2.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector3(-0.5f, 0.5f, -0.5f);
			f_Vector3.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector4(-0.5f, 0.5f, 0.5f);
			f_Vector4.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector5(0.5f, -0.5f, -0.5f);
			f_Vector5.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector6(0.5f, -0.5f, 0.5f);
			f_Vector6.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector7(0.5f, 0.5f, -0.5f);
			f_Vector7.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector8(0.5f, 0.5f, 0.5f);
			f_Vector8.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			Cube::BiVector f_Color1(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color2(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color3(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color4(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color5(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color6(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color7(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color8(Cube::random(), Cube::random(), Cube::random());

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

#if 1
			f_Vector1.acRun_visualminer();
			f_Vector2.acRun_visualminer();
			f_Vector3.acRun_visualminer();
			f_Vector4.acRun_visualminer();
			f_Vector5.acRun_visualminer();
			f_Vector6.acRun_visualminer();
			f_Vector7.acRun_visualminer();
			f_Vector8.acRun_visualminer();
#endif

			f_Bike->vec_Vertex.clear();

			f_Hash->acPushFloat(f_Vector1.m_X);
			f_Hash->acPushFloat(f_Vector1.m_Y);
			f_Hash->acPushFloat(f_Vector1.m_Z);
			f_Hash->acPushFloat(f_Vector2.m_X);
			f_Hash->acPushFloat(f_Vector2.m_Y);
			f_Hash->acPushFloat(f_Vector2.m_Z);
			f_Hash->acPushFloat(f_Vector3.m_X);
			f_Hash->acPushFloat(f_Vector3.m_Y);
			f_Hash->acPushFloat(f_Vector3.m_Z);
			f_Hash->acPushFloat(f_Vector4.m_X);
			f_Hash->acPushFloat(f_Vector4.m_Y);
			f_Hash->acPushFloat(f_Vector4.m_Z);
			f_Hash->acPushFloat(f_Vector5.m_X);
			f_Hash->acPushFloat(f_Vector5.m_Y);
			f_Hash->acPushFloat(f_Vector5.m_Z);
			f_Hash->acPushFloat(f_Vector6.m_X);
			f_Hash->acPushFloat(f_Vector6.m_Y);
			f_Hash->acPushFloat(f_Vector6.m_Z);
			f_Hash->acPushFloat(f_Vector7.m_X);
			f_Hash->acPushFloat(f_Vector7.m_Y);
			f_Hash->acPushFloat(f_Vector7.m_Z);
			f_Hash->acPushFloat(f_Vector8.m_X);
			f_Hash->acPushFloat(f_Vector8.m_Y);
			f_Hash->acPushFloat(f_Vector8.m_Z);

			f_Bike->vec_Vertex.push_back(f_Vector1);
			f_Bike->vec_Vertex.push_back(f_Vector2);
			f_Bike->vec_Vertex.push_back(f_Vector3);
			f_Bike->vec_Vertex.push_back(f_Vector4);
			f_Bike->vec_Vertex.push_back(f_Vector5);
			f_Bike->vec_Vertex.push_back(f_Vector6);
			f_Bike->vec_Vertex.push_back(f_Vector7);
			f_Bike->vec_Vertex.push_back(f_Vector8);

			f_Hash->acPushFloat(f_Color1.m_X);
			f_Hash->acPushFloat(f_Color1.m_Y);
			f_Hash->acPushFloat(f_Color1.m_Z);
			f_Hash->acPushFloat(f_Color2.m_X);
			f_Hash->acPushFloat(f_Color2.m_Y);
			f_Hash->acPushFloat(f_Color2.m_Z);
			f_Hash->acPushFloat(f_Color3.m_X);
			f_Hash->acPushFloat(f_Color3.m_Y);
			f_Hash->acPushFloat(f_Color3.m_Z);
			f_Hash->acPushFloat(f_Color4.m_X);
			f_Hash->acPushFloat(f_Color4.m_Y);
			f_Hash->acPushFloat(f_Color4.m_Z);
			f_Hash->acPushFloat(f_Color5.m_X);
			f_Hash->acPushFloat(f_Color5.m_Y);
			f_Hash->acPushFloat(f_Color5.m_Z);
			f_Hash->acPushFloat(f_Color6.m_X);
			f_Hash->acPushFloat(f_Color6.m_Y);
			f_Hash->acPushFloat(f_Color6.m_Z);
			f_Hash->acPushFloat(f_Color7.m_X);
			f_Hash->acPushFloat(f_Color7.m_Y);
			f_Hash->acPushFloat(f_Color7.m_Z);
			f_Hash->acPushFloat(f_Color8.m_X);
			f_Hash->acPushFloat(f_Color8.m_Y);
			f_Hash->acPushFloat(f_Color8.m_Z);

			f_Bike->vec_Color.clear();

			f_Bike->vec_Color.push_back(f_Color1);
			f_Bike->vec_Color.push_back(f_Color2);
			f_Bike->vec_Color.push_back(f_Color3);
			f_Bike->vec_Color.push_back(f_Color4);
			f_Bike->vec_Color.push_back(f_Color5);
			f_Bike->vec_Color.push_back(f_Color6);
			f_Bike->vec_Color.push_back(f_Color7);
			f_Bike->vec_Color.push_back(f_Color8);

			f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);
			}

		//hesh admax limiter
		float f_Finger = Cube::random();

#ifndef ECOIN_ADMAX_MAX
		float f_LimitSenseFLT = (((float)g_ADMAX - ECOIN_HESH_MINIMUM) * f_Finger) + ECOIN_HESH_MINIMUM;
		int f_LimitSense = (int)f_LimitSenseFLT;
#else
		int f_LimitSense = g_ADMAX;
#endif

		int f_PORTcntr = 0;
		while(f_Hesh_Cade->m_adIndex.size() < f_LimitSense)
			{
			f_Hesh_Cade->m_adIndex.push_back(f_PORTcntr);
			f_Hash->acPushInt((unsigned int)f_PORTcntr);

			f_PORTcntr++;
			}

		Cube::BiVector f_ColorBCK(Cube::random(), Cube::random(), Cube::random());

		f_Hash->acPushFloat(f_ColorBCK.m_X);
		f_Hash->acPushFloat(f_ColorBCK.m_Y);
		f_Hash->acPushFloat(f_ColorBCK.m_Z);

		//g_HeshCount++;


			////////////
		   //
		  // Hash
		 //
		int f_ShareID = 1;
		int f_BlockID = 1;
		int f_JobID = 1;	//Fixme pass out jobid
		int f_EslID = 1;
		int f_TargetID = 1;
		float f_Difficulty = 6840.0f; //Target Mark Threshold

		  ////////////
		 // HESH   //
		// Target //

		f_Hesh_Cade->m_bckred = f_ColorBCK.m_X;
		f_Hesh_Cade->m_bckgreen = f_ColorBCK.m_Y;
		f_Hesh_Cade->m_bckblue = f_ColorBCK.m_Z;

		f_Hesh_Cade->ac_IsOK();

		g_Result = false;

		//g_Type Switch
		switch(g_Type)
			{
			case 0:
			case 1:
				{
				std::shared_ptr<classTarget> f_Target = std::make_shared<classTarget>(f_Hesh_Cade);

				g_Result = g_Target_1->acCompare(f_Target, 80.55f, f_Difficulty, true);

				gf_Target_1 = f_Target;
				}break;
			case 2:
				{
				std::shared_ptr<classTarget> f_Target = std::make_shared<classTarget>(f_Hesh_Cade);

				g_Result = g_Target_2->acCompare(f_Target, 80.55f, f_Difficulty, true);

				gf_Target_2 = f_Target;
				}break;
			case 3:
				{
				std::shared_ptr<classTarget_Ecom> f_Target = std::make_shared<classTarget_Ecom>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_3);

				g_Result = g_Target_3->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_3 = f_Target;
				}break;
			case 4:
				{
				std::shared_ptr<classTarget_Ecom> f_Target = std::make_shared<classTarget_Ecom>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_4);

				g_Result = g_Target_4->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_4 = f_Target;
				}break;
			case 5:
				{
				std::shared_ptr<classTarget_ESL_Script> f_Target = std::make_shared<classTarget_ESL_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_5);

				g_Result = g_Target_5->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_5 = f_Target;
				}break;
			case 6:
				{
				std::shared_ptr<classTarget_ESL_Script> f_Target = std::make_shared<classTarget_ESL_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_6);

				g_Result = g_Target_6->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_6 = f_Target;
				}break;
			case 7:
				{
				std::shared_ptr<classTarget_Generation_Script> f_Target = std::make_shared<classTarget_Generation_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_7);

				g_Result = g_Target_7->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_7 = f_Target;
				}break;
			case 8:
				{
				std::shared_ptr<classTarget_Generation_Script> f_Target = std::make_shared<classTarget_Generation_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_8);

				g_Result = g_Target_8->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_8 = f_Target;
				}break;
			case 9:
				{
				std::shared_ptr<classTarget_JScript> f_Target = std::make_shared<classTarget_JScript>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_9);

				g_Result = g_Target_9->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_9 = f_Target;
				}break;
			case 10:
				{
				std::shared_ptr<classTarget_JScript> f_Target = std::make_shared<classTarget_JScript>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_10);

				g_Result = g_Target_10->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_10 = f_Target;
				}break;
			}

#if 0
		g_HeshCount++;
#else
		g_ElementCount += f_Hesh_Cade->m_adIndex.size();
#endif

		g_Result = false; //g_Target->acCompare(f_Target, 80.55f, f_Difficulty, true);
											//15.95

		if(g_Result)
			{
#if 0
			printf("HeshExt: %s\n", ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)g_Hesh_Extention)).c_str());
#endif
			f_Hesh_Cade->m_Hash = f_Hash;

			char* g_sharevalue[60];

			for(int f_Count = 0; f_Count < 60; f_Count++)
				{
				g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
				}

			sprintf(g_sharevalue[0], "%f", ag_Get_current_Target_Mark(g_Type));
			sprintf(g_sharevalue[1], "%i", 1);
			sprintf(g_sharevalue[2], "%s", "3");
			sprintf(g_sharevalue[4], "%i", f_EslID);
			sprintf(g_sharevalue[5], "%i", f_TargetID);
			sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
			sprintf(g_sharevalue[7], "%f", f_Difficulty);

				////////////
			   //
			  // Hash
			 //
			std::string f_InputHash = f_Hash->acGetInput();

			// check GenesisBlock (assume)
			std::string f_previousblock = "00000000000000000000000000000001";
			printf("ECN::Hesh...Checking Previous BlockHesh\n");

#if 1
			Cube::g_Count_Muti.ac_Fire();
			Cube::g_Other_Muti.ac_Fire();
			Cube::g_Share_Muti.ac_Fire();
#endif

			char blokquery[1000];
			sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");
			g_SafeL[0]->acSelectCommand(blokquery, 2, false);
			int f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

			printf("ECN::Stat::: f_TrxLCount %i\n", f_blokLCount);

			g_JobID = 0;

			//assume remote connection for windows
			if(f_blokLCount > 0)
				{
				g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
				g_JobID++;
				f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
				}

			f_JobID = g_JobID;

			sprintf(g_sharevalue[3], "%i", f_JobID);

			printf("ECN::Stat::: g_JobID %i\n", g_JobID);

			std::string f_tx = ag_GatherTransactions(g_JobID);

			std::string f_job = f_tx + f_previousblock;

			f_InputHash += f_job;

			//hey you could add a nonce here

			g_hasha.init(); //reset hasher state
			g_hasha.process(f_InputHash.begin(), f_InputHash.end());
			g_hasha.finish();
			picosha2::get_hash_hex_string(g_hasha, f_Hash->m_OutputHash);

			f_Hesh_Cade->m_Hash = f_Hash;

			printf("ShareHash-%s\n", f_Hash->m_OutputHash.c_str());

			sprintf(g_sharevalue[8], "%i", 0);
			sprintf(g_sharevalue[9], "%i", 10);
			sprintf(g_sharevalue[10], "%s", f_Hash->m_OutputHash.c_str());
			sprintf(g_sharevalue[11], "%s", f_Hash->m_OutputHash.c_str());
			sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
			sprintf(g_sharevalue[13], "%f", f_Hesh_Cade->m_bckred);
			sprintf(g_sharevalue[14], "%f", f_Hesh_Cade->m_bckgreen);
			sprintf(g_sharevalue[15], "%f", f_Hesh_Cade->m_bckblue);
			sprintf(g_sharevalue[16], "%f", 0.0f);

			printf("ECN::Hesh...Sending BlockHesh\n");

			char shlquery[1000];
			sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", f_Hash->m_OutputHash.c_str());// WHERE name = '%s' AND pass = MD5('%s')", i_name, i_password);
																				//Run the query
			g_SafeL[0]->acSelectCommand(shlquery, 2, false);
			int f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

			printf("ECN::Stat::: f_ShareLCount %i\n", f_ShareLCount);

			if(f_ShareLCount == 0)
				{
				int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

				f_ShareID = f_ShareUniqueID;
				g_ShareID = f_ShareID;

				printf("ECN::Stat::: f_ShareID %i f_shareuniqueID %i\n", f_ShareID, f_ShareUniqueID);

				ag_addGenesisTracking(f_ShareUniqueID);
				
				char* f_idquery2 = new char[150];
				sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);
				g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);

				int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
				int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

				g_PEERCNT = f_PEERCNT;
				g_SHARECNT = f_SHARECNT;

				g_PerShareCount++;

#if 1
				for(int f_Int = 0; f_Int < f_Hesh_Cade->m_adIndex.size(); f_Int++)
					{
					std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[f_Hesh_Cade->m_adIndex[f_Int]];

					char* g_cubevalue[60];

					for(int f_Count = 0; f_Count < 60; f_Count++)
						{
						g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
						}

					for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
						{
						sprintf(g_cubevalue[f_Int2 * 3], "%f", f_Bike->vec_Vertex[f_Int2].m_X);
						sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%f", f_Bike->vec_Vertex[f_Int2].m_Y);
						sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%f", f_Bike->vec_Vertex[f_Int2].m_Z);
						}

					for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
						{
						sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%f", f_Bike->vec_Color[f_Int3].m_X);
						sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%f", f_Bike->vec_Color[f_Int3].m_Y);
						sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%f", f_Bike->vec_Color[f_Int3].m_Z);
						}
				
					sprintf(g_cubevalue[48], "%i", f_BlockID);
					sprintf(g_cubevalue[49], "%i", f_ShareID);
					sprintf(g_cubevalue[50], "%i", f_JobID);
					sprintf(g_cubevalue[51], "%i", f_EslID);
					sprintf(g_cubevalue[52], "%i", f_TargetID);
					sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
					sprintf(g_cubevalue[54], "%f", f_Difficulty);

					g_CubeFieldCount = 55;

					int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
					}
#endif

				printf("ECN::Share Submitted.\n");

#if 1
				Ackent* f_Ack = new Ackent(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
				f_Ack->m_ECN = 0.0f;
				f_Ack->m_Reward = 50.0f;
				f_Ack->m_Origin = 1;
				f_Ack->m_Owner = g_Wallet->GetAdr();
				g_Ackent.push_back(f_Ack);
#endif

				f_SAVE = true;
				}
			else
				{
				printf("Duplicate Block Found.\n");
				g_Result = false;
				}

#if 1
			Cube::g_Count_Muti.ac_Free();
			Cube::g_Other_Muti.ac_Free();
			Cube::g_Share_Muti.ac_Free();
#endif
			}
		else
			{
			float f_Mark = ag_Get_current_Target_Mark(g_Type);

			if(f_Mark < g_LowtonMark)
				{
				g_LowtonMark = f_Mark;
				g_Lowton = f_Hesh_Cade;
				g_LowtonHash = f_Hash;

				switch(g_Type)
					{
					case 0:
					case 1:
						{
						g_LowtonTarget_1 = gf_Target_1;
						}break;
					case 2:
						{
						g_LowtonTarget_2 = gf_Target_2;
						}break;
					case 3:
						{
						g_LowtonTarget_3 = gf_Target_3;
						}break;
					case 4:
						{
						g_LowtonTarget_4 = gf_Target_4;
						}break;
					case 5:
						{
						g_LowtonTarget_5 = gf_Target_5;
						}break;
					case 6:
						{
						g_LowtonTarget_6 = gf_Target_6;
						}break;
					case 7:
						{
						g_LowtonTarget_7 = gf_Target_7;
						}break;
					case 8:
						{
						g_LowtonTarget_8 = gf_Target_8;
						}break;
					case 9:
						{
						g_LowtonTarget_9 = gf_Target_9;
						}break;
					case 10:
						{
						g_LowtonTarget_10 = gf_Target_10;
						}break;
					}

				f_SAVE = true;

				g_TargetedHesh = g_Lowton;

				g_TargetedHesh->ac_IsOK();

				g_RenderHesh = true;

				printf("New LowTon Holding...(%f)\n", g_LowtonMark);
				}

			time(&g_currenttime);

			if(g_currenttime > g_storagetime)
				{
				time(&g_storagetime);
				g_storagetime += ECOIN_TARGET_LOWTON_STORAGE;

				char* g_sharevalue[60];

				for(int f_Count = 0; f_Count < 60; f_Count++)
					{
					g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
					}

				sprintf(g_sharevalue[0], "%f", g_LowtonMark);
				sprintf(g_sharevalue[1], "%i", 1);
				sprintf(g_sharevalue[2], "%s", "3");
				sprintf(g_sharevalue[4], "%i", 15);
				sprintf(g_sharevalue[5], "%i", 15);
				sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
				sprintf(g_sharevalue[7], "%f", f_Difficulty);

					////////////
				   //
				  // Hash
				 //
				//char *lx = (char*)malloc(g_LowtonHash->m_vec_Input.size() * 8 * sizeof(char));
				//ag_bin2hex(lx, g_LowtonHash->m_vec_Input, g_LowtonHash->m_vec_Input.size());
				std::string f_InputHash = g_LowtonHash->acGetInput();

				// check GenesisBlock (assume)
				std::string f_previousblock = "00000000000000000000000000000001";
				printf("ECN::Hesh...Checking Previous BlockHesh\n");

#if 1
				Cube::g_Count_Muti.ac_Fire();
				Cube::g_Other_Muti.ac_Fire();
				Cube::g_Share_Muti.ac_Fire();
#endif

				char blokquery[1000];
				sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");
				g_SafeL[0]->acSelectCommand(blokquery, 2, false);
				int f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

				printf("ECN::Stat::: f_TrxLCount %i\n", f_blokLCount);

				g_JobID = 0;

				//assume remote connection for windows
				if(f_blokLCount > 0)
					{
					g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
					g_JobID++;
					f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
					}

				f_JobID = g_JobID;

				sprintf(g_sharevalue[3], "%i", f_JobID);

				printf("ECN::Stat::: g_JobID %i\n", g_JobID);

				std::string f_tx = ag_GatherTransactions(g_JobID);

				std::string f_job = f_tx + f_previousblock;

				f_InputHash += f_job;

				//hey you could add a nonce here

				g_hasha.init(); //reset hasher state
				g_hasha.process(f_InputHash.begin(), f_InputHash.end());
				g_hasha.finish();
				picosha2::get_hash_hex_string(g_hasha, g_LowtonHash->m_OutputHash);

				g_Lowton->m_Hash = g_LowtonHash;

				g_LowtonMark = 10000000.0f;

				printf("ShareHash-%s\n", g_LowtonHash->m_OutputHash.c_str());

				sprintf(g_sharevalue[8], "%i", 0);
				sprintf(g_sharevalue[9], "%i", 10);
				sprintf(g_sharevalue[10], "%s", g_LowtonHash->m_OutputHash.c_str());
				sprintf(g_sharevalue[11], "%s", g_LowtonHash->m_OutputHash.c_str());
				sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
				sprintf(g_sharevalue[13], "%f", g_Lowton->m_bckred);
				sprintf(g_sharevalue[14], "%f", g_Lowton->m_bckgreen);
				sprintf(g_sharevalue[15], "%f", g_Lowton->m_bckblue);
				sprintf(g_sharevalue[16], "%f", 0.0f);

				printf("ECN::Hesh...Sending BlockHesh\n");

				char shlquery[1000];
				sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", g_LowtonHash->m_OutputHash.c_str());// WHERE name = '%s' AND pass = MD5('%s')", i_name, i_password);
																					//Run the query
				g_SafeL[0]->acSelectCommand(shlquery, 2, false);
				int f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

				printf("ECN::Stat::: f_ShareLCount %i\n", f_ShareLCount);

				if(f_ShareLCount == 0)
					{
					int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

					f_ShareID = f_ShareUniqueID;
					g_ShareID = f_ShareID;

					printf("ECN::Stat::: f_ShareID %i f_shareuniqueID %i\n", f_ShareID, f_ShareUniqueID);

					ag_addGenesisTracking(f_ShareUniqueID);
				
					char* f_idquery2 = new char[150];
					sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);
					g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);

					int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
					int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

					g_PEERCNT = f_PEERCNT;
					g_SHARECNT = f_SHARECNT;

					g_PerShareCount++;

					for (int f_Int = 0; f_Int < g_Lowton->m_adIndex.size(); f_Int++)
						{
						shared_ptr<CubeBicycle> f_Bike = g_Lowton->vec_Bicycle[g_Lowton->m_adIndex[f_Int]];
						char* g_cubevalue[60];

						for(int f_Count = 0; f_Count < 60; f_Count++)
							{
							g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
							}

						for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
							{
							sprintf(g_cubevalue[f_Int2 * 3], "%f", f_Bike->vec_Vertex[f_Int2].m_X);
							sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%f", f_Bike->vec_Vertex[f_Int2].m_Y);
							sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%f", f_Bike->vec_Vertex[f_Int2].m_Z);
							}

						for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
							{
							sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%f", f_Bike->vec_Color[f_Int3].m_X);
							sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%f", f_Bike->vec_Color[f_Int3].m_Y);
							sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%f", f_Bike->vec_Color[f_Int3].m_Z);
							}
				
						sprintf(g_cubevalue[48], "%i", f_BlockID);
						sprintf(g_cubevalue[49], "%i", f_ShareID);
						sprintf(g_cubevalue[50], "%i", f_JobID);
						sprintf(g_cubevalue[51], "%i", f_EslID);
						sprintf(g_cubevalue[52], "%i", 1);	//FIXME ADD L-TARGETID
						sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
						sprintf(g_cubevalue[54], "%f", f_Difficulty);

						g_CubeFieldCount = 55;

						int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
						}

					printf("ECN::Lowton Share Submitted.\n");

#if 1
					Ackent* f_Ack = new Ackent(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
					f_Ack->m_ECN = 0.0f;
					f_Ack->m_Reward = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = g_Wallet->GetAdr();
					g_Ackent.push_back(f_Ack);
#endif

					f_SAVE = true;
					}
				else
					{
					printf("Duplicate Block Found.\n");
					g_Result = false;
					}

#if 1
				Cube::g_Count_Muti.ac_Free();
				Cube::g_Other_Muti.ac_Free();
				Cube::g_Share_Muti.ac_Free();
#endif
				}
			}

		if(!f_SAVE)
			{
			f_Hesh_Cade->acClear();
			}
		}
	else
		{
		g_StampProvider += 1.0f;
		}

#if 0
	g_Hesh_Extention.clear();
#endif

#if 0
	Cube::g_Count_Muti.ac_Free();
	Cube::g_Other_Muti.ac_Free();
	Cube::g_Share_Muti.ac_Free();
#endif
}

void Sample3DSceneRenderer::MapBuffers(void)
{
#if 0
	   /////////////
	  /////////////
	 // getWork
	//
	g_Schedular[0]->getWork(ESL_PATTERN_LAST);

	for(int f_Int = 0; f_Int < g_ADMAX; f_Int++)
		{
		Cube::CubeKEY* f_KEY = Cube::g_BicycleContainer[0].vec_Key[f_Int];

		// Load mesh vertices. Each vertex has a position and a color.
		Cube::BiRand f_BiRand;
		Cube::BiVector f_Vector1(-0.5f);
		f_Vector1.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		Cube::BiVector f_Vector2(-0.5f, -0.5f, 0.5f);
		f_Vector2.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		Cube::BiVector f_Vector3(-0.5f, 0.5f, -0.5f);
		f_Vector3.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		Cube::BiVector f_Vector4(-0.5f, 0.5f, 0.5f);
		f_Vector4.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		Cube::BiVector f_Vector5(0.5f, -0.5f, -0.5f);
		f_Vector5.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		Cube::BiVector f_Vector6(0.5f, -0.5f, 0.5f);
		f_Vector6.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		Cube::BiVector f_Vector7(0.5f, 0.5f, -0.5f);
		f_Vector7.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		Cube::BiVector f_Vector8(0.5f, 0.5f, 0.5f);
		f_Vector8.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

		Cube::BiVector f_Color1(Cube::random(), Cube::random(), Cube::random());
		Cube::BiVector f_Color2(Cube::random(), Cube::random(), Cube::random());
		Cube::BiVector f_Color3(Cube::random(), Cube::random(), Cube::random());
		Cube::BiVector f_Color4(Cube::random(), Cube::random(), Cube::random());
		Cube::BiVector f_Color5(Cube::random(), Cube::random(), Cube::random());
		Cube::BiVector f_Color6(Cube::random(), Cube::random(), Cube::random());
		Cube::BiVector f_Color7(Cube::random(), Cube::random(), Cube::random());
		Cube::BiVector f_Color8(Cube::random(), Cube::random(), Cube::random());

#if 0
		Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

		f_Vector1.acRun_visualminer();
		f_Vector2.acRun_visualminer();
		f_Vector3.acRun_visualminer();
		f_Vector4.acRun_visualminer();
		f_Vector5.acRun_visualminer();
		f_Vector6.acRun_visualminer();
		f_Vector7.acRun_visualminer();
		f_Vector8.acRun_visualminer();
#endif

		f_KEY->m_Link->vec_Vertex.clear();

		f_KEY->m_Link->vec_Vertex.push_back(f_Vector1);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector2);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector3);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector4);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector5);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector6);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector7);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector8);

		f_KEY->m_Link->vec_Color.clear();

		f_KEY->m_Link->vec_Color.push_back(f_Color1);
		f_KEY->m_Link->vec_Color.push_back(f_Color2);
		f_KEY->m_Link->vec_Color.push_back(f_Color3);
		f_KEY->m_Link->vec_Color.push_back(f_Color4);
		f_KEY->m_Link->vec_Color.push_back(f_Color5);
		f_KEY->m_Link->vec_Color.push_back(f_Color6);
		f_KEY->m_Link->vec_Color.push_back(f_Color7);
		f_KEY->m_Link->vec_Color.push_back(f_Color8);
		}

	for(int f_Int = 0; f_Int < Cube::g_BicycleContainer[0].vec_Key.size(); f_Int++)
		{
		Cube::CubeKEY* f_KEY = Cube::g_BicycleContainer[0].vec_Key[f_Int];

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		VertexBufferType* dataPtr;

		// Lock the constant buffer so it can be written to.
		HRESULT result = m_deviceResources->GetD3DDeviceContext()->Map(f_KEY->m_Link->m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
			{
			throw std::exception("GetD3DDeviceContext()->Map buffer map failed");
			}

		// Get a pointer to the data in the constant buffer.
		dataPtr = (VertexBufferType*)mappedResource.pData;

		int f_VertexCount = 0;
		for (int f_Count = 0; f_Count < 16; f_Count+=2)
			{
			//Cube::float4 f_pos(dataPtr->vertex[f_Count].x, dataPtr->vertex[f_Count].y, dataPtr->vertex[f_Count].z, 1.0f);
			//f_pos = Cube::g_model * f_pos;

			dataPtr->vertex[f_Count].x = f_KEY->m_Link->vec_Vertex[f_VertexCount].m_X;
			dataPtr->vertex[f_Count].y = f_KEY->m_Link->vec_Vertex[f_VertexCount].m_Y;
			dataPtr->vertex[f_Count].z = f_KEY->m_Link->vec_Vertex[f_VertexCount].m_Z;

			f_VertexCount++;

			dataPtr->vertex[f_Count + 1].x = f_KEY->m_Link->vec_Color[f_VertexCount].m_X;
			dataPtr->vertex[f_Count + 1].y = f_KEY->m_Link->vec_Color[f_VertexCount].m_Y;
			dataPtr->vertex[f_Count + 1].z = f_KEY->m_Link->vec_Color[f_VertexCount].m_Z;
			}

		// Unlock the constant buffer.
		m_deviceResources->GetD3DDeviceContext()->Unmap(f_KEY->m_Link->m_vertexBuffer.Get(), 0);
		}
#endif
}

void Sample3DSceneRenderer::RestoreTargetedBuffers(void)
{
	if(g_TargetedHesh)
		{
		if(g_SelectedHeshID >= Cube::g_HESH.size())
			{
			g_SelectedHeshID = Cube::g_HESH.size() - 1;
			}

		g_TargetedHesh->ac_IsOK();

		for(int f_Int = 0; f_Int < g_TargetedHesh->vec_Bicycle.size(); f_Int++)
			{
			shared_ptr<CubeBicycle> f_Bicycle = g_TargetedHesh->vec_Bicycle[f_Int];

			if (f_Int < g_ADMAX)
				{
				f_Bicycle->m_vertexBuffer = Cube::g_BicycleContainer[0].vec_Key[f_Int]->m_Link->m_vertexBuffer;
				f_Bicycle->m_indexBuffer = Cube::g_BicycleContainer[0].vec_Key[f_Int]->m_Link->m_indexBuffer;
				
				D3D11_MAPPED_SUBRESOURCE mappedResource;
				VertexBufferType* dataPtr;

				// Lock the constant buffer so it can be written to.
				HRESULT result = m_deviceResources->GetD3DDeviceContext()->Map(f_Bicycle->m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
				if (FAILED(result))
					{
					throw std::exception("GetD3DDeviceContext()->Map buffer map failed");
					}

				// Get a pointer to the data in the constant buffer.
				dataPtr = (VertexBufferType*)mappedResource.pData;

				int f_VertexCount = 0;
				for (int f_Count = 0; f_Count < 16; f_Count+=2)
					{
					if(f_VertexCount < f_Bicycle->vec_Vertex.size())
						{
						dataPtr->vertex[f_Count].x = f_Bicycle->vec_Vertex[f_VertexCount].m_X;
						dataPtr->vertex[f_Count].y = f_Bicycle->vec_Vertex[f_VertexCount].m_Y;
						dataPtr->vertex[f_Count].z = f_Bicycle->vec_Vertex[f_VertexCount].m_Z;

						f_VertexCount++;
						}

					if(f_VertexCount < f_Bicycle->vec_Color.size())
						{
						dataPtr->vertex[f_Count + 1].x = f_Bicycle->vec_Color[f_VertexCount].m_X;
						dataPtr->vertex[f_Count + 1].y = f_Bicycle->vec_Color[f_VertexCount].m_Y;
						dataPtr->vertex[f_Count + 1].z = f_Bicycle->vec_Color[f_VertexCount].m_Z;
						}
					}

				// Unlock the constant buffer.
				m_deviceResources->GetD3DDeviceContext()->Unmap(f_Bicycle->m_vertexBuffer.Get(), 0);
				}
			}
		}
}

void Sample3DSceneRenderer::RestoreBuffers(void)
{
#if 0
	if(g_SelectedHeshID >= Cube::g_HESH.size())
		{
		g_SelectedHeshID = Cube::g_HESH.size() - 1;
		}

	for(int f_Int = 0; f_Int < Cube::g_BicycleContainer[0].vec_Key.size(); f_Int++)
		{
		Cube::CubeKEY* f_KEY = Cube::g_BicycleContainer[0].vec_Key[f_Int];

		f_KEY->m_Link->vec_Vertex.clear();

		for(int f_CountVertex = 0; f_CountVertex < Cube::g_HESH[g_SelectedHeshID]->vec_Bicycle[f_Int]->vec_Vertex.size(); f_CountVertex++)
			{
			Cube::BiVector f_Vector = Cube::g_HESH[g_SelectedHeshID]->vec_Bicycle[f_Int]->vec_Vertex[f_CountVertex];

			f_KEY->m_Link->vec_Vertex.push_back(f_Vector);
			}

		f_KEY->m_Link->vec_Color.clear();

		for(int f_CountColor = 0; f_CountColor < Cube::g_HESH[g_SelectedHeshID]->vec_Bicycle[f_Int]->vec_Color.size(); f_CountColor++)
			{
			Cube::BiVector f_Color = Cube::g_HESH[g_SelectedHeshID]->vec_Bicycle[f_Int]->vec_Color[f_CountColor];

			f_KEY->m_Link->vec_Color.push_back(f_Color);
			}

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		VertexBufferType* dataPtr;

		// Lock the constant buffer so it can be written to.
		HRESULT result = m_deviceResources->GetD3DDeviceContext()->Map(f_KEY->m_Link->m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
			{
			throw std::exception("GetD3DDeviceContext()->Map buffer map failed");
			}

		// Get a pointer to the data in the constant buffer.
		dataPtr = (VertexBufferType*)mappedResource.pData;

		int f_VertexCount = 0;
		for (int f_Count = 0; f_Count < 16; f_Count+=2)
			{
			dataPtr->vertex[f_Count].x = f_KEY->m_Link->vec_Vertex[f_VertexCount].m_X;
			dataPtr->vertex[f_Count].y = f_KEY->m_Link->vec_Vertex[f_VertexCount].m_Y;
			dataPtr->vertex[f_Count].z = f_KEY->m_Link->vec_Vertex[f_VertexCount].m_Z;

			f_VertexCount++;

			dataPtr->vertex[f_Count + 1].x = f_KEY->m_Link->vec_Color[f_VertexCount].m_X;
			dataPtr->vertex[f_Count + 1].y = f_KEY->m_Link->vec_Color[f_VertexCount].m_Y;
			dataPtr->vertex[f_Count + 1].z = f_KEY->m_Link->vec_Color[f_VertexCount].m_Z;
			}

		// Unlock the constant buffer.
		m_deviceResources->GetD3DDeviceContext()->Unmap(f_KEY->m_Link->m_vertexBuffer.Get(), 0);
		}
#endif
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	m_vertexShader.Reset();
	m_inputLayout.Reset();
	m_pixelShader.Reset();
	m_constantBuffer.Reset();
	m_QCGvertexShader.Reset();
	m_QCGinputLayout.Reset();
	m_QCGpixelShader.Reset();
	m_QCGconstantBuffer.Reset();
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
}

bool Sample3DSceneRenderer::MapResources(Cube::CubeKEY* f_KEY)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexBufferType* dataPtr;

	// Lock the constant buffer so it can be written to.
	HRESULT result = m_deviceResources->GetD3DDeviceContext()->Map(f_KEY->m_Link->m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
		{
		throw std::exception("GetD3DDeviceContext()->Map buffer map failed");
		}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (VertexBufferType*)mappedResource.pData;

	for(int f_Count = 0; f_Count < 16; f_Count++)
		{
		Cube::float4 f_pos(dataPtr->vertex[f_Count].x, dataPtr->vertex[f_Count].y, dataPtr->vertex[f_Count].z, 1.0f);

		f_pos = Cube::g_model * f_pos;

		dataPtr->vertex[f_Count].x = (Cube::random() - 0.5) * 10;
		dataPtr->vertex[f_Count].y = (Cube::random() - 0.5) * 10;
		dataPtr->vertex[f_Count].z = (Cube::random() - 0.5) * 10;
		}

	// Unlock the constant buffer.
	m_deviceResources->GetD3DDeviceContext()->Unmap(f_KEY->m_Link->m_vertexBuffer.Get(), 0);

#if 0
	// Finanly set the constant buffer in the vertex shader with the updated values.
	m_deviceResources->GetD3DDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
#endif

	return true;
}

void Sample3DSceneRenderer::Reorientate(Cube::CubeKEY* f_KEY)
{
	for (int f_Count = 0; f_Count < f_KEY->m_Link->vec_Vertex.size(); f_Count++)
		{
		f_KEY->m_Link->vec_Vertex[f_Count]->acPrepare();
		}
}