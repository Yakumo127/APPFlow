/**
 *
 * @file FITKMeshGenOFInterface.h
 * @brief openfoam网格生成
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-07-17
 *
 */
#ifndef _FITK_MESHGEN_OF_INTERFACE_H___
#define _FITK_MESHGEN_OF_INTERFACE_H___

#include "FITKMeshGenOFAPI.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponentInterface.h"

namespace OF
{
    /**
     * @brief OpenFOAM网格生成
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-04
     */
    class FITKMeshGenOFAPI FITKMeshGenOFInterface :
        public AppFrame::FITKComponentInterface
    {
    public:
        /**
         * @brief Construct a new FITKMeshGenOFInterface object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        explicit FITKMeshGenOFInterface();
        /**
         * @brief Destroy the FITKMeshGenOFInterface object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        virtual ~FITKMeshGenOFInterface() = default;

        /**
        * @brief 获取部件名称，不能重复  return "FITKMeshGenOF"
        * @return QString
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-03-04
        */
        virtual QString getComponentName() override;

        /**
         * @brief 执行读取或写出
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-07
         */
        virtual bool exec(const int indexPort) override;

    };
}


#endif
