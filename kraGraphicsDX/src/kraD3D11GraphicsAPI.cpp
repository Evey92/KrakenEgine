#include "kraD3D11GraphicsAPI.h"



namespace kraEngineSDK {
  
  Device*
  GraphicsAPIDX::initializeAPI(void* g_hWnd) {
    
    //HWND m_hWnd = reinterpret_cast<HWND>(g_hWnd);
    
    HRESULT hr = S_OK;
    
    //Init device and Swap Chain
        
    hr = m_device.initializeDevice(g_hWnd);
   
    if (FAILED(hr))
    {
      return false;
    }
    
    return &m_device;
  }

  void
  GraphicsAPIDX::Render() {
    
    /*Vector4 clearColor = { 1.0f, 0.125f, 0.3f, 1.0f };
    m_device.m_pImmediateContext->ClearRenderTargetView(m_renderTargetView.m_pRenderTargetView, &clearColor[0]);
    m_device.m_pImmediateContext->VSSetShader(m_vertexShader.m_pVertexShader, NULL, 0);
    m_device.m_pImmediateContext->PSSetShader(m_pixelShader.m_pPixelShader, NULL, 0);
    m_device.m_pImmediateContext->Draw(3, 0);*/

   // m_device->m_pImmediateContext->VSSetShader(m_vertexShader.m_pVertexShader, NULL, 0);
   // m_device->m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_neverChanges.m_pBuffer);
   // m_device->m_pImmediateContext->VSSetConstantBuffers(1, 1, &m_changesOnResize.m_pBuffer);
   // m_device->m_pImmediateContext->VSSetConstantBuffers(2, 1, &m_changesEveryFrame.m_pBuffer);
   // m_device->m_pImmediateContext->PSSetShader(m_pixelShader.m_pPixelShader, NULL, 0);
   // m_device->m_pImmediateContext->PSSetConstantBuffers(2, 1, &m_changesEveryFrame.m_pBuffer);
   // m_device->m_pImmediateContext->PSSetShaderResources(0, 1, &m_shaderRV.m_pTextureRV);
    //m_device.m_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
    m_device.m_pImmediateContext->DrawIndexed(36, 0, 0);

    m_device.m_pSwapChain.m_pd3dSwapChain->Present(0, 0);

  }

  void
  GraphicsAPIDX::Cleanup() {
    
    m_device.cleanContextState();
    
   /* m_vertexBuffer.cleanVertexBuffer();
    m_indexbuffer.cleanIndexBuffer();
    m_inputLayout.cleanInputLayout();
    m_vertexShader.cleanShader();
    m_pixelShader.cleanShader();
    m_device.cleanDepthStencil(&m_depthS);
    m_depthStencilView.cleanDSV();
    m_renderTargetView.cleanRTV();*/
    m_device.cleanSwapChain();
    m_device.cleanContext();
    m_device.cleanDevice();
  }
}