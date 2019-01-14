//===----------- SpirvExecutionModel.h - SPIR-V Execution Model -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//===----------------------------------------------------------------------===//
//
//  This file defines a SPIR-V execution model class that takes in HLSL shader
//  model or shader attribute stagename and sets spv::ExecutionModel
//
//===----------------------------------------------------------------------===//

#ifndef SPIRV_EXECUTION_MODEL_H
#define SPIRV_EXECUTION_MODEL_H

#include "dxc/DXIL/DxilShaderModel.h"
#include "spirv/unified1/GLSL.std.450.h"
#include "clang/SPIRV/SpirvType.h"

namespace clang {
namespace spirv {

/// SPIR-V execution class.
class SpirvExecutionModel {
public:
  using HlslKind = hlsl::ShaderModel::Kind;
  using SpvModel = spv::ExecutionModel;

  bool IsPS() const { return execModel == SpvModel::Fragment; }
  bool IsVS() const { return execModel == SpvModel::Vertex; }
  bool IsGS() const { return execModel == SpvModel::Geometry; }
  bool IsHS() const { return execModel == SpvModel::TessellationControl; }
  bool IsDS() const { return execModel == SpvModel::TessellationEvaluation; }
  bool IsCS() const { return execModel == SpvModel::GLCompute; }
  bool IsRay() const {
    return execModel >= SpvModel::RayGenerationNV &&
           execModel <= SpvModel::CallableNV;
  }
  bool IsValid() const;

  HlslKind GetShaderKind() const { return shaderKind; }
  SpvModel GetExecutionModel() const { return execModel; }

  static const SpirvExecutionModel *GetByStageName(const StringRef &stageName);
  static const SpirvExecutionModel *GetByShaderKind(HlslKind sk);

private:
  HlslKind shaderKind;
  SpvModel execModel;

  SpirvExecutionModel() = delete;
  SpirvExecutionModel(HlslKind sk, SpvModel em)
      : shaderKind(sk), execModel(em) {}

  static const unsigned numExecutionModels = 14;
  static const SpirvExecutionModel executionModels[numExecutionModels];
};

} // end namespace spirv
} // end namespace clang

#endif // SPIRV_EXECUTION_MODEL_H
