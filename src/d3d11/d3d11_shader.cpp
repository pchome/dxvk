#include "d3d11_device.h"
#include "d3d11_shader.h"

namespace dxvk {

  D3D11ShaderModule:: D3D11ShaderModule() { }
  D3D11ShaderModule::~D3D11ShaderModule() { }


  D3D11ShaderModule::D3D11ShaderModule(
    const DxbcOptions*  pDxbcOptions,
          D3D11Device*  pDevice,
    const void*         pShaderBytecode,
          size_t        BytecodeLength) {
    DxbcReader reader(
      reinterpret_cast<const char*>(pShaderBytecode),
      BytecodeLength);

    DxbcModule module(reader);

    // Construct the shader name that we'll use for
    // debug messages and as the dump/read file name
    m_name = ConstructFileName(
      ComputeShaderHash(pShaderBytecode, BytecodeLength),
      module.version().type());

    Logger::debug(str::format("Compiling shader ", m_name));

    // If requested by the user, dump both the raw DXBC
    // shader and the compiled SPIR-V module to a file.
#ifdef WANT_ENV
    const std::string dumpPath = env::getEnvVar(L"DXVK_SHADER_DUMP_PATH");
    const std::string readPath = env::getEnvVar(L"DXVK_SHADER_READ_PATH");
#else
    const std::string dumpPath = "dxvk_shader_dump";
    const std::string readPath = "dxvk_shader_read";
#endif

    const std::string dxbcFileName    = str::format(dumpPath, "/", m_name, ".dxbc");
    const std::string spvFileName     = str::format(dumpPath, "/", m_name, ".spv");
    const std::string spvReadFileName = str::format(readPath, "/", m_name, ".spv");

    bool dxbcExists    = std::ifstream(dxbcFileName.c_str()).good();
    bool spvExists     = std::ifstream(spvFileName.c_str()).good();
    bool spvReadExists = std::ifstream(spvReadFileName.c_str()).good();


    Logger::debug(str::format("DXBC:", dxbcExists, " - SPV:", spvExists, " - SPV-opt:", spvReadExists));
    // read spv
    if(spvReadExists) {
      std::ifstream readStream(spvReadFileName, std::ios_base::binary);
      if (readStream) {
        m_shader = module.compile(*pDxbcOptions);
        m_shader->setDebugName(m_name);

        m_shader->read(std::move(readStream));
        Logger::debug("EARLY overrided");
      }
      return;
    }

    // dump dxbc
    if (dumpPath.size() != 0 && !dxbcExists) {
      reader.store(std::ofstream(dxbcFileName, std::ios_base::binary | std::ios_base::trunc));
      dxbcExists = true;
    }

    m_shader = module.compile(*pDxbcOptions);
    m_shader->setDebugName(m_name);

    // dump clean spv
    if (dumpPath.size() != 0 && !spvExists) {
      m_shader->dump(std::ofstream(spvFileName, std::ios_base::binary | std::ios_base::trunc));
      spvExists = true;
    }

#ifdef WANT_ENV
    // FIXME this is currently way too slow to be viable
    // as a default option, but may help Nvidia users.
    if (env::getEnvVar(L"DXVK_SHADER_OPTIMIZE") == "1") {
      if (!m_shader->optimize()) {
        Logger::warn(str::format("Failed to optimize: ", m_name));
      } else {
        // dump optimized spv
        if (readPath.size() != 0 && !spvReadExists) {
          m_shader->dump(std::ofstream(spvReadFileName, std::ios_base::binary | std::ios_base::trunc));
          spvReadExists = true;
        }
      }

    }

    if (env::getEnvVar(L"DXVK_SHADER_VALIDATE") == "1") {
      if (!m_shader->validate())
        Logger::warn(str::format("Invalid shader: ", m_name));
    }
#else
    if (!m_shader->optimize()) {
      Logger::warn(str::format("Failed to optimize: ", m_name));
    } else {
      // dump optimized spv
      if (readPath.size() != 0 && !spvReadExists) {
        m_shader->dump(std::ofstream(spvReadFileName, std::ios_base::binary | std::ios_base::trunc));
        spvReadExists = true;
      }
    }
#endif


/*
    // If requested by the user, replace
    // the shader with another file.
    if (readPath.size() != 0 && spvReadExists) {
      // Check whether the file exists
      std::ifstream readStream(
        str::format(readPath, "/", m_name, ".spv"),
        std::ios_base::binary);

      if (readStream)
        m_shader->read(std::move(readStream));
    }
*/
  }


  Sha1Hash D3D11ShaderModule::ComputeShaderHash(
    const void*   pShaderBytecode,
          size_t  BytecodeLength) const {
    return Sha1Hash::compute(
      reinterpret_cast<const uint8_t*>(pShaderBytecode),
      BytecodeLength);
  }


  std::string D3D11ShaderModule::ConstructFileName(
    const Sha1Hash&         hash,
    const DxbcProgramType&  type) const {
    std::string typeStr;

    switch (type) {
      case DxbcProgramType::PixelShader:    typeStr = "PS_"; break;
      case DxbcProgramType::VertexShader:   typeStr = "VS_"; break;
      case DxbcProgramType::GeometryShader: typeStr = "GS_"; break;
      case DxbcProgramType::HullShader:     typeStr = "HS_"; break;
      case DxbcProgramType::DomainShader:   typeStr = "DS_"; break;
      case DxbcProgramType::ComputeShader:  typeStr = "CS_"; break;
    }

    return str::format(typeStr, hash.toString());
  }

}
