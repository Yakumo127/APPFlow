#include "FITKAssElement.h"
#include "FITKAbstractModel.h"
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"

namespace Interface
{
    //静态单元ID
    static int AssEleID = 0;
    FITKAbstractAssemblyElement::FITKAbstractAssemblyElement()
    {
        _elementID = ++AssEleID;
    }
    int FITKAbstractAssemblyElement::getElementID() const
    {
        return _elementID;
    }

    void FITKAbstractAssemblyElement::setElementID(const int id)
    {
        AssEleID = AssEleID > id ? AssEleID : id;
        _elementID = id;
    }

    /**
     * @brief 拷贝到目标单元
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-06-24
     */
    void FITKAbstractAssemblyElement::copyTo(FITKAbstractAssemblyElement*)
    {
    }

    FITKModelEnum::FITKModelSetType FITKAssemblyElementSet::getModelSetType()
    {
        return FITKModelEnum::FMSNone;
    }

    void FITKAssemblyElementVertex::copyTo(FITKAbstractAssemblyElement* e)
    {
        //类型转换
        FITKAssemblyElementVertex* v = dynamic_cast<FITKAssemblyElementVertex*>(e);
        if (v) return;
        //设置ID
        v->setModelID(_nodeModelID);
        v->setNodeID(_nodeID);
    }

    void FITKAssemblyElementVertex::setModelID(const int mid)
    {
        _nodeModelID = mid;
    }

    void FITKAssemblyElementVertex::setNodeID(const int id)
    {
        _nodeID = id;
    }

    void FITKAssemblyElementVertex::getCoor(double* coor)
    {
        //获取模型
        if (coor == nullptr) return;
        auto m = FITKDATAREPO->getTDataByID<FITKAbstractModel>(_nodeModelID);
        if (m == nullptr) return;
        //获取坐标
        m->getPointCoor(_nodeID, coor);
    }

    void FITKAssemblyElementVertex::getNode(int& mid, int& id)
    {
        mid = _nodeModelID;
        id = _nodeID;
    }

    void FITKAssemblyElementLine::copyTo(FITKAbstractAssemblyElement* e)
    {
        //类型转换
        FITKAssemblyElementLine* l = dynamic_cast<FITKAssemblyElementLine*>(e);
        if (l== nullptr) return;
        //设置节点
        l->setNode1(_node1.first, _node1.second);
        l->setNode2(_node2.first, _node2.second);
    }

    void FITKAssemblyElementLine::setNode1(const int mid, const int id)
    {
        _node1.first = mid;
        _node1.second = id;
    }

    void FITKAssemblyElementLine::setNode2(const int mid, const int id)
    {
        _node2.first = mid;
        _node2.second = id;
    }

    void FITKAssemblyElementLine::getNode1(int& mid, int& id)
    {
        mid = _node1.first;
        id = _node1.second;
    }

    void FITKAssemblyElementLine::getNode2(int& mid, int& id)
    {
        mid = _node2.first;
        id = _node2.second;
    }

    void FITKAssemblyElementLine::getCoor1(double* coor1)
    {
        //模型
        if (coor1 == nullptr) return;
        auto m = FITKDATAREPO->getTDataByID<FITKAbstractModel>(_node1.first);
        if (m == nullptr) return;
        //获取坐标
        m->getPointCoor(_node1.second, coor1);
    }

    void FITKAssemblyElementLine::getCoor2(double* coor2)
    {
        //模型
        if (coor2 == nullptr) return;
        auto m = FITKDATAREPO->getTDataByID<FITKAbstractModel>(_node2.first);
        if (m == nullptr) return;
        //坐标
        m->getPointCoor(_node2.second, coor2);
    }

    QString FITKAssemblyElementLine::getTextLabel1()
    {
        //模型
        auto m = FITKDATAREPO->getTDataByID<FITKAbstractModel>(_node1.first);
        if (m == nullptr) return QString();
        if (m->getAbsModelType() == FITKModelEnum::AbsModelType::Assembly)
            return QString("Node[%1]").arg(_node1.second);
        //组合名称
        return QString("%1 Node[%2]").arg(m->getDataObjectName()).arg(_node1.second);
    }

    QString FITKAssemblyElementLine::getTextLabel2()
    {
        //模型
        auto m = FITKDATAREPO->getTDataByID<FITKAbstractModel>(_node2.first);
        if (m == nullptr) return QString();
        if (m->getAbsModelType() == FITKModelEnum::AbsModelType::Assembly)
            return QString("Node[%1]").arg(_node1.second);
        //组合名称
        return QString("%1 Node[%2]").arg(m->getDataObjectName()).arg(_node2.second);
    }

    void FITKAssemblyElementLine::swap()
    {
        QPair<int, int> t = _node1;
        _node1 = _node2;
        _node2 = t;
    }

}



