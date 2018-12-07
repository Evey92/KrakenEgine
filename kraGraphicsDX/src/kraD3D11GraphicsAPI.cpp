#include "kraD3D11GraphicsAPI.h"
#include "ConstantBufferMatrices.h"


namespace kraEngineSDK {
  
  HRESULT
  GraphicsAPI::initializeAPI(HWND g_hWnd) {
    HRESULT hr = S_OK;
    /*
    * Init device and Swap Chain
    * Create Render target view
    * Create Depth Stencil texture
    * Create Depth Stencil view
    * Set Viewport
    * Compile vertex Shader
    * Create Vertex Shader
    * Define Input Layout
    * Create Input Layout
    * Set input Layout
    * compile pixel shader
    * Create Pixel shader
    * Create vertex buffer
    * Creat Index Buffer
    * Set Primitive topology 
    * Create Constant buffer
    * Load texture
    * Create Sample State
    * Initialize world Matrices
    * Initialize view Matrices
    * Initialize project Matrices
    */
    
    m_device.initializeDevice(g_hWnd);
    m_renderTargetView.createRenderTargetView(m_device.m_pd3dDevice,
                                             m_device.m_pSwapChain);

    m_depthStencil.createDepthStencil(m_device.m_pd3dDevice, 
                                      m_device.m_height,
                                      m_device.m_width);

    m_depthStencilView.createDepthStencilView(m_device.m_pd3dDevice,
                                              &m_depthStencil);
    m_device.setRenderTarget(m_renderTargetView.m_pRenderTargetView,
                             m_depthStencilView.m_pDepthStencilView);
   
    m_viewport.createViewport(m_device.m_width, m_device.m_height, 0, 0);

    m_viewport.setViewport(m_device.m_pImmediateContext);

    if (FAILED(m_vertexShader.compileVertexShader(L"VS.hlsl", "VS")))
    {
      std::cout <<"Failed to compile shader\n";
      return 0;
    }

    m_vertexShader.createVertexShader(m_device.m_pd3dDevice);

    m_inputLayout.defineVertexLayout();
    m_inputLayout.defineTexcoordLayout();
    m_inputLayout.createInputLayout(m_device.m_pd3dDevice,
                                    &m_vertexShader);
    m_inputLayout.setInputLayout(m_device.m_pImmediateContext);

    if (FAILED(m_pixelShader.compilePixelShader(L"PS.hlsl", "PS")))
    {
      std::cout << "Failed to compile shader\n";
      return 0;
    }

    m_pixelShader.createPixelShader(m_device.m_pd3dDevice);

    /*Vertex vert1(Vector3(0.0f, 0.5f, 0.5f));
    m_vertexBuffer.add(vert1);
    Vertex vert2(Vector3(0.5f, -0.5f, 0.5f));
    m_vertexBuffer.add(vert2);
    Vertex vert3(Vector3(-0.5f, -0.5f, 0.5f));
    m_vertexBuffer.add(vert3);*/

    Vertex vert1(Vector3(-1.0f, 1.0f, -1.0f));
    vert1.Tex = Vector2(0.0f, 0.0f);
    m_vertexBuffer.add(vert1);
    Vertex vert2(Vector3(1.0f, 1.0f, -1.0f));
    vert2.Tex = Vector2(1.0f, 0.0f);
    m_vertexBuffer.add(vert2);
    Vertex vert3(Vector3(1.0f, 1.0f, 1.0f));
    vert3.Tex = Vector2(1.0f, 1.0f);
    m_vertexBuffer.add(vert3);
    Vertex vert4(Vector3(-1.0f, 1.0f, 1.0f));
    vert4.Tex = Vector2(0.0f, 1.0f);
    m_vertexBuffer.add(vert4);

    Vertex vert5(Vector3(-1.0f, -1.0f, -1.0f));
    vert5.Tex = Vector2(0.0f, 0.0f);
    m_vertexBuffer.add(vert5);
    Vertex vert6(Vector3(1.0f, -1.0f, -1.0f));
    vert6.Tex = Vector2(1.0f, 0.0f);
    m_vertexBuffer.add(vert6);
    Vertex vert7(Vector3(1.0f, -1.0f, 1.0f));
    vert7.Tex = Vector2(1.0f, 1.0f);
    m_vertexBuffer.add(vert7);
    Vertex vert8(Vector3(-1.0f, -1.0f, 1.0f));
    vert8.Tex = Vector2(0.0f, 1.0f);
    m_vertexBuffer.add(vert8);

    Vertex vert9(Vector3(-1.0f, -1.0f, 1.0f));
    vert9.Tex = Vector2(0.0f, 0.0f);
    m_vertexBuffer.add(vert9);
    Vertex vert10(Vector3(-1.0f, -1.0f, -1.0f));
    vert10.Tex = Vector2(1.0f, 0.0f);
    m_vertexBuffer.add(vert10);
    Vertex vert11(Vector3(-1.0f, 1.0f, -1.0f));
    vert11.Tex = Vector2(1.0f, 1.0f);
    m_vertexBuffer.add(vert11);
    Vertex vert12(Vector3(-1.0f, 1.0f, 1.0f));
    vert12.Tex = Vector2(0.0f, 1.0f);
    m_vertexBuffer.add(vert12);

    Vertex vert13(Vector3(1.0f, -1.0f, 1.0f));
    vert13.Tex = Vector2(0.0f, 0.0f);
    m_vertexBuffer.add(vert13);
    Vertex vert14(Vector3(1.0f, -1.0f, -1.0f));
    vert14.Tex = Vector2(1.0f, 0.0f);
    m_vertexBuffer.add(vert14);
    Vertex vert15(Vector3(1.0f, 1.0f, -1.0f));
    vert15.Tex = Vector2(1.0f, 1.0f);
    m_vertexBuffer.add(vert15);
    Vertex vert16(Vector3(1.0f, 1.0f, 1.0f));
    vert16.Tex = Vector2(0.0f, 1.0f);
    m_vertexBuffer.add(vert16);

    Vertex vert17(Vector3(-1.0f, -1.0f, -1.0f));
    vert17.Tex = Vector2(0.0f, 0.0f);
    m_vertexBuffer.add(vert17);
    Vertex vert18(Vector3(-1.0f, -1.0f, -1.0f));
    vert18.Tex = Vector2(1.0f, 0.0f);
    m_vertexBuffer.add(vert18);
    Vertex vert19(Vector3(1.0f, 1.0f, -1.0f));
    vert19.Tex = Vector2(1.0f, 1.0f);
    m_vertexBuffer.add(vert19);
    Vertex vert20(Vector3(-1.0f, 1.0f, -1.0f));
    vert20.Tex = Vector2(0.0f, 1.0f);
    m_vertexBuffer.add(vert20);

    Vertex vert21(Vector3(-1.0f, -1.0f, 1.0f));
    vert21.Tex = Vector2(0.0f, 0.0f);
    m_vertexBuffer.add(vert21);
    Vertex vert22(Vector3(1.0f, -1.0f, 1.0f));
    vert22.Tex = Vector2(1.0f, 0.0f);
    m_vertexBuffer.add(vert22);
    Vertex vert23(Vector3(1.0f, 1.0f, 1.0f));
    vert23.Tex = Vector2(1.0f, 1.0f);
    m_vertexBuffer.add(vert23);
    Vertex vert24(Vector3(-1.0f, 1.0f, 1.0f));
    vert24.Tex = Vector2(0.0f, 1.0f);
    m_vertexBuffer.add(vert24);

    m_vertexBuffer.createHardwareBuffer(m_device.m_pd3dDevice);
    m_vertexBuffer.setVertexBuffer(m_device.m_pImmediateContext);

    unsigned short index;
    //////////////////////////////////////////////////////////////////////////
    index = 3;
    m_indexbuffer.add(index);
    index = 1;
    m_indexbuffer.add(index);
    index = 0;
    m_indexbuffer.add(index);

    index = 2;
    m_indexbuffer.add(index);
    index = 1;
    m_indexbuffer.add(index);
    index = 3;
    m_indexbuffer.add(index);

    index = 6;
    m_indexbuffer.add(index);
    index = 4;
    m_indexbuffer.add(index);
    index = 5;
    m_indexbuffer.add(index);

    index = 7;
    m_indexbuffer.add(index);
    index = 4;
    m_indexbuffer.add(index);
    index = 6;
    m_indexbuffer.add(index);

    index = 11;
    m_indexbuffer.add(index);
    index = 9;
    m_indexbuffer.add(index);
    index = 8;
    m_indexbuffer.add(index);

    index = 10;
    m_indexbuffer.add(index);
    index = 9;
    m_indexbuffer.add(index);
    index = 11;
    m_indexbuffer.add(index);

    index = 14;
    m_indexbuffer.add(index);
    index = 12;
    m_indexbuffer.add(index);
    index = 13;
    m_indexbuffer.add(index);

    index = 15;
    m_indexbuffer.add(index);
    index = 12;
    m_indexbuffer.add(index);
    index = 14;
    m_indexbuffer.add(index);

    index = 19;
    m_indexbuffer.add(index);
    index = 17;
    m_indexbuffer.add(index);
    index = 16;
    m_indexbuffer.add(index);

    index = 18;
    m_indexbuffer.add(index);
    index = 17;
    m_indexbuffer.add(index);
    index = 19;
    m_indexbuffer.add(index);

    index = 22;
    m_indexbuffer.add(index);
    index = 20;
    m_indexbuffer.add(index);
    index = 22;
    m_indexbuffer.add(index);

    index = 23;
    m_indexbuffer.add(index);
    index = 20;
    m_indexbuffer.add(index);
    index = 22;
    m_indexbuffer.add(index);

    m_indexbuffer.createHardwareBuffer(m_device.m_pd3dDevice);

    m_indexbuffer.setIndexBuffer(m_device.m_pImmediateContext);    


    m_neverChanges.createHardwareBuffer(m_device.m_pd3dDevice);
    m_changesOnResize.createHardwareBuffer(m_device.m_pd3dDevice);
    m_changesEveryFrame.createHardwareBuffer(m_device.m_pd3dDevice);

    m_device.m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    Texture m_cubeTexture;
    m_cubeTexture.createTexture2DFromFile(m_device.m_pd3dDevice, "cube.png",
                                          DXGI_FORMAT_R8G8B8A8_UNORM,
                                          D3D11_BIND_SHADER_RESOURCE);

    m_shaderRV.createShaderResourceView(m_device.m_pd3dDevice,
                                        m_cubeTexture.m_pd3dTexture2D);
    m_shaderRV.setShaderResourceView(m_device.m_pImmediateContext);
    
    //m_World.identity();

    Vector4 Eye = Vector4(0.0f, 3.0f, -6.0f, 0.0f);
    Vector4 At = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4 Up = Vector4(0.0f, 1.0f, 0.0f, 0.0f);

    //m_View.MatrixLookAtLH(Eye, At, Up);

    CBNeverChanges constNeverChange;
    //constNeverChange.m_view.transpose();
    m_device.m_pImmediateContext->UpdateSubresource(m_neverChanges.m_pBuffer,
                                                    0, nullptr,
                                                    &constNeverChange, 0, 0);

    //m_Projection = ;

    CBChangeOnResize constChangeResize;
    //constChangeResize.m_projection.transpose();
    m_device.m_pImmediateContext->UpdateSubresource(m_changesOnResize.m_pBuffer,
                                                    0, nullptr,
                                                    &constChangeResize,
                                                    0, 0);
    /*
    * TODO:
    * -Make the Matrix4.PerspectiveFOVLH;
    * After Setup, call Render
    */
   

    return hr;
  }

