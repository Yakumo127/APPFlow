#include "FITKOCCModelSolid.h"
#include <gp_Pnt.hxx>
#include <gp_Pln.hxx>
#include <gp_Dir.hxx>
#include <TopoDS.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Precision.hxx>
#include <BRepBndLib.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <ProjLib.hxx>
#include <gp_Pnt2d.hxx>
#include <Bnd_Box2d.hxx>
#include <ShapeAnalysis.hxx>

#include <FITK_Interface/FITKInterfaceGeometry/FITKGeoEnum.h>
#include <FITK_Interface/FITKInterfaceGeometry/FITKVirtualTopoManager.h>
#include "FITKOCCVirtualTopoCreator.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoInterfaceFactory.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSurface.h"

#include <FITKOCCModelCurve.h>
#include <QSet>
#include <QDebug>

namespace {
    /**
     * @brief  代表草绘图中每个封闭的曲线.
     * @author YanZhiHui(chanyuantiandao@126.com)
     * @date   2024-09-29
     */
    struct CWire {
        /// 包围盒
        Bnd_Box Bound;
        /// TopoDS_Wire
        BRepBuilderAPI_MakeWire MakeWire{};
        /// 起点
        gp_Pnt Start{};
        /// 终点
        gp_Pnt End{};
        /// 封闭曲线的点
        QList<gp_Pnt> Pnts{};
        /**
         * @brief  连接新的边.
         * @param  edge 新边
         * @return 如果成功连接，返回true，否则返回false
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        bool connect(const TopoDS_Edge& edge) {
            Standard_Real first;
            Standard_Real last;
            Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
            gp_Pnt p1 = curve->Value(first);
            gp_Pnt p2 = curve->Value(last);
            // 空线段直接添加
            if (!MakeWire.IsDone() || MakeWire.Shape().IsNull()) {
                Start = p1;
                End = p2;
                Pnts.append(p1);
                Pnts.append(p2);
                MakeWire.Add(edge);
                return true;
            }
            // Start与p1重合
            if (Start.Distance(p1) <= Precision::Confusion()) {
                MakeWire.Add(edge);
                Pnts.append(p2);
                Start = p2;
                return true;
            }
            // Start与p2重合
            if (Start.Distance(p2) <= Precision::Confusion()) {
                MakeWire.Add(edge);
                Pnts.append(p1);
                Start = p1;
                return true;
            }
            // End与p1重合
            if (End.Distance(p1) <= Precision::Confusion()) {
                MakeWire.Add(edge);
                Pnts.append(p2);
                End = p2;
                return true;
            }
            // End与p2重合
            if (End.Distance(p2) <= Precision::Confusion()) {
                MakeWire.Add(edge);
                Pnts.append(p1);
                End = p1;
                return true;
            }
            return false;
        }
        /**
         * @brief  是否包含某边.
         * @param  edge 边
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        bool contain(const TopoDS_Edge& edge) {
            for (TopoDS_Iterator iter(MakeWire.Shape()); iter.More(); iter.Next()) {
                if (iter.Value().IsSame(edge)) return true;
            }
            return false;
        }
        /**
         * @brief  当前wire是否为空.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        bool isNull() { return MakeWire.Edge().IsNull(); }
        /**
         * @brief  当前wire是否闭合.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        bool isClosed() { return MakeWire.Shape().Closed(); }
    };
    /**
     * @brief  一组共点的边.
     * @author YanZhiHui(chanyuantiandao@126.com)
     * @date   2024-09-29
     */
    struct EdgePair {
        /// 共点
        gp_Pnt Pnt{};
        /// 共点的边，size必须是2，否则会出现交叉或者未封闭的图形
        QList<TopoDS_Edge> Edges{};
        /**
         * @brief  是否为空.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        bool isNull() { return Edges.size() == 0; }
        /**
         * @brief  判断共点边是否相同.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        friend bool operator ==(const EdgePair &, const EdgePair &) noexcept;
    };
    /**
     * @brief  判断共点边是否相同.
     * @author YanZhiHui(chanyuantiandao@126.com)
     * @date   2024-09-29
     */
    inline bool operator==(const EdgePair &first, const EdgePair &second) noexcept
    {
        return first.Pnt.Distance(second.Pnt) <= Precision::Confusion();
    }
    /**
     * @brief  共点边的组.
     * @author YanZhiHui(chanyuantiandao@126.com)
     * @date   2024-09-29
     */
    struct EdgeGroup {
        /// 共点边列表
        QList<EdgePair> Groups{};
        /**
         * @brief  以点为条件添加边.
         * @param  p 点
         * @param  e 边
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        void add(const gp_Pnt& p, const TopoDS_Edge& e) {
            // 如果已经存在该点的共点边，则添加到已有共点边
            for (auto& g : Groups) {
                if (g.Pnt.Distance(p) <= Precision::Confusion()) {
                    g.Edges.append(e);
                    return;
                }
            }
            // 否则创建新的共点边
            EdgePair ep;
            ep.Pnt = p;
            ep.Edges = { e };
            Groups.append(ep);
        }
        /**
         * @brief  移除某点处的共点边并返回删除对象.
         * @param  p 点
         * @return 返回删除的对象（可能为空isNull() == true）
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        EdgePair removeByPnt(const gp_Pnt& p) {
            EdgePair ret;
            for (auto g : Groups) {
                if (g.Pnt.Distance(p) <= Precision::Confusion()) {
                    ret = g;
                    Groups.removeOne(g);
                    break;
                }
            }
            return ret;
        }
        /**
         * @brief  移除某边所在的共点边并返回删除对象.
         * @param  e 要移除的边
         * @return 返回删除的对象（可能为空isNull() == true）
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        EdgePair removeByEdge(const TopoDS_Edge& e) {
            EdgePair ret;
            for (auto g : Groups) {
                for (auto edge : g.Edges) {
                    if (edge.IsSame(e))
                    {
                        ret = g;
                        Groups.removeOne(g);
                        break;
                    }
                }
            }
            return ret;
        }

    };
    /**
     * @brief  包围盒树结构的节点类.
     * @author YanZhiHui(chanyuantiandao@126.com)
     * @date   2024-09-29
     */
    class WireBoundTreeNode {
    public:
        /// 构造函数
        WireBoundTreeNode(const CWire& cw) : m_Data(cw) {}
        /// 析构函数
        ~WireBoundTreeNode() = default;
        /**
         * @brief  返回节点数据CWire.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        CWire& data() { return m_Data; }
        /**
         * @brief  返回当前节点的父节点.
         * @return 父节点，根节点返回空指针nullptr
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        WireBoundTreeNode* parent() { return m_Parent; }
        /**
         * @brief  是否有子节点.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        bool hasChild() { return m_Childs.size() > 0; }
        /**
         * @brief  返回所有子节点列表.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        QList<WireBoundTreeNode*>& childs() { return m_Childs; }
        /**
         * @brief  返回节点数据CWire的包围盒.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        Bnd_Box bnd() const { return m_Data.Bound; }
        /**
         * @brief  重新设置当前节点的父节点.
         * @param  n 新的父节点(n==nullptr代表根节点)
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        void setParent(WireBoundTreeNode* n) {
            if (n == m_Parent) return;
            // 移除原有的父级关系
            if (m_Parent != nullptr) {
                m_Parent->m_Childs.removeAll(this);
            }
            // 设置新的父子关系
            m_Parent = n;
            if (n != nullptr) {
                n->m_Childs.append(this);
            }
        }

    private:
        /// 节点数据
        CWire m_Data{};
        /// 节点父节点
        WireBoundTreeNode* m_Parent{};
        /// 节点子节点列表
        QList<WireBoundTreeNode*> m_Childs{};
    };
    /**
     * @brief  判断草图包围盒的包含关系.
     * @param  box1 包围盒1
     * @param  box2 包围盒2
     * @note   此处不能用OCC提供的IsOut代替，不符合草图包围的情况会抛异常由调用函数捕捉
     * @author YanZhiHui(chanyuantiandao@126.com)
     * @date   2024-09-29
     */
    bool isOut(const Bnd_Box& box1, const Bnd_Box& box2) {
        // 草图包围盒不能为空
        if (box1.IsVoid() || box2.IsVoid()) throw "System Error!";

        Standard_Real xMin1, xMax1, yMin1, yMax1, zMin1, zMax1;
        Standard_Real xMin2, xMax2, yMin2, yMax2, zMin2, zMax2;
        box1.Get(xMin1, yMin1, zMin1, xMax1, yMax1, zMax1);
        box2.Get(xMin2, yMin2, zMin2, xMax2, yMax2, zMax2);

        // XOY平面
        if (box1.IsZThin(box1.GetGap()) && box2.IsZThin(box2.GetGap())) {
            return (yMin1 < yMin2) && (xMin1 < xMin2) && (yMax1 > yMax2) && (xMax1 > xMax2);
        }
        // YOZ平面
        else if (box1.IsXThin(box1.GetGap()) && box2.IsXThin(box2.GetGap())) {
            return (yMin1 < yMin2) && (zMin1 < zMin2) && (yMax1 > yMax2) && (zMax1 > zMax2);
        }
        // XOZ平面
        else if (box1.IsYThin(box1.GetGap()) && box2.IsYThin(box2.GetGap())) {
            return (xMin1 < xMin2) && (zMin1 < zMin2) && (xMax1 > xMax2) && (zMax1 > zMax2);
        }
        // 普通平面
        else if (!box2.IsOpen()) {
            return (xMin1 < xMin1) && (yMin1 < yMin2) && (zMin1 < zMin2)
                && (xMax1 > xMax2) && (yMax1 > yMax2) && (zMax1 > zMax2);
        }
        else {
            throw "System Error!";
        }
    }
    /**
     * @brief  包围盒树结构类.
     * @author YanZhiHui(chanyuantiandao@126.com)
     * @date   2024-09-29
     */
    class WireBoundTree {
    public:
        /// 构造函数
        WireBoundTree() = default;
        /// 析构函数
        ~WireBoundTree() = default;
        /**
         * @brief  返回根节点列表.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        QSet<WireBoundTreeNode*> roots() { return m_Roots; }
        /**
         * @brief  添加CWire.
         * @param  w CWire
         * @note   该函数负责把CWire放在树结构中合适的位置
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        void addWire(const CWire& w) {
            auto newNode = new WireBoundTreeNode(w);
            // 如果根节点为空，则添加到根节点列表
            if (m_Roots.isEmpty()) { m_Roots.insert(newNode); return; }

            bool isContain = false;

            const auto oldRoots = m_Roots;
            for (WireBoundTreeNode* node : oldRoots) {
                // 新节点包含node
                if (isOut(newNode->bnd(), node->bnd())) {
                    node->setParent(newNode);
                    m_Roots.remove(node);
                    m_Roots.insert(newNode);
                    isContain = true;
                }
                // node包含新节点
                else if (isOut(node->bnd(), newNode->bnd())) {
                    if (!node->hasChild()) { newNode->setParent(node); }
                    else {
                        addChildNode(newNode, node);
                    }
                    isContain = true;
                    return;
                }
            }
            // 并列关系
            if (!isContain) {
                m_Roots.insert(newNode);
            }
        }

    protected:
        /**
         * @brief  比较新节点与子节点的关系，并设置合适的位置.
         * @param  newNode 新节点
         * @param  toNode 子节点
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        void addChildNode(WireBoundTreeNode* newNode, WireBoundTreeNode* toNode) {
            if (newNode == nullptr || toNode == nullptr) return;

            bool isContain = false;
            for (auto& node : toNode->childs()) {
                if (isOut(node->bnd(), newNode->bnd())) {
                    addChildNode(newNode, node);
                    isContain = true;
                    return;
                }
                else if (isOut(newNode->bnd(), node->bnd())) {
                    node->setParent(newNode);
                    newNode->setParent(toNode);
                    isContain = true;
                }
            }
            // 并列关系
            if (!isContain) {
                newNode->setParent(toNode);
            }
        }


    private:
        /**
         * @brief  根节点列表（最外围的草绘并列存在多个，因此根节点需要使用列表）.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-09-29
         */
        QSet<WireBoundTreeNode*> m_Roots{};
    };

}

namespace OCC
{
    FITKOCCModelClosedSurfaceSolid::FITKOCCModelClosedSurfaceSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelClosedSurfaceSolid::update()
    {
        if (m_Faces.isEmpty()) return false;

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        BRepBuilderAPI_Sewing sewing;

        for (int i = 0; i < m_Faces.size(); ++i) {
            auto face = m_Faces.at(i);
            if (face.isNull()) continue;

            auto cmd = geoCmdList->getDataByID(face.CmdId);
            if (cmd == nullptr)
            {
                printLog(tr("Failed to get geometry command."), 3);
                return false;
            }
            auto vshape = cmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSFace, face.VirtualTopoId);
            if (vshape == nullptr)
            {
                printLog(tr("Failed to get face from virtual topo."), 3);
                return false;
            }
            auto topoShape = vshape->getTopoShape();
            if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_FACE) {
                TopoDS_Face f = TopoDS::Face(topoShape);
                if (f.IsNull()) continue;
                if (f.Orientation() == TopAbs_Orientation::TopAbs_REVERSED) {
                    f.Reverse();
                }
                sewing.Add(f);
            }
            else {
                printLog(tr("Error topo shape type for make wire."), 3);
                return false;
            }
        }
        sewing.Perform();

