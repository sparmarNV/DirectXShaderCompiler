//===--------- SpirvExecutionModel.cpp - SPIR-V Execution Model -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//===----------------------------------------------------------------------===//
//
//  This file implements SPIR-V execution model class that takes in HLSL shader
//  model or shader attribute stagename and sets spv::ExecutionModel
//
//===----------------------------------------------------------------------===//

#include "SpirvExecutionModel.h"

namespace clang {
namespace spirv {

bool SpirvExecutionModel::IsValid() const {
  assert(IsPS() || IsVS() || IsGS() || IsHS() || IsDS() || IsCS() || IsRay() ||
         execModel == SpvModel::Max);
  return execModel != SpvModel::Max;
}

const SpirvExecutionModel *
SpirvExecutionModel::GetByStageName(const llvm::StringRef &stageName) {
  const SpirvExecutionModel *em;
  switch (stageName[0]) {
  case 'c':
    switch (stageName[1]) {
    case 'o':
      em = GetByShaderKind(HlslKind::Compute);
      break;
    case 'l':
      em = GetByShaderKind(HlslKind::ClosestHit);
      break;
    case 'a':
      em = GetByShaderKind(HlslKind::Callable);
      break;
    default:
      em = GetByShaderKind(HlslKind::Invalid);
      break;
    }
    break;
  case 'v':
    em = GetByShaderKind(HlslKind::Vertex);
    break;
  case 'h':
    em = GetByShaderKind(HlslKind::Hull);
    break;
  case 'd':
    em = GetByShaderKind(HlslKind::Domain);
    break;
  case 'g':
    em = GetByShaderKind(HlslKind::Geometry);
    break;
  case 'p':
    em = GetByShaderKind(HlslKind::Pixel);
    break;
  case 'r':
    em = GetByShaderKind(HlslKind::RayGeneration);
    break;
  case 'i':
    em = GetByShaderKind(HlslKind::Intersection);
    break;
  case 'a':
    em = GetByShaderKind(HlslKind::AnyHit);
    break;
  case 'm':
    em = GetByShaderKind(HlslKind::Miss);
    break;
  default:
    em = GetByShaderKind(HlslKind::Invalid);
    break;
  }
  if (!em->IsValid()) {
  }
  return em;
}

const SpirvExecutionModel *SpirvExecutionModel::GetByShaderKind(HlslKind sk) {
  int idx = (int)sk;
  assert(idx < numExecutionModels);
  return &executionModels[idx];
}

typedef SpirvExecutionModel SEM;
const SpirvExecutionModel SpirvExecutionModel::executionModels
    [SpirvExecutionModel::numExecutionModels] = {
        // Note: below sequence should match DXIL::ShaderKind
        // DXIL::ShaderKind <--> spv::ExecutionModel
        SEM(HlslKind::Pixel, SpvModel::Fragment),
        SEM(HlslKind::Vertex, SpvModel::Vertex),
        SEM(HlslKind::Geometry, SpvModel::Geometry),
        SEM(HlslKind::Hull, SpvModel::TessellationControl),
        SEM(HlslKind::Domain, SpvModel::TessellationEvaluation),
        SEM(HlslKind::Compute, SpvModel::GLCompute),
        SEM(HlslKind::Library, SpvModel::Max),
        SEM(HlslKind::RayGeneration, SpvModel::RayGenerationNV),
        SEM(HlslKind::Intersection, SpvModel::IntersectionNV),
        SEM(HlslKind::AnyHit, SpvModel::AnyHitNV),
        SEM(HlslKind::ClosestHit, SpvModel::ClosestHitNV),
        SEM(HlslKind::Miss, SpvModel::MissNV),
        SEM(HlslKind::Callable, SpvModel::CallableNV),
        SEM(HlslKind::Invalid, SpvModel::Max)};

} // end namespace spirv
} // end namespace clang
