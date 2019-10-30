#include <kraBlob.h>

#include "kraD3D11Shader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  bool
  ShaderDX::compileShaderFromFile(const WString filename,
                                  String entryPoint,
                                  String shaderModel)
  {

    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(filename.c_str(),
                            nullptr,
                            D3D_COMPILE_STANDARD_FILE_INCLUDE,
                            entryPoint.c_str(),
                            shaderModel.c_str(),
                            dwShaderFlags,
                            0,
                            &m_pBlob,
                            &pErrorBlob);

    if (FAILED(hr))
    {
      if (pErrorBlob) {
        String errorMsg;
        errorMsg += String("\n") + static_cast<const char*>(pErrorBlob->GetBufferPointer());
        //throw std::runtime_error(errorMsg);

        std::cout << "Error: " << errorMsg;
        pErrorBlob->Release();

        return false;
      }
    }
    

    return true;
  }


}