        auto type = sewing.SewedShape().ShapeType();

        /*if (type == TopAbs_COMPOUND)
        {
            TopoDS_Builder aShellBuilder;
            TopoDS_Shell aShell;

            aShellBuilder.MakeShell(aShell);

            int faceCount = 0;
            int edgeCount = 0;

            for (TopoDS_Iterator anExp(sewing.SewedShape()); anExp.More(); anExp.Next())
            {
                const TopoDS_Shape &curShape1 = anExp.Value();
                TopAbs_ShapeEnum type1 = curShape1.ShapeType();

                if (type1 == TopAbs_SHELL)
                {
                    for (TopExp_Explorer anExp(curShape1, TopAbs_FACE); anExp.More(); anExp.Next())
                    {
                        const TopoDS_Shape &curShape2 = anExp.Current();
                        aShellBuilder.Add(aShell, curShape2);
                        faceCount++;
                    }
                }
            }
        }*/

        if (type != TopAbs_SHELL)
        {
            printLog(tr("Error topo shape type for make wire."), 3);
            return false;
        }
        try {
            TopoDS_Shell shell = TopoDS::Shell(sewing.SewedShape());
            if (shell.IsNull() || !shell.Closed()) {
                printLog(tr("Must be closed shell."), 3);
                return false;
            }
            BRepBuilderAPI_MakeSolid solid(shell);

            if (!solid.IsDone()) {
                printLog(tr("Error topo shape type for make wire."), 3);
                return false;
            }
            _occShapeAgent->updateShape(solid.Shape());
        }
        catch (...)
        {
            printLog(tr("Failed to make solid!"), 3);
            return false;
        }
        return true;
    }
    FITKOCCModelExtrudeSolid::FITKOCCModelExtrudeSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelExtrudeSolid::update()
    {

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        auto cmd = geoCmdList->getDataByID(m_SourceSurface.CmdId);
        if (cmd == nullptr) return false;

        Interface::FITKGeoEnum::VTopoShapeType type = cmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSFace;

        auto shape = cmd->getShapeT<FITKOCCTopoShape>(type, m_SourceSurface.VirtualTopoId);
        if (shape == nullptr) return false;

        auto topoShape = shape->getTopoShape();
        gp_Vec dir(m_Direction[0], m_Direction[1], m_Direction[2]);
        auto mag = dir.Magnitude();
        if (mag <= Precision::Confusion()) {
            printLog(tr("The direction cannot be a zero vector!"), 3);
            return false;
        }
        dir = dir * m_Length / mag;

        try {
            // 如果是草绘则返回的是线的组合体，需要合并面
            if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND)
            {
                TopoDS_Compound sketchCompound = TopoDS::Compound(topoShape);
                TopExp_Explorer exp(sketchCompound, TopAbs_ShapeEnum::TopAbs_EDGE);

                QList<CWire> wiresList{};

                /* 按连接点分组 */
                /* @{ */
                EdgeGroup edgeGroup{};

                for (; exp.More(); exp.Next()) {
                    if (exp.Current().ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE) continue;
                    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                    if (edge.IsNull()) continue;
                    if (edge.Orientation() == TopAbs_Orientation::TopAbs_FORWARD)
                        edge.Reverse();
                    // 获取顶点
                    Standard_Real first;
                    Standard_Real last;
                    Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
                    gp_Pnt start = curve->Value(first);
                    gp_Pnt end = curve->Value(last);
                    /* 自成封闭的曲线 */
                    /* @{ */
                    if (start.Distance(end) < Precision::Confusion()) {
                        CWire w;
                        w.MakeWire.Add(edge);
                        w.Start = start;
                        w.End = end;
                        wiresList.push_back(w);
                        continue;
                    }
                    /* @} */
                    // 添加分组
                    edgeGroup.add(start, edge);
                    edgeGroup.add(end, edge);
                }
                /* @} */

                /* 如果边组不为空，则从第一个开始寻找闭合曲线 */
                /* @{ */
                while (edgeGroup.Groups.size() != 0)
                {
                    int s = edgeGroup.Groups.size();
                    CWire w;
                    auto grp = edgeGroup.Groups.at(0);
                    edgeGroup.Groups.removeOne(grp);
                    s = edgeGroup.Groups.size();

                    if (grp.Edges.size() != 2) {
                        printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                        return false;
                    }
                    //  空的cwire直接添加两条边
                    if (w.isNull()) {
                        if (!w.connect(grp.Edges.at(0)) || !w.connect(grp.Edges.at(1))) {
                            printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                            return false;
                        }
                    }

                    // 如果没闭合，则递归寻找下一段
                    while (!w.isClosed())
                    {
                        auto edgePair = edgeGroup.removeByPnt(w.End);
                        s = edgeGroup.Groups.size();
                        if (edgePair.isNull()) {
                            printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                            return false;
                        }

                        if (w.contain(edgePair.Edges.at(0))) {
                            w.connect(edgePair.Edges.at(1));
                        }
                        else {
                            w.connect(edgePair.Edges.at(0));
                        }
                    }
                    // 移除重复对象
                    for (gp_Pnt p : w.Pnts) {
                        edgeGroup.removeByPnt(p);
                    }

                    s = edgeGroup.Groups.size();
                    // 将闭合曲线添加到列表
                    wiresList.append(w);

                }
                /* @} */

                // 检测封闭性，计算包围盒
                Interface::FITKAbsGeoSketch2D* sketchCmd = dynamic_cast<Interface::FITKAbsGeoSketch2D*>(cmd);
                double pCenter[3], pDir[3];
                sketchCmd->getPosition(pCenter);
                sketchCmd->getNormal(pDir);

                gp_Pln sketchPln(gp_Pnt(pCenter[0], pCenter[1], pCenter[2]), gp_Dir(pDir[0], pDir[1], pDir[2]));
                for (auto& wire : wiresList) {
                    if (!wire.isClosed()) {
                        printLog(tr("The selected sketch contains several open profile."), 3);
                        return false;
                    }
                    else {
                        BRepBndLib::Add(wire.MakeWire.Shape(), wire.Bound);
                    }
                }

                /* 按包围盒大小生成树形包围结构 */
                /* @{ */
                if (wiresList.size() == 0) return false;
                WireBoundTree tree;
                for (int i = 0; i < wiresList.size(); ++i) {
                    tree.addWire(wiresList.at(i));
                }
                /* @} */

                // 初始化组合对象。
                BRep_Builder builder;
                TopoDS_Compound compoundSolid;
                builder.MakeCompound(compoundSolid);

                auto outNodes = tree.roots();
                while (!outNodes.isEmpty())
                {
                    QSet<WireBoundTreeNode*> nextOutNodes{};
                    for (WireBoundTreeNode* node : outNodes) {
                        // 外围轮廓
                        auto wire = node->data();
                        BRepBuilderAPI_MakeFace face;
                        if (wire.MakeWire.Shape().Orientation() == TopAbs_Orientation::TopAbs_REVERSED) {
                            face = BRepBuilderAPI_MakeFace(TopoDS::Wire(wire.MakeWire.Shape().Reversed()), true);
                        }
                        else {
                            face = BRepBuilderAPI_MakeFace(wire.MakeWire, true);
                        }
                        // 内部轮廓
                        if (node->hasChild()) {
                            for (WireBoundTreeNode* node : node->childs()) {
                                CWire cwire = node->data();
                                TopoDS_Shape innerShape = cwire.MakeWire.Shape();
                                if (innerShape.ShapeType() != TopAbs_WIRE) return false;
                                TopoDS_Wire innerWire = TopoDS::Wire(innerShape);
                                if (innerWire.IsNull()) return false;
                                if (innerWire.Orientation() == TopAbs_Orientation::TopAbs_FORWARD)
                                    innerWire.Reverse();
                                face.Add(innerWire);

                                for (auto n : node->childs()) {
                                    nextOutNodes.insert(n);
                                }
                            }
                        }
                        face.Build();
                        if (!face.IsDone()) return false;
                        builder.Add(compoundSolid, BRepPrimAPI_MakePrism(face, dir).Shape());
                    }
                    outNodes = nextOutNodes;
                }

                _occShapeAgent->updateShape(compoundSolid);
            }
            else {
                _occShapeAgent->updateShape(BRepPrimAPI_MakePrism(topoShape, dir).Shape());
            }
        }
        catch (...)
        {
            printLog(tr("Failed to make solid!"), 3);
            return false;
        }
        return true;
    }
    FITKOCCModelRevolSolid::FITKOCCModelRevolSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelRevolSolid::update()
    {
        gp_Pnt start(m_RotateAxisPoint1[0], m_RotateAxisPoint1[1], m_RotateAxisPoint1[2]);
        gp_Pnt end(m_RotateAxisPoint2[0], m_RotateAxisPoint2[1], m_RotateAxisPoint2[2]);
        if (start.Distance(end) <= Precision::Confusion()) {
            printLog(tr("The two ends of the axis of rotation can not coincide!"), 3);
            return false;
        }

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        auto cmd = geoCmdList->getDataByID(m_SourceSurface.CmdId);
        if (cmd == nullptr) return false;

        Interface::FITKGeoEnum::VTopoShapeType type = cmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSFace;

        auto vshape = cmd->getShapeT<FITKOCCTopoShape>(type, m_SourceSurface.VirtualTopoId);
        if (vshape == nullptr) return false;
        auto topoShape = vshape->getTopoShape();
        //m_OriginId;
        gp_Ax1 ax1(start, gp_Dir(end.XYZ() - start.XYZ()));
        try {
            // 如果是草绘则返回的是线的组合体，需要合并面
            if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND)
            {
                TopoDS_Compound sketchCompound = TopoDS::Compound(topoShape);
                TopExp_Explorer exp(sketchCompound, TopAbs_ShapeEnum::TopAbs_EDGE);

                QList<CWire> wiresList{};

                /* 按连接点分组 */
                /* @{ */
                EdgeGroup edgeGroup{};

                for (; exp.More(); exp.Next()) {
                    if (exp.Current().ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE) continue;
                    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                    if (edge.IsNull()) continue;
                    if (edge.Orientation() == TopAbs_Orientation::TopAbs_FORWARD)
                        edge.Reverse();
                    // 获取顶点
                    Standard_Real first;
                    Standard_Real last;
                    Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
                    gp_Pnt start = curve->Value(first);
                    gp_Pnt end = curve->Value(last);
                    /* 自成封闭的曲线 */
                    /* @{ */
                    if (start.Distance(end) < Precision::Confusion()) {
                        CWire w;
                        w.MakeWire.Add(edge);
                        w.Start = start;
                        w.End = end;
                        wiresList.push_back(w);
                        continue;
                    }
                    /* @} */
                    // 添加分组
                    edgeGroup.add(start, edge);
                    edgeGroup.add(end, edge);
                }
                /* @} */

                /* 如果边组不为空，则从第一个开始寻找闭合曲线 */
                /* @{ */
                while (edgeGroup.Groups.size() != 0)
                {
                    int s = edgeGroup.Groups.size();
                    CWire w;
                    auto grp = edgeGroup.Groups.at(0);
                    edgeGroup.Groups.removeOne(grp);
                    s = edgeGroup.Groups.size();

                    if (grp.Edges.size() != 2) {
                        printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                        return false;
                    }
                    //  空的cwire直接添加两条边
                    if (w.isNull()) {
                        if (!w.connect(grp.Edges.at(0)) || !w.connect(grp.Edges.at(1))) {
                            printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                            return false;
                        }
                    }

                    // 如果没闭合，则递归寻找下一段
                    while (!w.isClosed())
                    {
                        auto edgePair = edgeGroup.removeByPnt(w.End);
                        s = edgeGroup.Groups.size();
                        if (edgePair.isNull()) {
                            printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                            return false;
                        }

                        if (w.contain(edgePair.Edges.at(0))) {
                            w.connect(edgePair.Edges.at(1));
                        }
                        else {
                            w.connect(edgePair.Edges.at(0));
                        }
                    }
                    // 移除重复对象
                    for (gp_Pnt p : w.Pnts) {
                        edgeGroup.removeByPnt(p);
                    }

                    s = edgeGroup.Groups.size();
                    // 将闭合曲线添加到列表
                    wiresList.append(w);

                }
                /* @} */

                // 检测封闭性，计算包围盒
                Interface::FITKAbsGeoSketch2D* sketchCmd = dynamic_cast<Interface::FITKAbsGeoSketch2D*>(cmd);
                double pCenter[3], pDir[3];
                sketchCmd->getPosition(pCenter);
                sketchCmd->getNormal(pDir);

                gp_Pln sketchPln(gp_Pnt(pCenter[0], pCenter[1], pCenter[2]), gp_Dir(pDir[0], pDir[1], pDir[2]));
                for (auto& wire : wiresList) {
                    if (!wire.isClosed()) {
                        printLog(tr("The selected sketch contains several open profile."), 3);
                        return false;
                    }
                    else {
                        BRepBndLib::Add(wire.MakeWire.Shape(), wire.Bound);
                    }
                }

                /* 按包围盒大小生成树形包围结构 */
                /* @{ */
                if (wiresList.size() == 0) return false;
                WireBoundTree tree;
                for (int i = 0; i < wiresList.size(); ++i) {
                    tree.addWire(wiresList.at(i));
                }
                /* @} */

                // 初始化组合对象。
                BRep_Builder builder;
                TopoDS_Compound compoundSolid;
                builder.MakeCompound(compoundSolid);

                auto outNodes = tree.roots();
                while (!outNodes.isEmpty())
                {
                    QSet<WireBoundTreeNode*> nextOutNodes{};
                    for (WireBoundTreeNode* node : outNodes) {
                        // 外围轮廓
                        auto wire = node->data();
                        BRepBuilderAPI_MakeFace face;
                        if (wire.MakeWire.Shape().Orientation() == TopAbs_Orientation::TopAbs_REVERSED) {
                            face = BRepBuilderAPI_MakeFace(TopoDS::Wire(wire.MakeWire.Shape().Reversed()), true);
                        }
                        else {
                            face = BRepBuilderAPI_MakeFace(wire.MakeWire, true);
                        }
                        // 内部轮廓
                        if (node->hasChild()) {
                            for (WireBoundTreeNode* node : node->childs()) {
                                CWire cwire = node->data();
                                TopoDS_Shape innerShape = cwire.MakeWire.Shape();
                                if (innerShape.ShapeType() != TopAbs_WIRE) return false;
                                TopoDS_Wire innerWire = TopoDS::Wire(innerShape);
                                if (innerWire.IsNull()) return false;
                                if (innerWire.Orientation() == TopAbs_Orientation::TopAbs_FORWARD)
                                    innerWire.Reverse();
                                face.Add(innerWire);

                                for (auto n : node->childs()) {
                                    nextOutNodes.insert(n);
                                }
                            }
                        }
                        face.Build();
                        if (!face.IsDone()) return false;
                        builder.Add(compoundSolid, BRepPrimAPI_MakeRevol(face, ax1, m_Angle * M_PI / 180).Shape());
                    }
                    outNodes = nextOutNodes;
                }

                _occShapeAgent->updateShape(compoundSolid);
            }
            else {
                _occShapeAgent->updateShape(BRepPrimAPI_MakeRevol(topoShape, ax1, m_Angle  * M_PI / 180).Shape());
            }
        }
        catch (...)
        {
            printLog(tr("Failed to make solid!"), 3);
            return false;
        }
        return true;
    }
    FITKOCCModelSweepSolid::FITKOCCModelSweepSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelSweepSolid::update()
    {
        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        auto profileCmd = geoCmdList->getDataByID(m_Profile.CmdId);
        auto curveCmd = geoCmdList->getDataByID(m_Curve.CmdId);
        if (profileCmd == nullptr || curveCmd == nullptr) return false;

        Interface::FITKGeoEnum::VTopoShapeType profileType = profileCmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSFace;
        auto profileShape = profileCmd->getShapeT<FITKOCCTopoShape>(profileType, m_Profile.VirtualTopoId);

        Interface::FITKGeoEnum::VTopoShapeType curveType = curveCmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSEdge;
        auto curveShape = curveCmd->getShapeT<FITKOCCTopoShape>(curveType, m_Curve.VirtualTopoId);
        if (profileShape == nullptr || curveShape == nullptr) return false;

        auto profileTopoShape = profileShape->getTopoShape();
        auto curveTopoShape = curveShape->getTopoShape();

        try {
            /* 分析扫略线 */
            /*@{*/
            TopoDS_Wire sweepWire;
            auto type = curveTopoShape.ShapeType();
            if (type == TopAbs_ShapeEnum::TopAbs_WIRE)
            {
                sweepWire = TopoDS::Wire(curveTopoShape);
            }
            else if (type == TopAbs_ShapeEnum::TopAbs_EDGE) {
                sweepWire = BRepBuilderAPI_MakeWire(TopoDS::Edge(curveTopoShape));
            }
            else if (type == TopAbs_ShapeEnum::TopAbs_COMPOUND) {
                TopoDS_Compound compound = TopoDS::Compound(curveTopoShape);
                TopExp_Explorer exp;
                BRepBuilderAPI_MakeWire makeWire;
                for (exp.Init(compound, TopAbs_EDGE); exp.More(); exp.Next())
                {
                    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                    if (edge.IsNull()) continue;
                    makeWire.Add(edge);
                }
                makeWire.Build();
                if (!makeWire.IsDone()) return false;
                sweepWire = TopoDS::Wire(makeWire.Shape());
            }
            else return false;
            /*@}*/


            // 如果是草绘则返回的是线的组合体，需要合并面
            if (profileTopoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND)
            {
                TopoDS_Compound sketchCompound = TopoDS::Compound(profileTopoShape);
                TopExp_Explorer exp(sketchCompound, TopAbs_ShapeEnum::TopAbs_EDGE);

                QList<CWire> wiresList{};

                /* 按连接点分组 */
                /* @{ */
                EdgeGroup edgeGroup{};

                for (; exp.More(); exp.Next()) {
                    if (exp.Current().ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE) continue;
                    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                    if (edge.IsNull()) continue;
                    if (edge.Orientation() == TopAbs_Orientation::TopAbs_FORWARD)
                        edge.Reverse();
                    // 获取顶点
                    Standard_Real first;
                    Standard_Real last;
                    Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
                    gp_Pnt start = curve->Value(first);
                    gp_Pnt end = curve->Value(last);
                    /* 自成封闭的曲线 */
                    /* @{ */
                    if (start.Distance(end) < Precision::Confusion()) {
                        CWire w;
                        w.MakeWire.Add(edge);
                        w.Start = start;
                        w.End = end;
                        wiresList.push_back(w);
                        continue;
                    }
                    /* @} */
                    // 添加分组
                    edgeGroup.add(start, edge);
                    edgeGroup.add(end, edge);
                }
                /* @} */

                /* 如果边组不为空，则从第一个开始寻找闭合曲线 */
                /* @{ */
                while (edgeGroup.Groups.size() != 0)
                {
                    int s = edgeGroup.Groups.size();
                    CWire w;
                    auto grp = edgeGroup.Groups.at(0);
                    edgeGroup.Groups.removeOne(grp);
                    s = edgeGroup.Groups.size();

                    if (grp.Edges.size() != 2) {
                        printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                        return false;
                    }
                    //  空的cwire直接添加两条边
                    if (w.isNull()) {
                        if (!w.connect(grp.Edges.at(0)) || !w.connect(grp.Edges.at(1))) {
                            printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                            return false;
                        }
                    }

                    // 如果没闭合，则递归寻找下一段
                    while (!w.isClosed())
                    {
                        auto edgePair = edgeGroup.removeByPnt(w.End);
                        s = edgeGroup.Groups.size();
                        if (edgePair.isNull()) {
                            printLog(tr("The specified profile contains several open contours or some geometry used for construction."), 3);
                            return false;
                        }

                        if (w.contain(edgePair.Edges.at(0))) {
                            w.connect(edgePair.Edges.at(1));
                        }
                        else {
                            w.connect(edgePair.Edges.at(0));
                        }
                    }
                    // 移除重复对象
                    for (gp_Pnt p : w.Pnts) {
                        edgeGroup.removeByPnt(p);
                    }

                    s = edgeGroup.Groups.size();
                    // 将闭合曲线添加到列表
                    wiresList.append(w);

                }
                /* @} */

                // 检测封闭性，计算包围盒
                Interface::FITKAbsGeoSketch2D* sketchCmd = dynamic_cast<Interface::FITKAbsGeoSketch2D*>(profileCmd);
                double pCenter[3], pDir[3];
                sketchCmd->getPosition(pCenter);
                sketchCmd->getNormal(pDir);

                gp_Pln sketchPln(gp_Pnt(pCenter[0], pCenter[1], pCenter[2]), gp_Dir(pDir[0], pDir[1], pDir[2]));
                for (auto& wire : wiresList) {
                    if (!wire.isClosed()) {
                        printLog(tr("The selected sketch contains several open profile."), 3);
                        return false;
                    }
                    else {
                        BRepBndLib::Add(wire.MakeWire.Shape(), wire.Bound);
                    }
                }

                /* 按包围盒大小生成树形包围结构 */
                /* @{ */
                if (wiresList.size() == 0) return false;
                WireBoundTree tree;
                for (int i = 0; i < wiresList.size(); ++i) {
                    tree.addWire(wiresList.at(i));
                }
                /* @} */

                // 初始化组合对象。
                BRep_Builder builder;
                TopoDS_Compound compoundSolid;
                builder.MakeCompound(compoundSolid);

                auto outNodes = tree.roots();
                while (!outNodes.isEmpty())
                {
                    QSet<WireBoundTreeNode*> nextOutNodes{};
                    for (WireBoundTreeNode* node : outNodes) {
                        // 外围轮廓
                        auto wire = node->data();
                        BRepBuilderAPI_MakeFace face;
                        if (wire.MakeWire.Shape().Orientation() == TopAbs_Orientation::TopAbs_REVERSED) {
                            face = BRepBuilderAPI_MakeFace(TopoDS::Wire(wire.MakeWire.Shape().Reversed()), true);
                        }
                        else {
                            face = BRepBuilderAPI_MakeFace(wire.MakeWire, true);
                        }
                        // 内部轮廓
                        if (node->hasChild()) {
                            for (WireBoundTreeNode* node : node->childs()) {
                                CWire cwire = node->data();
                                TopoDS_Shape innerShape = cwire.MakeWire.Shape();
                                if (innerShape.ShapeType() != TopAbs_WIRE) return false;
                                TopoDS_Wire innerWire = TopoDS::Wire(innerShape);
                                if (innerWire.IsNull()) return false;
                                if (innerWire.Orientation() == TopAbs_Orientation::TopAbs_FORWARD)
                                    innerWire.Reverse();
                                face.Add(innerWire);

                                for (auto n : node->childs()) {
                                    nextOutNodes.insert(n);
                                }
                            }
                        }
                        face.Build();
                        if (!face.IsDone()) return false;
                        builder.Add(compoundSolid, BRepOffsetAPI_MakePipe(sweepWire, face).Shape());
                    }
                    outNodes = nextOutNodes;
                }

                _occShapeAgent->updateShape(compoundSolid);
            }
            else {
                BRepOffsetAPI_MakePipe pipe(sweepWire, profileTopoShape);
                pipe.Build();
                if (!pipe.IsDone()) return false;
                _occShapeAgent->updateShape(pipe.Shape());
            }
            return true;
        }
        catch (...)
        {
            printLog(tr("Failed to make solid!"), 3);
            return false;
        }
    }
    FITKOCCModelMultiSectionSolid::FITKOCCModelMultiSectionSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelMultiSectionSolid::update()
    {
        if (m_Sections.size() < 2) return false;

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        BRepOffsetAPI_ThruSections thruSection(true);

        for (auto section : m_Sections) {
            auto cmd = geoCmdList->getDataByID(section.CmdId);
            if (cmd == nullptr) return false;
            Interface::FITKGeoEnum::VTopoShapeType type = cmd->getGeometryCommandType() ==
                Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSFace;
            auto vshape = cmd->getShapeT<FITKOCCTopoShape>(type, section.VirtualTopoId);
            if (vshape == nullptr) return false;
            auto topoShape = vshape->getTopoShape();

            if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_EDGE) {
                BRepLib_MakeWire wire(TopoDS::Edge(topoShape));
                thruSection.AddWire(wire.Wire());
            }
            else if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_WIRE) {
                thruSection.AddWire(TopoDS::Wire(topoShape));
            }
            else if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_FACE) {
                thruSection.AddWire(ShapeAnalysis::OuterWire(TopoDS::Face(topoShape)));
            }
            else if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND) {
                TopExp_Explorer exp;
                BRepLib_MakeWire wire;
                // 按封闭曲线分组
                for (exp.Init(topoShape, TopAbs_EDGE); exp.More(); exp.Next())
                {
                    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                    if (edge.IsNull()) continue;
                    wire.Add(edge);
                }
                try
                {
                    wire.Build();
                    if (!wire.IsDone()) {
                        printLog(tr("Failed to make solid!"), 3);
                        return false;
                    }
                    thruSection.AddWire(wire.Wire());
                }
                catch (...)
                {
                    printLog(tr("Failed to make wire!"), 3);
                    return false;
                }
            }
        }

        try {
            thruSection.Build();
            if (!thruSection.IsDone()) {
                printLog(tr("Failed to make solid!"), 3);
                return false;
            }
            _occShapeAgent->updateShape(thruSection.Shape());
        }
        catch (...)
        {
            printLog(tr("Failed to make solid!"), 3);
            return false;
        }
        return true;
    }

}
