import nndeploy._nndeploy_internal as _C

# 优化pass

# 算子融合
FuseConvBias = _C.net.OptPassType.kOptPassTypeFuseConvBias
FuseConvBatchNorm = _C.net.OptPassType.kOptPassTypeFuseConvBatchNorm
FuseConvRelu = _C.net.OptPassType.kOptPassTypeFuseConvRelu


# 消除冗余算子
EliminateCommonSubexpression = (
    _C.net.OptPassType.kOptPassTypeEliminateCommonSubexpression
)
EliminateDeadOp = _C.net.OptPassType.kOptPassTypeEliminateDeadOp