#include "FITKOFMeshIOAPI.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponentInterface.h"

namespace Interface {
    class FITKUnstructuredFluidMeshVTK;
}
namespace IO
{
    class FITKOFMeshIOAPI FITKOFMeshReader : public AppFrame::FITKComponentInterface
    {
    public:
        /**
         * @brief  构造函数
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-07-29
         */
        FITKOFMeshReader() = default;
        /**
         * @brief  析构函数
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-07-29
         */
        ~FITKOFMeshReader() = default;
        /**
         * @brief  获取组件名称
         * @return 组件名称
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-07-29
         */
        QString getComponentName() override;
        /**
         * @brief  执行组件
         * @return 执行结果
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-07-29
         */
        bool exec(const int indexPort) override;
        /**
         * @brief  设置网格文件所在路径
         * @param  folder 文件夹路径
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-07-29
         */
        void setMeshFolder(QString folder);
        /**
         * @brief  设置网格数据存放对象
         * @param  mesh 网格数据对象
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-07-29
         */
        void setMeshObj(Interface::FITKUnstructuredFluidMeshVTK* mesh);
    private:
        /**
         * @brief  网格文件所在路径
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-07-29
         */
        QString m_Folder{};
        /**
         * @brief  网格数据对象
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-07-29
         */
        Interface::FITKUnstructuredFluidMeshVTK* m_Mesh{};
    };

}