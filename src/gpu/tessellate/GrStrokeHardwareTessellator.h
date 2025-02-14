/*
 * Copyright 2020 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrStrokeHardwareTessellator_DEFINED
#define GrStrokeHardwareTessellator_DEFINED

#include "src/gpu/GrVertexChunkArray.h"
#include "src/gpu/tessellate/GrStrokeTessellator.h"

// Renders opaque, constant-color strokes by decomposing them into standalone tessellation patches.
// Each patch is either a "cubic" (single stroked bezier curve with butt caps) or a "join". Requires
// MSAA if antialiasing is desired.
class GrStrokeHardwareTessellator : public GrStrokeTessellator {
public:
    GrStrokeHardwareTessellator(ShaderFlags shaderFlags, const GrShaderCaps& shaderCaps,
                                const SkMatrix& viewMatrix, PathStrokeList* pathStrokeList,
                                std::array<float,2> matrixMinMaxScales, const SkRect&
                                strokeCullBounds)
            : GrStrokeTessellator(GrStrokeTessellationShader::Mode::kHardwareTessellation,
                                  shaderFlags, SkNextLog2(shaderCaps.maxTessellationSegments()),
                                  viewMatrix, pathStrokeList, matrixMinMaxScales,
                                  strokeCullBounds) {
    }

    void prepare(GrMeshDrawTarget*, int totalCombinedVerbCnt) override;
    void draw(GrOpFlushState*) const override;

private:
    GrVertexChunkArray fPatchChunks;
};

#endif