  void
  GraphicsAPI::Render() {
    
    /*Vector4 clearColor = { 1.0f, 0.125f, 0.3f, 1.0f };
    m_device.m_pImmediateContext->ClearRenderTargetView(m_renderTargetView.m_pRenderTargetView, &clearColor[0]);
    m_device.m_pImmediateContext->VSSetShader(m_vertexShader.m_pVertexShader, NULL, 0);
    m_device.m_pImmediateContext->PSSetShader(m_pixelShader.m_pPixelShader, NULL, 0);
    m_device.m_pImmediateContext->Draw(3, 0);*/

    m_device.m_pImmediateContext->VSSetShader(m_vertexShader.m_pVertexShader, NULL, 0);
    m_device.m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_neverChanges.m_pBuffer);
    m_device.m_pImmediateContext->VSSetConstantBuffers(1, 1, &m_changesOnResize.m_pBuffer);
    m_device.m_pImmediateContext->VSSetConstantBuffers(2, 1, &m_changesEveryFrame.m_pBuffer);
    m_device.m_pImmediateContext->PSSetShader(m_pixelShader.m_pPixelShader, NULL, 0);
    m_device.m_pImmediateContext->PSSetConstantBuffers(2, 1, &m_changesEveryFrame.m_pBuffer);
    m_device.m_pImmediateContext->PSSetShaderResources(0, 1, &m_shaderRV.m_pTextureRV);
    //m_device.m_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
    m_device.m_pImmediateContext->DrawIndexed(36, 0, 0);

    m_device.m_pSwapChain->Present(0, 0);

  }

  void
  GraphicsAPI::Cleanup() {
    
    m_device.cleanContextState();
    
    m_vertexBuffer.cleanVertexBuffer();
    m_indexbuffer.cleanIndexBuffer();
    m_inputLayout.cleanInputLayout();
    m_vertexShader.cleanShader();
    m_pixelShader.cleanShader();
    m_depthStencil.cleanDepthStencil();
    m_depthStencilView.cleanDSV();
    m_renderTargetView.cleanRTV();
    m_device.cleanSwapChain();
    m_device.cleanContext();
    m_device.cleanDevice();
  }
}