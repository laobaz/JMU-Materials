# -*- coding: utf-8 -*-

import tensorrt as trt

def ONNX2TRT(args, calib=None):
    ''' convert onnx to tensorrt engine, use mode of ['fp32', 'fp16', 'int8']
    :return: trt engine
    '''

    assert args.mode.lower() in ['fp32', 'fp16', 'int8'], "mode should be in ['fp32', 'fp16', 'int8']"

    G_LOGGER = trt.Logger(trt.Logger.WARNING)
    # TRT7中的onnx解析器的network，需要指定EXPLICIT_BATCH
    EXPLICIT_BATCH = 1 << (int)(trt.NetworkDefinitionCreationFlag.EXPLICIT_BATCH)

    with trt.Builder(G_LOGGER) as builder, builder.create_network(
            EXPLICIT_BATCH) as network, builder.create_builder_config() as builder_config:
        #builder_config.max_workspace_size = workspace_size * (1024 * 1024)
        # builder_config.avg_timing_iterations = 8
        # if config.use_fp16:
        #     builder_config.set_flag(trt.BuilderFlag.FP16)
        # if config.use_int8:
        #     builder_config.set_flag(trt.BuilderFlag.INT8)
        #     if not config.use_qat:
        #         calibrator = BertCalibrator(squad_json, vocab_file, calibrationCacheFile, 1, sequence_lengths[-1],
        #                                     calib_num)
        #         builder_config.set_quantization_flag(trt.QuantizationFlag.CALIBRATE_BEFORE_FUSION)
        #         builder_config.int8_calibrator = calibrator
        # if config.use_strict:
        #     builder_config.set_flag(trt.BuilderFlag.STRICT_TYPES)
        #
        # if verbose:
        #     builder_config.profiling_verbosity = trt.ProfilingVerbosity.DETAILED
        #
        # if config.use_sparsity:
        #     TRT_LOGGER.log(TRT_LOGGER.INFO, "Setting sparsity flag on builder_config.")
        #     builder_config.set_flag(trt.BuilderFlag.SPARSE_WEIGHTS)


        # builder.max_batch_size = args.batch_size
        #
        # builder.max_workspace_size = 1 << 30
        #config = builder.create_builder_config()
        builder_config.max_workspace_size=args.batch_size
        builder_config.max_workspace_size = 1 << 30
        if args.mode.lower() == 'int8':
            assert (builder.platform_has_fast_int8 == True), "not support int8"
            builder_config.set_flag(trt.BuilderFlag.INT8)
           # bulidr.int8_mode = True
            builder.int8_calibrator = calib
        elif args.mode.lower() == 'fp16':
            assert (builder.platform_has_fast_fp16 == True), "not support fp16"
            builder_config.set_flag(trt.BuilderFlag.FP16)

        print('Loading ONNX file from path {}...'.format(args.onnx_file_path))
        with open(args.onnx_file_path, 'rb') as model:
            print('Beginning ONNX file parsing')
            if not parse(model.read()):
                for e in range(builder_config.num_errors):
                    print(builder_config.get_error(e))
                raise TypeError("Parser parse failed.")

        print('Completed parsing of ONNX file')

        print('Building an engine from file {}; this may take a while...'.format(args.onnx_file_path))
        engine = builder.build_cuda_engine(network)
        print("Created engine success! ")

        # 保存计划文件
        print('Saving TRT engine file to path {}...'.format(args.engine_file_path))
        with open(args.engine_file_path, "wb") as f:
            f.write(engine.serialize())
        print('Engine file has already saved to {}!'.format(args.engine_file_path))
        return engine


def loadEngine2TensorRT(filepath):
    '''
    通过加载计划文件，构建TensorRT运行引擎
    '''
    G_LOGGER = trt.Logger(trt.Logger.WARNING)
    # 反序列化引擎
    with open(filepath, "rb") as f, trt.Runtime(G_LOGGER) as runtime:
        engine = runtime.deserialize_cuda_engine(f.read())
        return engine
