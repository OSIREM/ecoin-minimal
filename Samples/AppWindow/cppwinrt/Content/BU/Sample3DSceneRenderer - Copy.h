#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

#include <collection.h>
#include <ppltasks.h>

#include "Include\Cube.h"

namespace ecoin
{
	// This sample renderer instantiates a basic rendering pipeline.
	class Sample3DSceneRenderer
		{
		public:
			Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
			void CreateDeviceDependentResources();
			bool MapResources(Cube::CubeKEY* f_KEY);
			void MapBuffers(void);
			void Reorientate(Cube::CubeKEY* f_KEY);
			void RestoreBuffers(void);
			void RestoreTargetedBuffers(void);
			void CreateWindowSizeDependentResources();
			void ReleaseDeviceDependentResources();
			void Update(DX::StepTimer const& timer);
			void Render(int f_Index);
			void Render_Qcom(void);
			void Render_COM(float f_X, float f_Y);
			void StartTracking();
			void TrackingUpdate(float positionX);
			void StopTracking();
			bool IsTracking() { return m_tracking; }

			void acGen_Hesha(void);

			picosha2::hash256_one_by_one m_hasha;

		private:
			void Rotate(float radians);

		private:
			// Cached pointer to device resources.
			std::shared_ptr<DX::DeviceResources> m_deviceResources;

			// Direct3D resources for cube geometry.
			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_QCGinputLayout;
			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_COMinputLayout;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_COMvertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_COMindexBuffer;
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_QCGvertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_QCGpixelShader;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_QCGconstantBuffer;
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_COMvertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_COMpixelShader;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_COMconstantBuffer;

			// System resources for cube geometry.
			ModelViewProjectionConstantBuffer	m_constantBufferData;
			ModelViewProjectionConstantBuffer	m_QCGconstantBufferData;
			ModelViewProjectionConstantBuffer	m_COMconstantBufferData;
			uint32	m_indexCount;

			// Variables used with the rendering loop.
			bool	m_loadingComplete;
			bool	m_COMloadingComplete;
			float	m_degreesPerSecond;
			bool	m_tracking;
		};
}

